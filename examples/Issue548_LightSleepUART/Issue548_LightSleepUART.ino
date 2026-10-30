/**
 * Issue 548 standard UART sleep/wake diagnostic for LilyGO T-SIM7600X.
 *
 * Commands in the serial monitor:
 *   r - create a deterministic 4096-byte EFS file
 *   b - read it with CSCLK=0 (baseline)
 *   l - enter ESP32 light sleep with CSCLK=1, then read it after wake
 *
 * Each transfer prints host-side UART error counters and the largest observed
 * gap between bytes delivered to the application. HardwareSerial uses the
 * normal Arduino-ESP32 interrupt-backed driver; these counters do not prove
 * that the modem did or did not transmit during a gap. Use an independent
 * capture of the modem TXD line to make that determination.
 */

#include <Arduino.h>
#include <driver/gpio.h>
#include <driver/uart.h>
#include <esp_sleep.h>

// T-SIM7600X board definition. Keep this example standalone so it can be
// opened directly in Arduino IDE without importing another example's header.
static constexpr int MODEM_RX_PIN = 26;
static constexpr int MODEM_TX_PIN = 27;
static constexpr int MODEM_DTR_PIN = 32;
static constexpr int MODEM_RING_PIN = 33;
static constexpr int MODEM_FLIGHT_PIN = 25;
static constexpr int BOARD_PWRKEY_PIN = 4;
static constexpr uint32_t MODEM_POWERON_PULSE_WIDTH_MS = 500;
static constexpr uint32_t MODEM_START_WAIT_MS = 15000;
static constexpr char PRODUCT_MODEL_NAME[] = "LilyGo-SIM7600X ESP32 Version";
static HardwareSerial &SerialAT = Serial1;

static constexpr char TEST_PATH[] = "E:/issue548.bin";
static constexpr size_t TEST_FILE_SIZE = 4096;
static constexpr uint32_t MODEM_SLEEP_SETTLE_MS = 25000;
static constexpr uint32_t WAKE_UART_SETTLE_MS = 300;
#ifndef ISSUE548_UART_BAUD
#define ISSUE548_UART_BAUD 115200
#endif
#ifndef ISSUE548_RX_BUFFER
#define ISSUE548_RX_BUFFER 8192
#endif
#ifndef ISSUE548_RX_FIFO_THRESHOLD
#define ISSUE548_RX_FIFO_THRESHOLD 112
#endif
#ifndef ISSUE548_WINDOW_SIZE
#define ISSUE548_WINDOW_SIZE 512
#endif
static constexpr size_t WINDOW_SIZE = ISSUE548_WINDOW_SIZE;
static constexpr uint32_t IO_TIMEOUT_MS = 5000;

struct UartErrorCounters {
    volatile uint32_t bufferFull = 0;
    volatile uint32_t fifoOverflow = 0;
    volatile uint32_t frame = 0;
    volatile uint32_t parity = 0;
    volatile uint32_t breakError = 0;
};

static UartErrorCounters uartErrors;
static uint32_t traceBytes = 0;
static uint32_t traceStartUs = 0;
static uint32_t traceFirstByteUs = 0;
static uint32_t traceLastByteUs = 0;
static uint32_t traceMaxGapUs = 0;

static void onModemReceiveError(hardwareSerial_error_t error)
{
    switch (error) {
    case UART_BUFFER_FULL_ERROR: ++uartErrors.bufferFull; break;
    case UART_FIFO_OVF_ERROR: ++uartErrors.fifoOverflow; break;
    case UART_FRAME_ERROR: ++uartErrors.frame; break;
    case UART_PARITY_ERROR: ++uartErrors.parity; break;
    case UART_BREAK_ERROR: ++uartErrors.breakError; break;
    default: break;
    }
}

static void resetReceiveTrace()
{
    traceBytes = 0;
    traceStartUs = micros();
    traceFirstByteUs = 0;
    traceLastByteUs = 0;
    traceMaxGapUs = 0;
}

static int readModemByte()
{
    const int value = SerialAT.read();
    if (value >= 0) {
        const uint32_t now = micros();
        if (traceBytes == 0) {
            traceFirstByteUs = now - traceStartUs;
        } else if (now - traceLastByteUs > traceMaxGapUs) {
            traceMaxGapUs = now - traceLastByteUs;
        }
        traceLastByteUs = now;
        ++traceBytes;
    }
    return value;
}

static void noteReceivedBytes(size_t count)
{
    if (count == 0) {
        return;
    }
    const uint32_t now = micros();
    if (traceBytes == 0) {
        traceFirstByteUs = now - traceStartUs;
    } else if (now - traceLastByteUs > traceMaxGapUs) {
        traceMaxGapUs = now - traceLastByteUs;
    }
    traceLastByteUs = now;
    traceBytes += count;
}

static void printDiagnostics(size_t location, uint32_t fifoBefore, uint32_t bufferBefore,
                             uint32_t frameBefore, uint32_t parityBefore)
{
    Serial.printf(
        "DIAG window=%u rx=%lu first_us=%lu max_gap_us=%lu fifo_ovf=%lu buffer_full=%lu frame=%lu parity=%lu\n",
        static_cast<unsigned>(location), static_cast<unsigned long>(traceBytes),
        static_cast<unsigned long>(traceFirstByteUs), static_cast<unsigned long>(traceMaxGapUs),
        static_cast<unsigned long>(uartErrors.fifoOverflow - fifoBefore),
        static_cast<unsigned long>(uartErrors.bufferFull - bufferBefore),
        static_cast<unsigned long>(uartErrors.frame - frameBefore),
        static_cast<unsigned long>(uartErrors.parity - parityBefore));
}

static uint8_t testByte(size_t index)
{
    return static_cast<uint8_t>((index * 37U + 11U) & 0xffU);
}

static void flushModem()
{
    while (SerialAT.available()) {
        readModemByte();
    }
}

static bool readExact(uint8_t *buffer, size_t length, uint32_t timeout)
{
    const uint32_t deadline = millis() + timeout;
    size_t received = 0;
    while (received < length && static_cast<int32_t>(millis() - deadline) < 0) {
        if (SerialAT.available()) {
            const size_t count = SerialAT.readBytes(buffer + received, length - received);
            received += count;
            noteReceivedBytes(count);
        } else {
            delay(1);
        }
    }
    return received == length;
}

static String readLine(uint32_t timeout)
{
    String line;
    const uint32_t deadline = millis() + timeout;
    while (static_cast<int32_t>(millis() - deadline) < 0) {
        if (!SerialAT.available()) {
            delay(1);
            continue;
        }
        const char c = static_cast<char>(readModemByte());
        line += c;
        if (c == '\n') {
            break;
        }
    }
    return line;
}

static bool command(const String &at, uint32_t timeout = IO_TIMEOUT_MS)
{
    flushModem();
    SerialAT.print(at);
    SerialAT.print("\r\n");
    String response;
    const uint32_t deadline = millis() + timeout;
    while (static_cast<int32_t>(millis() - deadline) < 0) {
        if (SerialAT.available()) {
            response += static_cast<char>(readModemByte());
            if (response.endsWith("\r\nOK\r\n") || response.endsWith("\r\nERROR\r\n")) {
                break;
            }
        } else {
            delay(1);
        }
    }
    Serial.printf("AT %s => %s", at.c_str(), response.length() ? response.c_str() : "<timeout>\r\n");
    return response.indexOf("\r\nOK") >= 0 || response == "OK\r\n";
}

static bool ensureModemReady()
{
    // Do not toggle PWRKEY when the modem is already responding. This keeps
    // the test from powering off a modem that was left running between runs.
    if (command("AT", 2000)) {
        return true;
    }

    Serial.printf("No AT response; pulsing modem PWRKEY on GPIO%d\n", BOARD_PWRKEY_PIN);
    pinMode(BOARD_PWRKEY_PIN, OUTPUT);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
    delay(100);
    digitalWrite(BOARD_PWRKEY_PIN, HIGH);
    delay(MODEM_POWERON_PULSE_WIDTH_MS);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
    delay(MODEM_START_WAIT_MS);
    return command("AT", 5000);
}

static bool createTestFile()
{
    flushModem();
    SerialAT.printf("AT+CFTRANRX=\"%s\",%u\r\n", TEST_PATH, static_cast<unsigned>(TEST_FILE_SIZE));

    const uint32_t deadline = millis() + IO_TIMEOUT_MS;
    bool prompt = false;
    while (static_cast<int32_t>(millis() - deadline) < 0) {
        if (SerialAT.available()) {
            const char c = static_cast<char>(readModemByte());
            if (c == '>') {
                prompt = true;
                break;
            }
        } else {
            delay(1);
        }
    }
    if (!prompt) {
        Serial.println("CREATE FAIL: no CFTRANRX prompt");
        return false;
    }

    uint8_t block[128];
    for (size_t offset = 0; offset < TEST_FILE_SIZE; offset += sizeof(block)) {
        const size_t count = min(sizeof(block), TEST_FILE_SIZE - offset);
        for (size_t i = 0; i < count; ++i) {
            block[i] = testByte(offset + i);
        }
        SerialAT.write(block, count);
    }
    SerialAT.flush();

    String response;
    const uint32_t responseDeadline = millis() + IO_TIMEOUT_MS;
    while (static_cast<int32_t>(millis() - responseDeadline) < 0) {
        if (SerialAT.available()) {
            response += static_cast<char>(readModemByte());
            if (response.endsWith("\r\nOK\r\n") || response.endsWith("\r\nERROR\r\n")) {
                break;
            }
        } else {
            delay(1);
        }
    }
    Serial.printf("CREATE %s\n", response.indexOf("\r\nOK") >= 0 ? "PASS" : "FAIL");
    return response.indexOf("\r\nOK") >= 0;
}

static bool readWindow(size_t location, size_t requested)
{
    flushModem();
    resetReceiveTrace();
    const uint32_t fifoBefore = uartErrors.fifoOverflow;
    const uint32_t bufferBefore = uartErrors.bufferFull;
    const uint32_t frameBefore = uartErrors.frame;
    const uint32_t parityBefore = uartErrors.parity;
    SerialAT.printf("AT+CFTRANTX=\"%s\",%u,%u\r\n", TEST_PATH,
                    static_cast<unsigned>(location), static_cast<unsigned>(requested));

    size_t checked = 0;
    bool sawData = false;
    for (;;) {
        const String line = readLine(IO_TIMEOUT_MS);
        if (line.length() == 0) {
            Serial.printf("WINDOW %u FAIL: timeout waiting for DATA header\n", static_cast<unsigned>(location));
            printDiagnostics(location, fifoBefore, bufferBefore, frameBefore, parityBefore);
            return false;
        }

        const int header = line.indexOf("+CFTRANTX: DATA,");
        if (header >= 0) {
            const size_t comma = line.indexOf(',', header);
            const size_t chunkLength = line.substring(comma + 1).toInt();
            if (chunkLength == 0 || chunkLength > 1024) {
                Serial.println("WINDOW FAIL: invalid DATA length");
                printDiagnostics(location, fifoBefore, bufferBefore, frameBefore, parityBefore);
                return false;
            }
            uint8_t block[1024];
            if (!readExact(block, chunkLength, IO_TIMEOUT_MS)) {
                Serial.println("WINDOW FAIL: short DATA block");
                printDiagnostics(location, fifoBefore, bufferBefore, frameBefore, parityBefore);
                return false;
            }
            sawData = true;
            for (size_t i = 0; i < chunkLength; ++i) {
                if (checked + i >= requested || block[i] != testByte(location + checked + i)) {
                    Serial.printf("WINDOW %u FAIL: byte mismatch at offset %u\n",
                                  static_cast<unsigned>(location), static_cast<unsigned>(checked + i));
                    printDiagnostics(location, fifoBefore, bufferBefore, frameBefore, parityBefore);
                    return false;
                }
            }
            checked += chunkLength;
            continue;
        }

        if (line.indexOf("+CFTRANTX:0") >= 0 || line.indexOf("+CFTRANTX: 0") >= 0) {
            String terminal;
            // Firmware variants may insert an extra CRLF between the final
            // result code and OK. Skip blank lines but stop on the terminal.
            for (uint8_t i = 0; i < 3 && terminal.indexOf("OK") < 0 && terminal.indexOf("ERROR") < 0; ++i) {
                terminal = readLine(IO_TIMEOUT_MS);
            }
            const bool ok = sawData && checked == requested && terminal.indexOf("OK") >= 0;
            Serial.printf("WINDOW %u %s (%u bytes)\n", static_cast<unsigned>(location),
                          ok ? "PASS" : "FAIL", static_cast<unsigned>(checked));
            printDiagnostics(location, fifoBefore, bufferBefore, frameBefore, parityBefore);
            return ok;
        }
        // Echo, blank lines, and modem URCs are ignored before the first DATA header.
    }
}

static bool readWholeFile(const char *label)
{
    Serial.printf("--- %s ---\n", label);
    bool passed = true;
    for (size_t location = 0; location < TEST_FILE_SIZE; location += WINDOW_SIZE) {
        passed = readWindow(location, WINDOW_SIZE) && passed;
    }
    Serial.printf("%s %s\n", label, passed ? "PASS" : "FAIL");
    return passed;
}

static void restoreUartAfterLightSleep()
{
    SerialAT.end();
    uart_driver_delete(UART_NUM_1);
    delay(20);
    SerialAT.setRxBufferSize(ISSUE548_RX_BUFFER);
    SerialAT.begin(ISSUE548_UART_BAUD, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN,
                   false, 20000UL, ISSUE548_RX_FIFO_THRESHOLD);
    SerialAT.onReceiveError(onModemReceiveError);
    delay(WAKE_UART_SETTLE_MS);
    digitalWrite(MODEM_DTR_PIN, LOW);
    delay(WAKE_UART_SETTLE_MS);
    flushModem();
    command("AT");
    command("AT+CATR=1");
    command("AT+CSCLK=0");
}

static void lightSleepCycle()
{
    command("AT+CSCLK=1");
    flushModem();
    digitalWrite(MODEM_DTR_PIN, HIGH);
    Serial.printf("DTR HIGH; waiting %u ms before ESP32 light sleep\n",
                  static_cast<unsigned>(MODEM_SLEEP_SETTLE_MS));
    delay(MODEM_SLEEP_SETTLE_MS);

    gpio_wakeup_enable(static_cast<gpio_num_t>(MODEM_RING_PIN), GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();
    esp_sleep_enable_timer_wakeup(5000000ULL);
    Serial.flush();
    esp_light_sleep_start();
    gpio_wakeup_disable(static_cast<gpio_num_t>(MODEM_RING_PIN));

    Serial.println("ESP32 woke; restoring UART and modem UART sleep state");
    restoreUartAfterLightSleep();
}

void setup()
{
    Serial.begin(115200);
    SerialAT.setRxBufferSize(ISSUE548_RX_BUFFER);
    SerialAT.begin(ISSUE548_UART_BAUD, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN,
                   false, 20000UL, ISSUE548_RX_FIFO_THRESHOLD);
    pinMode(MODEM_DTR_PIN, OUTPUT);
    digitalWrite(MODEM_DTR_PIN, LOW);
    pinMode(MODEM_FLIGHT_PIN, OUTPUT);
    digitalWrite(MODEM_FLIGHT_PIN, HIGH);
    pinMode(MODEM_RING_PIN, INPUT_PULLUP);
    delay(1000);

    SerialAT.onReceiveError(onModemReceiveError);
    Serial.printf("READY: %s; pins RX=%d TX=%d DTR=%d RI=%d baud=%u rxbuf=%u fifo_threshold=%u ISR_IRAM=%s\n",
                  PRODUCT_MODEL_NAME, MODEM_RX_PIN, MODEM_TX_PIN, MODEM_DTR_PIN, MODEM_RING_PIN,
                  ISSUE548_UART_BAUD, ISSUE548_RX_BUFFER, ISSUE548_RX_FIFO_THRESHOLD,
#ifdef CONFIG_UART_ISR_IN_IRAM
                  "1"
#else
                  "0"
#endif
    );
    const bool modemReady = ensureModemReady();
    Serial.printf("MODEM_READY=%s\n", modemReady ? "1" : "0");
    command("AT+CSCLK=0");
    Serial.println("Commands: r=create file, b=baseline, l=light sleep diagnostic");
}

void loop()
{
    if (!Serial.available()) {
        delay(10);
        return;
    }
    const char commandChar = static_cast<char>(Serial.read());
    if (commandChar == 'r') {
        createTestFile();
    } else if (commandChar == 'b') {
        command("AT+CSCLK=0");
        digitalWrite(MODEM_DTR_PIN, LOW);
        readWholeFile("BASELINE");
    } else if (commandChar == 'l') {
        lightSleepCycle();
        readWholeFile("LIGHT_SLEEP");
    }
}

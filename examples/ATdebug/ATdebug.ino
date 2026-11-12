/**
 * @file      ATdebug.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-10-26
 *
 */
#include "utilities.h"
#include "Arduino.h"

bool checkRespond()
{
    for (int j = 0; j < 10; j++) {
        SerialAT.print("AT\r\n");
        String input = SerialAT.readString();
        if (input.indexOf("OK") >= 0) {
            return true;
        }
        delay(200);
    }
    return false;
}

uint32_t AutoBaud()
{
    static uint32_t rates[] = {115200, 9600, 57600,  38400, 19200,  74400, 74880,
                               230400, 460800, 2400,  4800,  14400, 28800
                              };
    for (uint8_t i = 0; i < sizeof(rates) / sizeof(rates[0]); i++) {
        uint32_t rate = rates[i];
        Serial.printf("Trying baud rate %u\n", rate);
        SerialAT.updateBaudRate(rate);
        delay(10);
        for (int j = 0; j < 10; j++) {
            SerialAT.print("AT\r\n");
            String input = SerialAT.readString();
            if (input.indexOf("OK") >= 0) {
                Serial.printf("Modem responded at rate:%u\n", rate);
                return rate;
            }
        }
    }
    SerialAT.updateBaudRate(115200);
    return 0;
}

void powerOn()
{
    // Turn on the modem
    Serial.printf("Power on modem via pin %d\n", BOARD_PWRKEY_PIN);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
    delay(100);
    digitalWrite(BOARD_PWRKEY_PIN, HIGH);
    delay(MODEM_POWERON_PULSE_WIDTH_MS);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
    delay(2000);
}

void setup()
{
    Serial.begin(115200); // Set console baud rate

    //Wait 5 second for Serial connected
    int i = 5;
    while (i--) {
        Serial.printf("Waiting for Serial to connect... %d\r\n", i);
        delay(1000);
    }

    Serial.println("Start Sketch");
    Serial.printf("Initialize SerialAT at pins RX:%d, TX:%d\n", MODEM_RX_PIN, MODEM_TX_PIN);
    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);

#ifdef BOARD_LED_PIN
    Serial.printf("Set LED pin %d OFF\n", BOARD_LED_PIN);
    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN, !LED_ON);
#endif

#ifdef BOARD_POWERON_PIN
    /* Set Power control pin output
    * * @note      Known issues, ESP32 (V1.2) version of T-A7670, T-A7608,
    *            when using battery power supply mode, BOARD_POWERON_PIN (IO12) must be set to high level after esp32 starts, otherwise a reset will occur.
    * */
    Serial.printf("Set power control pin %d HIGH\n", BOARD_POWERON_PIN);
    pinMode(BOARD_POWERON_PIN, OUTPUT);
    digitalWrite(BOARD_POWERON_PIN, HIGH);
#endif

    // Set modem reset pin ,reset modem
#ifdef MODEM_RESET_PIN
    Serial.printf("Reset modem via pin %d\n", MODEM_RESET_PIN);
    pinMode(MODEM_RESET_PIN, OUTPUT);
    digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL); delay(100);
    digitalWrite(MODEM_RESET_PIN, MODEM_RESET_LEVEL); delay(2600);
    digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL);
#endif

#ifdef MODEM_FLIGHT_PIN
    Serial.printf("Set flight mode pin %d HIGH\r\n", MODEM_FLIGHT_PIN);
    // If there is an airplane mode control, you need to exit airplane mode
    pinMode(MODEM_FLIGHT_PIN, OUTPUT);
    digitalWrite(MODEM_FLIGHT_PIN, HIGH);
#endif

#ifdef MODEM_DTR_PIN
    // Pull down DTR to ensure the modem is not in sleep state
    Serial.printf("Set DTR pin %d LOW\n", MODEM_DTR_PIN);
    pinMode(MODEM_DTR_PIN, OUTPUT);
    digitalWrite(MODEM_DTR_PIN, LOW);
#endif

    // Power key pin
    pinMode(BOARD_PWRKEY_PIN, OUTPUT);

    bool started = checkRespond();
    if (started) {
        Serial.println("Modem already started");
    } else {
        Serial.println("Modem not started, power on modem...");
        powerOn();
    }

    Serial.printf("utilities.h select model : ");
    Serial.println(PRODUCT_MODEL_NAME);

    started = checkRespond();
    // Check whether it has been started
    if (!started) {
        Serial.println("Wait modem started...");
        // Wait for the modem to finish booting
        delay(MODEM_START_WAIT_MS);
    }

    // Determine the communication baud rate
    if (AutoBaud()) {
        Serial.println(F("***********************************************************"));
        Serial.println(F(" You can now send AT commands"));
        Serial.println(F(" Enter \"AT\" (without quotes), and you should see \"OK\""));
        Serial.println(F(" If it doesn't work, select \"Both NL & CR\" in Serial Monitor"));
        Serial.println(F(" DISCLAIMER: Entering AT commands without knowing what they do"));
        Serial.println(F(" can have undesired consequences..."));
        Serial.println(F("***********************************************************\n"));
    } else {
        Serial.println(F("***********************************************************"));
        Serial.println(F(" Failed to connect to the modem! Check the baud and try again."));
        Serial.println(F("***********************************************************\n"));
    }


#ifdef BOARD_LED_PIN
    Serial.printf("Set LED pin %d ON\n", BOARD_LED_PIN);
    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN, LED_ON);
#endif

}

void loop()
{
    if (SerialAT.available()) {
        Serial.write(SerialAT.read());
    }
    if (Serial.available()) {
        SerialAT.write(Serial.read());
    }
    delay(1);
}

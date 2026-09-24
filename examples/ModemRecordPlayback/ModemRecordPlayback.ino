/**
 * @file      ModemRecordPlayback.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2026 Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2026-09-24
 * @note      Record to and play from the SIM7600G SD card.
 *            Only supports T-SIM7600X-S3-Standard.
 */

// Uncomment to print every AT command and response.
// #define DUMP_AT_COMMANDS

#include "utilities.h"
#include <Arduino.h>
#include <TinyGsmClient.h>

#if !defined(LILYGO_SIM7600X_S3_STAN)
#error "ModemRecordPlayback only supports T-SIM7600X-S3-Standard"
#endif

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, Serial);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

static const char MODEM_SD_ROOT[] = "D:/";
static const char RECORD_FILE[] = "D:/rec.wav";

bool isRecording = false;
bool isPlaying = false;
String consoleCommand;
String unsolicitedLine;

static void printHelp()
{
    Serial.println();
    Serial.println("Serial commands:");
    Serial.println("  record or r  Start recording to D:/rec.wav");
    Serial.println("  stop   or s  Stop recording");
    Serial.println("  play   or p  Play D:/rec.wav");
    Serial.println("  help   or h  Show this command list");
    Serial.println("Enter a command followed by Enter.");
    Serial.println();
}

static void printAtError(const char *message, const String &response)
{
    Serial.print("ERROR: ");
    Serial.println(message);
    if (response.length() > 0) {
        Serial.println("Modem response:");
        Serial.println(response);
    }
}

static bool checkSdCard()
{
    modem.sendAT("+FSCD=", MODEM_SD_ROOT);
    String changeDirectoryResponse;
    if (modem.waitResponse(10000UL, changeDirectoryResponse) != 1 ||
            changeDirectoryResponse.indexOf("+FSCD: D:/") < 0) {
        printAtError("Modem SD card is not available.", changeDirectoryResponse);
        return false;
    }

    modem.sendAT("+FSMEM");
    String memoryResponse;
    if (modem.waitResponse(10000UL, memoryResponse) != 1 ||
            memoryResponse.indexOf("+FSMEM: D:(") < 0) {
        printAtError("Cannot read modem SD card capacity.", memoryResponse);
        return false;
    }

    int memoryLineStart = memoryResponse.indexOf("+FSMEM: D:(");
    int memoryLineEnd = memoryResponse.indexOf('\n', memoryLineStart);
    if (memoryLineEnd < 0) {
        memoryLineEnd = memoryResponse.length();
    }
    String memoryLine = memoryResponse.substring(memoryLineStart, memoryLineEnd);
    memoryLine.trim();
    Serial.print("SD card ready: ");
    Serial.println(memoryLine);
    return true;
}

static void startRecording()
{
    if (isRecording) {
        Serial.println("ERROR: Recording is already in progress.");
        return;
    }
    if (isPlaying) {
        Serial.println("ERROR: Stop playback before recording.");
        return;
    }

    Serial.println("Checking modem SD card...");
    if (!checkSdCard()) {
        Serial.println("Recording was not started.");
        return;
    }

    modem.sendAT("+CREC=1,\"", RECORD_FILE, '"');
    String response;
    if (modem.waitResponse(10000UL, response) != 1 ||
            response.indexOf("+CREC: 1") < 0) {
        printAtError("Failed to start recording.", response);
        return;
    }

    isRecording = true;
    Serial.print("Recording started: ");
    Serial.println(RECORD_FILE);
}

static void stopRecording()
{
    if (!isRecording) {
        Serial.println("ERROR: Recording is not in progress.");
        return;
    }

    modem.sendAT("+CREC=0");
    String response;
    if (modem.waitResponse(10000UL, response) != 1 ||
            response.indexOf("+CREC: 0") < 0) {
        printAtError("Failed to stop recording.", response);
        return;
    }

    isRecording = false;
    Serial.print("Recording stopped: ");
    Serial.println(RECORD_FILE);
}

static void playRecording()
{
    if (isRecording) {
        Serial.println("ERROR: Stop recording before playback.");
        return;
    }
    if (isPlaying) {
        Serial.println("ERROR: Playback is already in progress.");
        return;
    }

    if (!checkSdCard()) {
        Serial.println("Playback was not started.");
        return;
    }

    modem.sendAT("+CCMXPLAY=\"", RECORD_FILE, "\",0,0");
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        printAtError("Failed to play D:/rec.wav. Record it first.", response);
        return;
    }

    isPlaying = true;
    Serial.print("Playback started: ");
    Serial.println(RECORD_FILE);
}

static void processConsoleCommand(String command)
{
    command.trim();
    command.toLowerCase();
    if (command.length() == 0) {
        return;
    }

    if (command == "record" || command == "r") {
        startRecording();
    } else if (command == "stop" || command == "s") {
        stopRecording();
    } else if (command == "play" || command == "p") {
        playRecording();
    } else if (command == "help" || command == "h") {
        printHelp();
    } else {
        Serial.print("ERROR: Unknown command: ");
        Serial.println(command);
        printHelp();
    }
}

static void readConsole()
{
    while (Serial.available()) {
        const char value = static_cast<char>(Serial.read());
        if (value == '\r' || value == '\n') {
            if (consoleCommand.length() > 0) {
                processConsoleCommand(consoleCommand);
                consoleCommand = "";
            }
        } else if (consoleCommand.length() < 32) {
            consoleCommand += value;
        }
    }
}

static void handleUnsolicitedLine(String line)
{
    line.trim();
    if (line.length() == 0) {
        return;
    }

    if (line.indexOf("+RECSTATE: crec stop") >= 0) {
        isRecording = false;
        Serial.println("Modem reports that recording has stopped.");
    } else if (line.indexOf("+AUDIOSTATE: audio play stop") >= 0) {
        isPlaying = false;
        Serial.println("Modem reports that playback has stopped.");
    }
}

static void readModemUrc()
{
    while (SerialAT.available()) {
        const char value = static_cast<char>(SerialAT.read());
        Serial.write(value);

        if (value == '\n') {
            handleUnsolicitedLine(unsolicitedLine);
            unsolicitedLine = "";
        } else if (value != '\r') {
            unsolicitedLine += value;
            if (unsolicitedLine.length() > 256) {
                unsolicitedLine.remove(0, unsolicitedLine.length() - 256);
            }
        }
    }
}

static void powerOnModem()
{
    pinMode(MODEM_DTR_PIN, OUTPUT);
    digitalWrite(MODEM_DTR_PIN, LOW);

    pinMode(BOARD_PWRKEY_PIN, OUTPUT);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
    delay(100);
    digitalWrite(BOARD_PWRKEY_PIN, HIGH);
    delay(MODEM_POWERON_PULSE_WIDTH_MS);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
}

static void enableAudioPowerAmplifier()
{
    modem.sendAT("+CGDRT=", MODEM_AUDIO_PA_ENABLE_GPIO, ',', 1);
    if (modem.waitResponse() != 1) {
        Serial.println("ERROR: Failed to configure audio PA GPIO 77 direction.");
    }

    modem.sendAT("+CGSETV=", MODEM_AUDIO_PA_ENABLE_GPIO, ',',
                 MODEM_AUDIO_PA_ENABLE_LEVEL);
    if (modem.waitResponse() != 1) {
        Serial.println("ERROR: Failed to enable audio PA GPIO 77.");
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("SIM7600G SD card recorder and player");
    Serial.println(PRODUCT_MODEL_NAME);

    SerialAT.begin(MODEM_BAUDRATE, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);
    powerOnModem();

    Serial.println("Waiting for modem...");
    uint8_t retry = 0;
    while (!modem.testAT(1000)) {
        Serial.print('.');
        if (++retry >= 30) {
            Serial.println("\nRetry modem power-on sequence.");
            powerOnModem();
            retry = 0;
        }
    }
    Serial.println("\nModem is ready.");

    enableAudioPowerAmplifier();
    printHelp();
}

void loop()
{
    readModemUrc();
    readConsole();
    delay(1);
}

#ifndef TINY_GSM_FORK_LIBRARY
#error "No correct definition detected. Copy this repository's lib directories to the Arduino libraries directory."
#endif

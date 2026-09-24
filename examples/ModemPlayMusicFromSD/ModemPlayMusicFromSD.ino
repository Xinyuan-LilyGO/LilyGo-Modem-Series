/**
 * @file      ModemPlayMusicFromSD.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2026 Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2026-09-24
 * @note      Play MP3 files from the SIM7600 series modem SD card.
 *            The SIM7600 module must include the audio decoding function.
 *            Only supports T-SIM7600X-S3-Standard.
 */

// Uncomment to print every AT command and response.
// #define DUMP_AT_COMMANDS

#include "utilities.h"
#include <Arduino.h>
#include <TinyGsmClient.h>
#include <vector>

#if !defined(LILYGO_SIM7600X_S3_STAN)
#error "ModemPlayMusicFromSD only supports T-SIM7600X-S3-Standard"
#endif

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, Serial);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

static const char MODEM_SD_ROOT[] = "D:/";
static const size_t MAX_DIRECTORIES = 32;
static const size_t MAX_MP3_FILES = 64;
static const uint32_t RESCAN_INTERVAL_MS = 10000;
static const uint32_t NEXT_TRACK_DELAY_MS = 500;

std::vector<String> playlist;
size_t currentTrack = 0;
bool isPlaying = false;
uint32_t nextActionAt = 0;
String unsolicitedLine;

static bool timeReached(uint32_t target)
{
    return static_cast<int32_t>(millis() - target) >= 0;
}

static bool selectDirectory(const String &path)
{
    modem.sendAT("+FSCD=", path);
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        Serial.print("Cannot open modem SD directory: ");
        Serial.println(path);
        return false;
    }
    return true;
}

static bool isMp3File(const String &name)
{
    String lowerName = name;
    lowerName.toLowerCase();
    return lowerName.endsWith(".mp3");
}

static void parseDirectoryListing(const String &response, const String &relativePath,
                                  std::vector<String> &directories)
{
    enum ListSection {
        LIST_NONE,
        LIST_DIRECTORIES,
        LIST_FILES,
    } section = LIST_NONE;

    int lineStart = 0;
    while (lineStart < response.length()) {
        int lineEnd = response.indexOf('\n', lineStart);
        if (lineEnd < 0) {
            lineEnd = response.length();
        }

        String line = response.substring(lineStart, lineEnd);
        line.trim();

        if (line == "+FSLS: SUBDIRECTORIES:") {
            section = LIST_DIRECTORIES;
        } else if (line == "+FSLS: FILES:") {
            section = LIST_FILES;
        } else if (line.startsWith("+FSLS:") || line == "OK" ||
                   line == "ERROR" || line.startsWith("AT+FSLS")) {
            section = LIST_NONE;
        } else if (line.length() > 0) {
            if (section == LIST_DIRECTORIES && line != "." && line != "..") {
                if (directories.size() < MAX_DIRECTORIES) {
                    directories.push_back(relativePath + line + "/");
                }
            } else if (section == LIST_FILES && isMp3File(line)) {
                if (line.indexOf('"') >= 0) {
                    Serial.print("Skip a file containing a quote: ");
                    Serial.println(line);
                } else if (playlist.size() < MAX_MP3_FILES) {
                    playlist.push_back(String(MODEM_SD_ROOT) + relativePath + line);
                }
            }
        }

        lineStart = lineEnd + 1;
    }
}

static bool scanMp3Files()
{
    playlist.clear();
    currentTrack = 0;

    if (!selectDirectory(MODEM_SD_ROOT)) {
        return false;
    }

    modem.sendAT("+FSMEM");
    String memoryResponse;
    if (modem.waitResponse(10000UL, memoryResponse) == 1) {
        memoryResponse.trim();
        Serial.println("Modem SD card memory:");
        Serial.println(memoryResponse);
    } else {
        Serial.println("Cannot read modem SD card capacity.");
    }

    std::vector<String> directories;
    directories.push_back("");

    for (size_t directoryIndex = 0; directoryIndex < directories.size(); ++directoryIndex) {
        const String relativePath = directories[directoryIndex];
        const String absolutePath = String(MODEM_SD_ROOT) + relativePath;

        if (!selectDirectory(absolutePath)) {
            continue;
        }

        modem.sendAT("+FSLS");
        String listResponse;
        if (modem.waitResponse(10000UL, listResponse) != 1) {
            Serial.print("Cannot list modem SD directory: ");
            Serial.println(absolutePath);
            continue;
        }
        parseDirectoryListing(listResponse, relativePath, directories);

        if (playlist.size() >= MAX_MP3_FILES) {
            Serial.println("MP3 file limit reached; remaining files are ignored.");
            break;
        }
    }

    selectDirectory(MODEM_SD_ROOT);

    Serial.printf("Found %u MP3 file(s):\n", static_cast<unsigned>(playlist.size()));
    for (size_t i = 0; i < playlist.size(); ++i) {
        Serial.printf("  %u: %s\n", static_cast<unsigned>(i + 1), playlist[i].c_str());
    }
    return !playlist.empty();
}

static bool playTrack(size_t index)
{
    if (index >= playlist.size()) {
        return false;
    }

    Serial.printf("Playing %u/%u: %s\n",
                  static_cast<unsigned>(index + 1),
                  static_cast<unsigned>(playlist.size()),
                  playlist[index].c_str());

    modem.sendAT("+CCMXPLAY=\"", playlist[index], "\",0,0");
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        Serial.println("Failed to start MP3 playback.");
        isPlaying = false;
        nextActionAt = millis() + RESCAN_INTERVAL_MS;
        return false;
    }

    isPlaying = true;
    return true;
}

static void handleUnsolicitedLine(String line)
{
    line.trim();
    if (line.length() == 0) {
        return;
    }

    if (line.indexOf("+AUDIOSTATE: audio play stop") >= 0) {
        Serial.println("Playback finished.");
        isPlaying = false;
        if (!playlist.empty()) {
            currentTrack = (currentTrack + 1) % playlist.size();
        }
        nextActionAt = millis() + NEXT_TRACK_DELAY_MS;
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
#ifdef BOARD_POWERON_PIN
    pinMode(BOARD_POWERON_PIN, OUTPUT);
    digitalWrite(BOARD_POWERON_PIN, HIGH);
#endif

#ifdef MODEM_RESET_PIN
    pinMode(MODEM_RESET_PIN, OUTPUT);
    digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL);
    delay(100);
    digitalWrite(MODEM_RESET_PIN, MODEM_RESET_LEVEL);
    delay(2600);
    digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL);
#endif

#ifdef MODEM_FLIGHT_PIN
    pinMode(MODEM_FLIGHT_PIN, OUTPUT);
    digitalWrite(MODEM_FLIGHT_PIN, HIGH);
#endif

#ifdef MODEM_DTR_PIN
    pinMode(MODEM_DTR_PIN, OUTPUT);
    digitalWrite(MODEM_DTR_PIN, LOW);
#endif

    pinMode(BOARD_PWRKEY_PIN, OUTPUT);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
    delay(100);
    digitalWrite(BOARD_PWRKEY_PIN, HIGH);
    delay(MODEM_POWERON_PULSE_WIDTH_MS);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("SIM7600 modem SD MP3 player");
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

#ifdef MODEM_AUDIO_PA_ENABLE_GPIO
    modem.sendAT("+CGDRT=", MODEM_AUDIO_PA_ENABLE_GPIO, ',', 1);
    if (modem.waitResponse() != 1) {
        Serial.println("Failed to configure the audio PA GPIO direction.");
    }

    modem.sendAT("+CGSETV=", MODEM_AUDIO_PA_ENABLE_GPIO, ',',
                 MODEM_AUDIO_PA_ENABLE_LEVEL);
    if (modem.waitResponse() != 1) {
        Serial.println("Failed to enable the audio PA.");
    }
#endif

    if (scanMp3Files()) {
        playTrack(currentTrack);
    } else {
        Serial.println("No MP3 file found. The SD card will be scanned again.");
        nextActionAt = millis() + RESCAN_INTERVAL_MS;
    }
}

void loop()
{
    readModemUrc();

    if (!isPlaying && timeReached(nextActionAt)) {
        if (playlist.empty()) {
            if (!scanMp3Files()) {
                Serial.println("No MP3 file found. Retrying in 10 seconds.");
                nextActionAt = millis() + RESCAN_INTERVAL_MS;
                return;
            }
        }
        playTrack(currentTrack);
    }

    delay(1);
}

#ifndef TINY_GSM_FORK_LIBRARY
#error "No correct definition detected. Copy this repository's lib directories to the Arduino libraries directory."
#endif

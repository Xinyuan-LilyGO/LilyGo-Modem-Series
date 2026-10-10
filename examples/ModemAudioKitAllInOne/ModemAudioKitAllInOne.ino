/**
 * @file      ModemAudioKitAllInOne.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @note      SIM7600 SD audio, voice calls and CPTONE example.
 *            Only supports T-SIM7600X-S3-Standard + Audio Kit.
 * @date      2026-10-10
 * @product   https://lilygo.cc/products/t-sim-t-a-series-standard-edition?variant=52513685536949
 */

// Uncomment to print every AT command and response.
// #define DUMP_AT_COMMANDS

#include "utilities.h"
#include <Arduino.h>
#include <TinyGsmClient.h>
#include <vector>

#if !defined(LILYGO_SIM7600X_S3_STAN)
#error "ModemAudioKit only supports T-SIM7600X-S3-Standard"
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
static const size_t MAX_AUDIO_FILES = 128;
static const long INCOMING_RING_TONE = 1;
static const long INCOMING_RING_TONE_MS = 500;
static const long DEFAULT_TONE_GAIN = 4000;
static const long DEFAULT_MICROPHONE_GAIN = 7;

bool isPlaying = false;
bool isRecording = false;
bool callActive = false;
bool callRinging = false;
bool atDebugMode = false;
String recordFile;
String consoleCommand;
String unsolicitedLine;

static bool setVoiceChannel(long device, bool printResult = true);

static void printAtError(const char *message, const String &response)
{
    Serial.print("ERROR: ");
    Serial.println(message);
    if (response.length() > 0) {
        Serial.println(response);
    }
}

static bool selectDirectory(const String &path)
{
    modem.sendAT("+FSCD=", path);
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        return false;
    }
    return true;
}

static bool stopPlayback()
{
    if (!isPlaying) {
        return true;
    }
    modem.sendAT("+CCMXSTOP");
    String response;
    const bool success = modem.waitResponse(10000UL, response) == 1;
    if (!success) {
        printAtError("Failed to stop audio playback.", response);
    }
    isPlaying = false;
    return success;
}

static bool checkSdCard()
{
    if (!selectDirectory(MODEM_SD_ROOT)) {
        Serial.println("ERROR: Modem SD card is not available.");
        return false;
    }
    modem.sendAT("+FSMEM");
    String response;
    if (modem.waitResponse(10000UL, response) != 1 || response.indexOf("+FSMEM: D:(") < 0) {
        printAtError("Cannot read modem SD card capacity.", response);
        return false;
    }
    return true;
}

static bool isAudioFile(const String &name)
{
    String lowerName = name;
    lowerName.toLowerCase();
    return lowerName.endsWith(".mp3") || lowerName.endsWith(".wav") ||
           lowerName.endsWith(".amr") || lowerName.endsWith(".aac");
}

static void parseAudioDirectory(const String &response, const String &relativePath,
                                std::vector<String> &directories, std::vector<String> &files)
{
    enum ListSection { LIST_NONE, LIST_DIRECTORIES, LIST_FILES } section = LIST_NONE;
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
        } else if (line.startsWith("+FSLS:") || line == "OK" || line == "ERROR" ||
                   line.startsWith("AT+FSLS")) {
            section = LIST_NONE;
        } else if (section == LIST_DIRECTORIES && line.length() > 0 && line != "." && line != "..") {
            if (directories.size() < MAX_DIRECTORIES) {
                directories.push_back(relativePath + line + "/");
            }
        } else if (section == LIST_FILES && isAudioFile(line) && line.indexOf('"') < 0) {
            if (files.size() < MAX_AUDIO_FILES) {
                files.push_back(String(MODEM_SD_ROOT) + relativePath + line);
            }
        }
        lineStart = lineEnd + 1;
    }
}

static void listAudioFiles()
{
    if (isRecording || callActive || callRinging) {
        Serial.println("ERROR: Stop recording and calls before listing SD files.");
        return;
    }
    if (!checkSdCard()) {
        return;
    }

    std::vector<String> directories;
    std::vector<String> files;
    directories.push_back("");
    for (size_t index = 0; index < directories.size(); ++index) {
        const String relativePath = directories[index];
        const String absolutePath = String(MODEM_SD_ROOT) + relativePath;
        if (!selectDirectory(absolutePath)) {
            continue;
        }
        modem.sendAT("+FSLS");
        String response;
        if (modem.waitResponse(10000UL, response) == 1) {
            parseAudioDirectory(response, relativePath, directories, files);
        }
        if (files.size() >= MAX_AUDIO_FILES) {
            break;
        }
    }
    selectDirectory(MODEM_SD_ROOT);

    Serial.println("Audio files on modem SD:");
    if (recordFile.length() > 0) {
        Serial.print("Current recording file: ");
        Serial.println(recordFile);
    }
    for (size_t index = 0; index < files.size(); ++index) {
        Serial.printf("  %u: %s\n", static_cast<unsigned>(index + 1), files[index].c_str());
    }
    Serial.printf("Total audio files: %u\n", static_cast<unsigned>(files.size()));
}

static String makeRecordFileName()
{
    return String(MODEM_SD_ROOT) + "rec_" + String(millis()) + ".wav";
}

static void startRecording()
{
    if (isRecording || isPlaying || callActive || callRinging) {
        Serial.println("ERROR: Stop playback and calls before recording.");
        return;
    }
    if (!checkSdCard()) {
        return;
    }
    recordFile = makeRecordFileName();
    modem.sendAT("+CREC=1,\"", recordFile, '"');
    String response;
    if (modem.waitResponse(10000UL, response) != 1 || response.indexOf("+CREC: 1") < 0) {
        printAtError("Failed to start recording.", response);
        return;
    }
    isRecording = true;
    Serial.print("Recording started: ");
    Serial.println(recordFile);
}

static void stopRecording()
{
    if (!isRecording) {
        Serial.println("ERROR: Recording is not in progress.");
        return;
    }
    modem.sendAT("+CREC=0");
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        printAtError("Failed to stop recording.", response);
        return;
    }
    isRecording = false;
    Serial.print("Recording stopped: ");
    Serial.println(recordFile);
}

static void playAudioFile(const String &path)
{
    if (path.length() == 0 || path.indexOf('"') >= 0) {
        Serial.println("Usage: play <path/file>, for example: play D:/music/test.mp3");
        return;
    }
    if (isRecording || isPlaying || callActive || callRinging) {
        Serial.println("ERROR: Stop current audio and calls before playback.");
        return;
    }
    if (!checkSdCard()) {
        return;
    }
    modem.sendAT("+CCMXPLAY=\"", path, "\",0,0");
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        printAtError("Failed to play the requested audio file.", response);
        return;
    }
    isPlaying = true;
    Serial.print("Playback started: ");
    Serial.println(path);
}

static bool parseUnsigned(const String &value, long minimum, long maximum, long &result)
{
    if (value.length() == 0) {
        return false;
    }
    for (size_t i = 0; i < value.length(); ++i) {
        if (value[i] < '0' || value[i] > '9') {
            return false;
        }
    }
    result = value.toInt();
    return result >= minimum && result <= maximum;
}

static void setSpeakerVolume(const String &arguments)
{
    long level = 0;
    if (!parseUnsigned(arguments, 0, 5, level)) {
        Serial.println("Usage: volume <0-5>");
        return;
    }
    modem.sendAT("+CLVL=", level);
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        printAtError("Failed to set speaker volume.", response);
        return;
    }
    Serial.print("Speaker volume set to ");
    Serial.println(level);
}

static void setMicrophoneGain(const String &arguments)
{
    long gain = 0;
    if (!parseUnsigned(arguments, 0, 8, gain)) {
        Serial.println("Usage: mic-gain <0-8>");
        return;
    }
    modem.sendAT("+CMICGAIN=", gain);
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        printAtError("Failed to set microphone gain.", response);
        return;
    }
    Serial.print("Microphone gain set to ");
    Serial.println(gain);
}

static void playTone(const String &arguments)
{
    String values[3];
    int count = 0;
    int start = 0;
    while (start <= arguments.length() && count < 3) {
        while (start < arguments.length() &&
               (arguments[start] == ' ' || arguments[start] == ',')) {
            ++start;
        }
        if (start >= arguments.length()) {
            break;
        }
        int end = start;
        while (end < arguments.length() && arguments[end] != ' ' && arguments[end] != ',') {
            ++end;
        }
        values[count++] = arguments.substring(start, end);
        values[count - 1].trim();
        start = end;
    }
    if (count < 2 || count > 3) {
        Serial.println("Usage: tone <0-16> <1-1000> [gain 1-9999]");
        return;
    }
    long tone = 0;
    long duration = 0;
    long gain = DEFAULT_TONE_GAIN;
    if (!parseUnsigned(values[0], 0, 16, tone) || !parseUnsigned(values[1], 1, 1000, duration) ||
        (count == 3 && !parseUnsigned(values[2], 1, 9999, gain))) {
        Serial.println("ERROR: Invalid tone parameters.");
        return;
    }
    modem.sendAT("+CPTONE=", tone, ',', duration, ',', gain);
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        printAtError("Failed to play tone.", response);
        return;
    }
    Serial.println("Tone played.");
}

static void playIncomingRingTone()
{
    for (uint8_t toneIndex = 0; toneIndex < 2; ++toneIndex) {
        modem.sendAT("+CPTONE=", INCOMING_RING_TONE, ',', INCOMING_RING_TONE_MS,
                     ',', DEFAULT_TONE_GAIN);
        String response;
        if (modem.waitResponse(10000UL, response) != 1) {
            printAtError("Failed to play the incoming-call ring tone.", response);
            return;
        }
        if (toneIndex == 0) {
            delay(100);
        }
    }
}

static void dialNumber(const String &number)
{
    if (number.length() == 0 || callActive || callRinging || isRecording) {
        Serial.println("Usage: call <phone number>; no call or recording may be active.");
        return;
    }
    stopPlayback();
    Serial.print("Dialing: ");
    Serial.println(number);
    if (modem.callNumber(number)) {
        callActive = true;
        Serial.println("Call connected.");
    } else {
        Serial.println("Call failed or was not answered.");
    }
}

static void answerCall()
{
    if (!callRinging) {
        Serial.println("ERROR: No incoming call is ringing.");
        return;
    }
    if (isRecording) {
        Serial.println("ERROR: Stop recording before answering the call.");
        return;
    }
    if (modem.callAnswer()) {
        callRinging = false;
        callActive = true;
        Serial.println("Call answered.");
    } else {
        Serial.println("Failed to answer call.");
    }
}

static void hangupCall()
{
    if (!callActive && !callRinging) {
        Serial.println("No active call.");
        return;
    }
    if (modem.callHangup()) {
        callActive = false;
        callRinging = false;
        Serial.println("Call hung up.");
    } else {
        Serial.println("Failed to hang up call.");
    }
}

static void printHelp()
{
    Serial.println();
    Serial.println("Serial commands:");
    Serial.println("  call <number>       Place a voice call");
    Serial.println("  answer              Answer an incoming call");
    Serial.println("  hangup              Hang up the current call");
    Serial.println("  volume <0-5>        Set loudspeaker volume (default 4)");
    Serial.println("  mic-gain <0-8>      Set microphone gain (default 7)");
    Serial.println("  tone <tone> <ms> [gain]  Play CPTONE (default gain 4000)");
    Serial.println("  record              Record to a timestamped D:/rec_<timestamp>.wav");
    Serial.println("  record-stop         Stop recording");
    Serial.println("  play <path/file>    Play one audio file from modem SD");
    Serial.println("  play-stop           Stop audio playback");
    Serial.println("  list-files          List recorded and other audio files on modem SD");
    Serial.println("  voice-channel <0|1|3>  Switch voice channel");
    Serial.println("  RING event          Plays a two-tone incoming-call alert");
    Serial.println("  at-debug            Enter AT command passthrough mode");
    Serial.println("  help");
    Serial.println();
}

static void processConsoleCommand(String command)
{
    command.trim();
    if (command.length() == 0) {
        return;
    }
    int separator = command.indexOf(' ');
    String action = separator < 0 ? command : command.substring(0, separator);
    String arguments = separator < 0 ? String() : command.substring(separator + 1);
    action.toLowerCase();
    arguments.trim();

    if (action == "call") {
        dialNumber(arguments);
    } else if (action == "answer") {
        answerCall();
    } else if (action == "hangup") {
        hangupCall();
    } else if (action == "volume") {
        setSpeakerVolume(arguments);
    } else if (action == "mic-gain") {
        setMicrophoneGain(arguments);
    } else if (action == "tone") {
        playTone(arguments);
    } else if (action == "record") {
        startRecording();
    } else if (action == "record-stop") {
        stopRecording();
    } else if (action == "play") {
        playAudioFile(arguments);
    } else if (action == "play-stop") {
        stopPlayback();
    } else if (action == "list-files") {
        listAudioFiles();
    } else if (action == "voice-channel") {
        long device = -1;
        if (!parseUnsigned(arguments, 0, 3, device) || (device != 0 && device != 1 && device != 3)) {
            Serial.println("Usage: voice-channel <0|1|3> (0=off, 1=handset, 3=speaker phone)");
            return;
        }
        setVoiceChannel(device);
    } else if (action == "at-debug") {
        if (isRecording || callActive || callRinging) {
            Serial.println("ERROR: Stop recording and calls before entering ATDebug mode.");
            return;
        }
        stopPlayback();
        atDebugMode = true;
        Serial.println();
        Serial.println("ATDebug mode entered. Type AT commands directly.");
        Serial.println("Type 'exit' on a separate line to return to command mode.");
    } else if (action == "help") {
        printHelp();
    } else {
        Serial.print("ERROR: Unknown command: ");
        Serial.println(action);
        printHelp();
    }
}

static void readConsole()
{
    while (Serial.available()) {
        const char value = static_cast<char>(Serial.read());
        if (value == '\r' || value == '\n') {
            if (consoleCommand.length() > 0) {
                if (atDebugMode) {
                    String debugCommand = consoleCommand;
                    debugCommand.trim();
                    String lowerCommand = debugCommand;
                    lowerCommand.toLowerCase();
                    if (lowerCommand == "exit") {
                        atDebugMode = false;
                        Serial.println("ATDebug mode exited. Type 'play' to play an audio file.");
                        printHelp();
                    } else {
                        SerialAT.print(consoleCommand);
                        SerialAT.print("\r\n");
                    }
                } else {
                    processConsoleCommand(consoleCommand);
                }
                consoleCommand = "";
            }
        } else if (consoleCommand.length() < 128) {
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
    if (line == "RING" || line.startsWith("+CRING:")) {
        callRinging = true;
        stopPlayback();
        playIncomingRingTone();
        Serial.println("Incoming call. Type 'answer' or 'hangup'.");
    } else if (line.startsWith("+CLIP:")) {
        Serial.print("Caller: ");
        Serial.println(line);
    } else if (line.indexOf("+RECSTATE: crec stop") >= 0) {
        isRecording = false;
        Serial.println("Modem reports that recording has stopped.");
    } else if (line.indexOf("+AUDIOSTATE: audio play stop") >= 0) {
        isPlaying = false;
        Serial.println("Modem reports that playback has stopped.");
    } else if (line == "NO CARRIER" || line == "BUSY" || line == "NO ANSWER" ||
               line.startsWith("MISSED_CALL") || line == "VOICE CALL: END" ||
               line.indexOf("+CIEV: \"CALL\",0") >= 0) {
        callActive = false;
        callRinging = false;
        Serial.print("Call status: ");
        Serial.println(line);
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
        Serial.println("ERROR: Failed to configure audio PA GPIO.");
    }
    modem.sendAT("+CGSETV=", MODEM_AUDIO_PA_ENABLE_GPIO, ',', MODEM_AUDIO_PA_ENABLE_LEVEL);
    if (modem.waitResponse() != 1) {
        Serial.println("ERROR: Failed to enable audio PA.");
    }
}

static void waitForModemBootServices()
{
    const uint32_t timeout = 15000UL;
    const uint32_t start = millis();
    String bootLine;

    Serial.println("Waiting for modem services...");
    while (millis() - start < timeout) {
        while (SerialAT.available()) {
            const char value = static_cast<char>(SerialAT.read());
            Serial.write(value);
            if (value == '\n') {
                bootLine.trim();
                if (bootLine == "PB DONE") {
                    Serial.println("Modem services are ready.");
                    return;
                }
                bootLine = "";
            } else if (value != '\r') {
                bootLine += value;
                if (bootLine.length() > 128) {
                    bootLine.remove(0, bootLine.length() - 128);
                }
            }
        }
        delay(10);
    }
    Serial.println("Modem service-ready URC timeout; continuing with audio setup.");
}

static bool setVoiceChannel(long device, bool printResult)
{
    if (device != 0 && device != 1 && device != 3) {
        Serial.println("Usage: voice-channel <0|1|3> (0=off, 1=handset, 3=speaker phone)");
        return false;
    }

    modem.sendAT("+CSDVC=", device);
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        printAtError("Failed to switch the voice channel.", response);
        return false;
    }
    if (printResult) {
        Serial.print("Voice channel switched to ");
        Serial.println(device);
    }
    return true;
}

static void enableNau8810VoiceCodec()
{
    // Host control is required before CSDVC can open the external NAU8810 path.
    modem.sendAT("+CODECCTL=1");
    String response;
    if (modem.waitResponse(10000UL, response) != 1) {
        printAtError("Failed to enable NAU8810 host codec control.", response);
        return;
    }
    setVoiceChannel(1, false);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("SIM7600 SD audio and voice call example");
    Serial.println(PRODUCT_MODEL_NAME);
    SerialAT.begin(MODEM_BAUDRATE, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);
    powerOnModem();
    pinMode(MODEM_RING_PIN, INPUT_PULLUP);

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
    waitForModemBootServices();
    enableAudioPowerAmplifier();
    enableNau8810VoiceCodec();
    setMicrophoneGain(String(DEFAULT_MICROPHONE_GAIN));
    printHelp();
}

void loop()
{
    readModemUrc();
    readConsole();
    delay(1);
}

#ifndef TINY_GSM_FORK_LIBRARY
#error "No correct definition detected, Please copy all the [lib directories](https://github.com/Xinyuan-LilyGO/LilyGO-T-A76XX/tree/main/lib) to the arduino libraries directory , See README"
#endif

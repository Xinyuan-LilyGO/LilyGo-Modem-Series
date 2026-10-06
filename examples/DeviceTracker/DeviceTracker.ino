/**
 * @file      DeviceTracker.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2026  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2026-09-29
 * @note      Long-running camera/GNSS/modem power-cycle test for the SIM7670G/SIM7080G variants of T-SIM-S3-Standard.
 * 
 *            SIM7080G acquires GNSS before activating the cellular PDP context because that modem cannot run GNSS and packet data at the same time.
 *            
 *            If you need to view the logs, please disable the "USB CDC ON BOOT" option so that serial log output is 
 *            directed to the QWIIC UART port by default; using the USB CDC interface causes the USB connection to shut down when entering light sleep, making it impossible to view the serial logs.
 * 
 *            The complete test report for this example can be found here: https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/issues/540#issuecomment-6008206690
 *
 *            This example requires you to set up your own Gotify server(https://gotify.net/); if you use a different service, you can modify the HTTP POST section to send data to your server.
 *            private server. You will not receive any data unless a valid server is specified.
 * 
 */
#define TINY_GSM_RX_BUFFER 1024

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG Serial

// Keep raw modem commands/responses visible while diagnosing the first GPS run.
#define DUMP_AT_COMMANDS

#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <esp_camera.h>
#include <esp_sleep.h>
#include "utilities.h"
#include <TinyGsmClient.h>
#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
#endif

#if !defined(LILYGO_SIM7670G_S3_STAN) && !defined(LILYGO_SIM7080G_S3_STAN)
#error "This example is for T-SIM7670G-S3-Standard or T-SIM7080G-S3-Standard only. Please define one of these boards in utilities.h."
#endif

#define SLEEP_SECONDS 7200ULL
#define BATTERY_CUTOFF_MV 3200U
#define MODEM_BOOT_TIMEOUT_MS 30000UL
#define SIM_READY_TIMEOUT_MS 20000UL
#define NETWORK_TIMEOUT_MS 90000UL
#define GPS_TIMEOUT_MS 180000UL
#define PHOTO_MIN_FREE_BYTES (2ULL * 1024ULL * 1024ULL)
#define GOTIFY_BODY_MAX_BYTES 1024U

#ifndef NETWORK_APN
#define NETWORK_APN ""
#endif

static const char *const GOTIFY_URL = "YOUR_GOTIFY_URL_HERE";
static const char *const GOTIFY_TOKEN = "YOUR_GOTIFY_TOKEN_HERE";

#if defined(LILYGO_SIM7670G_S3_STAN)
static const char *const  GOTIFY_USER_AGENT = "LilyGo-T-SIM7670G-S3-Standard";
#elif defined(LILYGO_SIM7080G_S3_STAN)
static const char *const  GOTIFY_USER_AGENT = "LilyGo-T-SIM7080G-S3-Standard";
#endif

static const char *const apn = NETWORK_APN;

#ifdef DUMP_AT_COMMANDS
StreamDebugger debugger(SerialAT, Serial);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
RTC_DATA_ATTR uint32_t wakeCount = 0;
RTC_DATA_ATTR uint32_t modemResetCount = 0;

struct WakeData {
    uint32_t batteryAdcMv = 0;
    uint32_t solarAdcMv = 0;
    uint32_t batteryCbcMv = 0;
    uint32_t modemWakeMs = 0;
    uint32_t networkMs = 0;
    uint32_t gpsMs = 0;
    uint32_t photoMs = 0;
    uint32_t totalToGotifyMs = 0;
    bool simReady = false;
    bool registered = false;
    bool gpsFix = false;
    bool gotifySent = false;
    bool photoSaved = false;
    bool sdMounted = false;
    uint64_t sdTotalBytes = 0;
    uint64_t sdUsedBytes = 0;
    uint64_t sdFreeBytes = 0;
    String cameraModel = "unknown";
    String eventUtc = "unknown";
    String nextWakeUtc = "unknown";
    String timeSource = "unknown";
    GPSInfo gps;
};

struct DateTimeParts {
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
};

static bool cameraPowerStarted = false;

void shallowSleep(uint32_t ms)
{
    esp_sleep_enable_timer_wakeup((uint64_t)ms * 1000ULL);
    esp_light_sleep_start();
}

uint32_t readVoltageMv(uint8_t pin)
{
    uint32_t total = 0;
    for (int i = 0; i < 8; ++i) {
        total += analogReadMilliVolts(pin);
        delay(2);
    }
    return (total / 8U) * 2U; // board divider is 1:2
}

void cameraPower(bool enable)
{
    if (!cameraPowerStarted) {
        Wire.begin(BOARD_SDA_PIN, BOARD_SCL_PIN);
        cameraPowerStarted = true;
    }
    uint8_t rails[] = {0x03, 0x7C, 0x7C, 0xCA, 0xB1};
    Wire.beginTransmission(0x28);
    Wire.write(rails, sizeof(rails));
    Wire.endTransmission();

    uint8_t control[] = {0x0E, (uint8_t)(enable ? 0x0F : 0x00)};
    Wire.beginTransmission(0x28);
    Wire.write(control, sizeof(control));
    Wire.endTransmission();
    if (enable) {
        control[1] = 0x00;
        Wire.beginTransmission(0x28);
        Wire.write(control, sizeof(control));
        Wire.endTransmission();
        delay(300);
        control[1] = 0x0F;
        Wire.beginTransmission(0x28);
        Wire.write(control, sizeof(control));
        Wire.endTransmission();
        delay(100);
    }
}

void cameraPowerOff()
{
    if (cameraPowerStarted) {
        cameraPower(false);
        Serial.println("Camera power OFF");
    }
}

void enterDeepSleep(const char *reason)
{
    Serial.printf("Deep sleep: %s (%llu s)\n", reason, SLEEP_SECONDS);
    cameraPowerOff();
#ifdef BOARD_POWER_SAVE_MODE_PIN
    pinMode(BOARD_POWER_SAVE_MODE_PIN, OUTPUT);
    digitalWrite(BOARD_POWER_SAVE_MODE_PIN, LOW);
#endif
    Serial.flush();
    esp_sleep_enable_timer_wakeup(SLEEP_SECONDS * 1000000ULL);
    delay(100);
    esp_deep_sleep_start();
}

bool startModem(WakeData &data)
{
    Serial.println("STEP modem: starting UART and pulsing PWRKEY");
    uint32_t started = millis();
    SerialAT.begin(MODEM_BAUDRATE, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);
    pinMode(MODEM_DTR_PIN, OUTPUT);
    digitalWrite(MODEM_DTR_PIN, LOW);

#ifdef BOARD_POWER_SAVE_MODE_PIN
    pinMode(BOARD_POWER_SAVE_MODE_PIN, OUTPUT);
    digitalWrite(BOARD_POWER_SAVE_MODE_PIN, HIGH);
#endif

    pinMode(BOARD_PWRKEY_PIN, OUTPUT);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
    delay(100);
    digitalWrite(BOARD_PWRKEY_PIN, HIGH);
    delay(MODEM_POWERON_PULSE_WIDTH_MS);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);

    bool online = false;
    while (millis() - started < MODEM_BOOT_TIMEOUT_MS) {
        if (modem.testAT(800)) {
            online = true;
            break;
        }
        shallowSleep(300);
    }
    data.modemWakeMs = millis() - started;
    Serial.printf("Modem wake: %lu ms, online=%s\n", (unsigned long)data.modemWakeMs,
                  online ? "yes" : "no");
    if (!online) return false;

    modem.sendAT("E0");
    modem.waitResponse(1000);
#if defined(LILYGO_SIM7670G_S3_STAN)
    Serial.println("STEP time: enabling automatic network clock updates");
    modem.sendAT("+CTZR=0");
    bool timezoneUrcDisabled = modem.waitResponse(1000) == 1;
    modem.sendAT("+CTZU=1");
    bool automaticTimeEnabled = modem.waitResponse(1000) == 1;
    Serial.printf("Network clock setup: CTZR=%s CTZU=%s\n",
                  timezoneUrcDisabled ? "OK" : "FAILED",
                  automaticTimeEnabled ? "OK" : "FAILED");
#endif
    return true;
}

bool waitForSim(WakeData &data)
{
    Serial.println("STEP modem: checking CPIN/SIM readiness");
    uint32_t started = millis();
    while (millis() - started < SIM_READY_TIMEOUT_MS) {
        SimStatus status = modem.getSimStatus();
        if (status == SIM_READY) {
            data.simReady = true;
            Serial.printf("CPIN/SIM ready after %lu ms\n", (unsigned long)(millis() - started));
            return true;
        }
        if (status == SIM_LOCKED || status == SIM_ERROR) {
            Serial.printf("CPIN error, status=%d\n", status);
            return false;
        }
        shallowSleep(500);
    }
    Serial.println("CPIN timeout");
    return false;
}

bool hasUsablePdpAddress(const String &ip)
{
    return ip.length() > 0 && ip != "0.0.0.0" && ip != "::";
}

bool waitForPdpAddress(uint32_t timeoutMs)
{
    uint32_t started = millis();
    while (millis() - started < timeoutMs) {
        String ip = modem.getLocalIP();
        ip.trim();
        Serial.printf("PDP address=%s\n", ip.length() ? ip.c_str() : "unavailable");
        if (hasUsablePdpAddress(ip)) return true;
        shallowSleep(1000);
    }
    return false;
}

void prepareNetworkMode()
{
#if defined(LILYGO_SIM7080G_S3_STAN)
    Serial.println("STEP network: GNSS is off; configuring SIM7080G Cat-M/NB-IoT mode");
    bool networkModeOk = modem.setNetworkMode(MODEM_NETWORK_AUTO);
    bool preferredModeOk = modem.setPreferredMode(MODEM_PREFERRED_CATM_NBIOT);
    Serial.printf("SIM7080G network mode=%s preferred mode=%s\n",
                  networkModeOk ? "OK" : "FAILED",
                  preferredModeOk ? "OK" : "FAILED");
#endif
}

bool waitForNetwork(WakeData &data)
{
    Serial.println("STEP network: waiting for CEREG registration and PDP activation");
    uint32_t started = millis();
    bool modemWasResponsive = true;
    while (millis() - started < NETWORK_TIMEOUT_MS) {
        if (!modem.testAT(700)) {
            if (modemWasResponsive) {
                modemResetCount++;
                Serial.printf("Modem became unresponsive; reset count=%lu\n", (unsigned long)modemResetCount);
            }
            modemWasResponsive = false;
            shallowSleep(1000);
            continue;
        }
        modemWasResponsive = true;
        RegStatus status = modem.getRegistrationStatus();
        int16_t csq = modem.getSignalQuality();
        Serial.printf("CEREG=%d CSQ=%d elapsed=%lu ms\n", status, csq,
                      (unsigned long)(millis() - started));
        if (status == REG_OK_HOME || status == REG_OK_ROAMING) {
            data.registered = true;
            for (uint8_t attempt = 1; attempt <= 3; ++attempt) {
                Serial.printf("PDP activation attempt %u/3\n", attempt);
                if (modem.setNetworkActive(String(apn), false) &&
                    waitForPdpAddress(10000)) {
                    data.networkMs = millis() - started;
                    Serial.printf("Network and PDP ready after %lu ms\n",
                                  (unsigned long)data.networkMs);
                    return true;
                }
                Serial.println("PDP activation did not produce a usable IP address");
                if (attempt < 3) shallowSleep(3000);
            }
            break;
        }
        shallowSleep(2000);
    }
    data.networkMs = millis() - started;
    Serial.printf("Network timeout after %lu ms\n", (unsigned long)data.networkMs);
    return false;
}

void readVoltages(WakeData &data)
{
    Serial.println("STEP power: reading battery ADC, solar ADC and modem battery API");
    analogSetAttenuation(ADC_11db);
    analogReadResolution(12);
    data.batteryAdcMv = readVoltageMv(BOARD_BAT_ADC_PIN);
    data.solarAdcMv = readVoltageMv(BOARD_SOLAR_ADC_PIN);
    data.batteryCbcMv = modem.getBattVoltage();
    Serial.printf("Battery ADC=%lu mV, Solar ADC=%lu mV, Modem API battery=%lu mV\n",
                  (unsigned long)data.batteryAdcMv, (unsigned long)data.solarAdcMv,
                  (unsigned long)data.batteryCbcMv);
}

bool acquireGps(WakeData &data)
{
    Serial.println("STEP GPS: enabling GNSS and waiting for a fix (light sleep polling)");
    uint32_t started = millis();
#if defined(LILYGO_SIM7080G_S3_STAN)
    Serial.println("STEP GPS: ensuring SIM7080G PDP context is inactive before GNSS");
    if (modem.getNetworkActive() && !modem.setNetworkDeactivate()) {
        Serial.println("WARNING: failed to deactivate PDP before GNSS");
    }
#endif
    if (!modem.enableGPS(MODEM_GPS_ENABLE_GPIO, MODEM_GPS_ENABLE_LEVEL)) {
        Serial.println("GPS enable failed");
        modem.disableGPS(MODEM_GPS_ENABLE_GPIO, 0);
        data.gpsMs = millis() - started;
        return false;
    }
#if defined(TINY_GSM_MODEM_A7670) || defined(TINY_GSM_MODEM_A7608)
    modem.setGPSMode(GNSS_MODE_GPS_BDS_GALILEO_SBAS_QZSS);
#elif defined(TINY_GSM_MODEM_SIM7670G)
    modem.setGPSMode(GNSS_MODE_GPS_GLONASS_GALILEO_BDS);
#elif defined(TINY_GSM_MODEM_SIM7600)
    modem.setGPSMode(GNSS_MODE_ALL);
#elif defined(TINY_GSM_MODEM_SIM7000SSL) || defined(TINY_GSM_MODEM_SIM7000)
    modem.setGPSMode(GNSS_MODE_ALL);
#endif
    while (millis() - started < GPS_TIMEOUT_MS) {
        if (modem.getGPS_Ex(data.gps)) {
            data.gpsFix = data.gps.isFix;
            if (data.gpsFix) break;
        }
        shallowSleep(2000); // GPS query must not busy-spin
    }
    data.gpsMs = millis() - started;
    bool gpsDisabled = modem.disableGPS(MODEM_GPS_ENABLE_GPIO, 0);
#if defined(LILYGO_SIM7080G_S3_STAN)
    if (!gpsDisabled) {
        Serial.println("STEP GPS: first GNSS shutdown failed; retrying once");
        shallowSleep(500);
        gpsDisabled = modem.disableGPS(MODEM_GPS_ENABLE_GPIO, 0);
    }
#endif
    Serial.printf("STEP GPS: fix query finished, GNSS shutdown=%s\n",
                  gpsDisabled ? "OK" : "FAILED");
#if defined(LILYGO_SIM7080G_S3_STAN)
    Serial.println("STEP GPS: waiting for SIM7080G GNSS shutdown before cellular attach");
    shallowSleep(1000);
#endif
    if (!data.gpsFix) {
        Serial.printf("GPS timeout after %lu ms; continuing with the remaining steps\n",
                      (unsigned long)data.gpsMs);
    }
    Serial.printf("GPS fix=%s after %lu ms, lat=%.7f lon=%.7f speed=%.2f\n",
                  data.gpsFix ? "yes" : "no", (unsigned long)data.gpsMs,
                  data.gps.latitude, data.gps.longitude, data.gps.speed);
    return data.gpsFix;
}

bool isLeapYear(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int daysInMonth(int year, int month)
{
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

bool validDateTime(const DateTimeParts &value, int minimumYear = 2000)
{
    return value.year >= minimumYear && value.month >= 1 && value.month <= 12 &&
           value.day >= 1 && value.day <= daysInMonth(value.year, value.month) &&
           value.hour >= 0 && value.hour <= 23 && value.minute >= 0 &&
           value.minute <= 59 && value.second >= 0 && value.second <= 59;
}

void shiftDate(DateTimeParts &value, int deltaDays)
{
    while (deltaDays > 0) {
        value.day++;
        if (value.day > daysInMonth(value.year, value.month)) {
            value.day = 1;
            value.month++;
            if (value.month > 12) {
                value.month = 1;
                value.year++;
            }
        }
        deltaDays--;
    }

    while (deltaDays < 0) {
        value.day--;
        if (value.day < 1) {
            value.month--;
            if (value.month < 1) {
                value.month = 12;
                value.year--;
            }
            value.day = daysInMonth(value.year, value.month);
        }
        deltaDays++;
    }
}

void addSeconds(DateTimeParts &value, int64_t seconds)
{
    int64_t secondsOfDay = (int64_t)value.hour * 3600 +
                           (int64_t)value.minute * 60 + value.second + seconds;
    int deltaDays = 0;
    while (secondsOfDay < 0) {
        secondsOfDay += 86400;
        deltaDays--;
    }
    while (secondsOfDay >= 86400) {
        secondsOfDay -= 86400;
        deltaDays++;
    }
    shiftDate(value, deltaDays);
    value.hour = secondsOfDay / 3600;
    value.minute = (secondsOfDay % 3600) / 60;
    value.second = secondsOfDay % 60;
}

String isoUtc(const DateTimeParts &value)
{
    char formatted[32];
    snprintf(formatted, sizeof(formatted), "%04d-%02d-%02dT%02d:%02d:%02dZ",
             value.year, value.month, value.day, value.hour, value.minute,
             value.second);
    return String(formatted);
}

bool parseNetworkClock(const String &raw, DateTimeParts &utc, int &timezoneQuarters)
{
    int shortYear = 0;
    char timezoneSign = 0;
    int matched = sscanf(raw.c_str(), "%d/%d/%d,%d:%d:%d%c%d", &shortYear,
                         &utc.month, &utc.day, &utc.hour, &utc.minute,
                         &utc.second, &timezoneSign, &timezoneQuarters);
    if (matched != 8 || (timezoneSign != '+' && timezoneSign != '-')) return false;

    utc.year = shortYear < 100 ? shortYear + 2000 : shortYear;
    if (timezoneSign == '-') timezoneQuarters = -timezoneQuarters;
    // 3GPP +CCLK expresses the local-time offset in 15-minute units.
    if (!validDateTime(utc, 2020) || timezoneQuarters < -96 || timezoneQuarters > 96) {
        return false;
    }
    addSeconds(utc, -(int64_t)timezoneQuarters * 15 * 60);
    return true;
}

void resolveWakeTime(WakeData &data)
{
    DateTimeParts currentUtc;
    if (data.gpsFix) {
        currentUtc.year = data.gps.year;
        currentUtc.month = data.gps.month;
        currentUtc.day = data.gps.day;
        currentUtc.hour = data.gps.hour;
        currentUtc.minute = data.gps.minute;
        currentUtc.second = data.gps.second;
        if (validDateTime(currentUtc)) {
            data.timeSource = "gps";
        }
    }

    if (data.timeSource == "unknown") {
        Serial.println("STEP time: GPS time unavailable; reading network clock with AT+CCLK?");
        for (uint8_t attempt = 1; attempt <= 3; ++attempt) {
            String raw = modem.getGSMDateTime(DATE_FULL);
            raw.trim();
            int timezoneQuarters = 0;
            Serial.printf("Network clock attempt %u/3: %s\n", attempt,
                          raw.length() ? raw.c_str() : "no response");
            if (parseNetworkClock(raw, currentUtc, timezoneQuarters)) {
                data.timeSource = "network";
                Serial.printf("Network clock accepted; UTC offset=%d minutes\n",
                              timezoneQuarters * 15);
                break;
            }
            if (attempt < 3) shallowSleep(2000);
        }
    }

    if (data.timeSource == "unknown") {
        Serial.println("WARNING: GPS and network clocks are unavailable; absolute wake time is unknown");
        return;
    }

    data.eventUtc = isoUtc(currentUtc);
    addSeconds(currentUtc, SLEEP_SECONDS);
    data.nextWakeUtc = isoUtc(currentUtc);
}

const char *cameraModelName(uint16_t pid)
{
    switch (pid) {
    case OV9650_PID: return "OV9650";
    case OV7725_PID: return "OV7725";
    case OV2640_PID: return "OV2640";
    case OV3660_PID: return "OV3660";
    case OV5640_PID: return "OV5640";
    case OV7670_PID: return "OV7670";
    case NT99141_PID: return "NT99141";
    case GC2145_PID: return "GC2145";
    case GC032A_PID: return "GC032A";
    case GC0308_PID: return "GC0308";
    default: return "UNKNOWN";
    }
}

bool sendGotify(WakeData &data, uint32_t cycleStartedMs)
{
    Serial.println("STEP network: sending telemetry to Gotify");
    // Keep custom telemetry in Gotify's retained extras object for backend parsing.
    char body[1280];
    data.totalToGotifyMs = millis() - cycleStartedMs;
    char notification[384];
    snprintf(notification, sizeof(notification),
             "Wake->Send %.1fs\\nModem wake %.1fs\\nGPS %.1fs %s\\n"
             "Network %.1fs %s\\nPhoto %.1fs %s\\n"
             "Battery ADC %lumV | Modem %lumV | Solar %lumV\\n"
             "SD %.2fGiB free | Camera %s\\nNext %s (%s time)",
             data.totalToGotifyMs / 1000.0f, data.modemWakeMs / 1000.0f,
             data.gpsMs / 1000.0f, data.gpsFix ? "OK" : "FAILED",
             data.networkMs / 1000.0f,
             data.registered ? "OK" : "FAILED", data.photoMs / 1000.0f,
             data.photoSaved ? "OK" : "SKIP/FAIL", (unsigned long)data.batteryAdcMv,
             (unsigned long)data.batteryCbcMv, (unsigned long)data.solarAdcMv,
             data.sdFreeBytes / (1024.0f * 1024.0f * 1024.0f),
             data.cameraModel.c_str(), data.nextWakeUtc.c_str(),
             data.timeSource.c_str());
    int priority = (data.gpsFix && data.sdMounted && data.photoSaved) ? 0 : 5;
    int bodyLength = snprintf(body, sizeof(body),
             "{\"title\":\"%s wake %lu\",\"message\":\"%s\",\"priority\":%d,\"extras\":{\"com.lilygo.issue540\":{\"wake\":%lu,\"battery_adc_mv\":%lu,\"solar_adc_mv\":%lu,\"battery_cbc_mv\":%lu,\"modem_wake_ms\":%lu,\"network_ms\":%lu,\"gps_ms\":%lu,\"photo_ms\":%lu,\"total_to_gotify_ms\":%lu,\"sim_ready\":%s,\"registered\":%s,\"gps_fix\":%s,\"gps_result\":\"%s\",\"latitude\":%.7f,\"longitude\":%.7f,\"date\":\"%s\",\"time_source\":\"%s\",\"speed_knots\":%.2f,\"sd_mounted\":%s,\"sd_total_bytes\":%llu,\"sd_used_bytes\":%llu,\"sd_free_bytes\":%llu,\"camera_model\":\"%s\",\"photo_saved\":%s,\"next_wakeup_utc\":\"%s\",\"next_wakeup_in_s\":%llu,\"modem_resets\":%lu}}}",
             PRODUCT_MODEL_NAME, (unsigned long)wakeCount, notification, priority,
             (unsigned long)wakeCount, (unsigned long)data.batteryAdcMv,
             (unsigned long)data.solarAdcMv, (unsigned long)data.batteryCbcMv,
             (unsigned long)data.modemWakeMs, (unsigned long)data.networkMs,
             (unsigned long)data.gpsMs, (unsigned long)data.photoMs,
             (unsigned long)data.totalToGotifyMs, data.simReady ? "true" : "false",
             data.registered ? "true" : "false", data.gpsFix ? "true" : "false",
             data.gpsFix ? "OK" : "FAILED", data.gps.latitude, data.gps.longitude,
             data.eventUtc.c_str(), data.timeSource.c_str(), data.gps.speed,
             data.sdMounted ? "true" : "false",
             (unsigned long long)data.sdTotalBytes, (unsigned long long)data.sdUsedBytes,
             (unsigned long long)data.sdFreeBytes, data.cameraModel.c_str(),
             data.photoSaved ? "true" : "false", data.nextWakeUtc.c_str(),
             (unsigned long long)SLEEP_SECONDS, (unsigned long)modemResetCount);
    if (bodyLength < 0 || bodyLength >= (int)sizeof(body) ||
        bodyLength > (int)GOTIFY_BODY_MAX_BYTES) {
        Serial.printf("Gotify JSON too long: %d bytes (modem limit=%u)\n",
                      bodyLength, GOTIFY_BODY_MAX_BYTES);
        return false;
    }
    Serial.printf("Gotify JSON length=%d\n", bodyLength);
    Serial.println(body);

    String uploadIp = modem.getLocalIP();
    uploadIp.trim();
    Serial.printf("STEP network: verifying PDP before Gotify, address=%s\n",
                  uploadIp.length() ? uploadIp.c_str() : "unavailable");
    if (!hasUsablePdpAddress(uploadIp)) {
        Serial.println("PDP is inactive before Gotify; attempting one recovery");
        if (!modem.setNetworkActive(String(apn), false) ||
            !waitForPdpAddress(10000)) {
            Serial.println("Gotify skipped: PDP recovery failed");
            return false;
        }
    }
    bool ok = modem.https_begin();
    Serial.printf("Gotify HTTPS begin=%s\n", ok ? "OK" : "FAILED");
    if (ok) {
        ok = modem.https_set_url(GOTIFY_URL);
        Serial.printf("Gotify URL setup=%s\n", ok ? "OK" : "FAILED");
    }
    if (ok) {
        ok = modem.https_add_header("X-Gotify-Key", GOTIFY_TOKEN);
        ok = modem.https_set_content_type("application/json") && ok;
        ok = modem.https_set_user_agent(GOTIFY_USER_AGENT) && ok;
        Serial.printf("Gotify headers=%s\n", ok ? "OK" : "FAILED");
    }
    if (ok) {
        int code = modem.https_post(body);
        ok = code == 200 || code == 202;
        Serial.printf("Gotify HTTP status=%d\n", code);
        Serial.print("Gotify response: ");
        Serial.println(modem.https_body());
    }
    modem.https_end();
    return ok;
}

void updateSdStats(WakeData &data)
{
    data.sdMounted = SD.cardType() != CARD_NONE;
    if (!data.sdMounted) {
        data.sdTotalBytes = 0;
        data.sdUsedBytes = 0;
        data.sdFreeBytes = 0;
        return;
    }
    data.sdTotalBytes = SD.totalBytes();
    data.sdUsedBytes = SD.usedBytes();
    data.sdFreeBytes = data.sdTotalBytes > data.sdUsedBytes
                           ? data.sdTotalBytes - data.sdUsedBytes
                           : 0;
    Serial.printf("SD mounted=yes total=%llu used=%llu free=%llu bytes\n",
                  (unsigned long long)data.sdTotalBytes,
                  (unsigned long long)data.sdUsedBytes,
                  (unsigned long long)data.sdFreeBytes);
}

bool setupSd(WakeData &data)
{
    Serial.println("STEP SD: mounting card and reading capacity");
    SPI.begin(BOARD_SCK_PIN, BOARD_MISO_PIN, BOARD_MOSI_PIN);
    if (!SD.begin(BOARD_SD_CS_PIN) || SD.cardType() == CARD_NONE) {
        data.sdMounted = false;
        data.sdTotalBytes = 0;
        data.sdUsedBytes = 0;
        data.sdFreeBytes = 0;
        Serial.println("SD mounted=no");
        return false;
    }
    updateSdStats(data);
    return true;
}

bool capturePhoto(WakeData &data)
{
    Serial.println("STEP camera: powering camera, capturing JPEG and writing SD");
    uint32_t started = millis();
    bool saved = false;
    cameraPower(true);
    pinMode(BOARD_POWER_SAVE_MODE_PIN, OUTPUT);
    digitalWrite(BOARD_POWER_SAVE_MODE_PIN, HIGH);
    camera_config_t config = {};
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = CAMERA_Y2_PIN; config.pin_d1 = CAMERA_Y3_PIN;
    config.pin_d2 = CAMERA_Y4_PIN; config.pin_d3 = CAMERA_Y5_PIN;
    config.pin_d4 = CAMERA_Y6_PIN; config.pin_d5 = CAMERA_Y7_PIN;
    config.pin_d6 = CAMERA_Y8_PIN; config.pin_d7 = CAMERA_Y9_PIN;
    config.pin_xclk = CAMERA_XCLK_PIN; config.pin_pclk = CAMERA_PCLK_PIN;
    config.pin_vsync = CAMERA_VSYNC_PIN; config.pin_href = CAMERA_HREF_PIN;
    config.pin_sccb_sda = CAMERA_SIOD_PIN; config.pin_sccb_scl = CAMERA_SIOC_PIN;
    config.pin_pwdn = CAMERA_PWDN_PIN; config.pin_reset = CAMERA_RESET_PIN;
    config.xclk_freq_hz = 20000000; config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_HD; config.jpeg_quality = 5;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM; config.fb_count = 2;
    if (esp_camera_init(&config) != ESP_OK) {
        Serial.println("Camera init failed");
        data.cameraModel = "INIT_FAILED";
        cameraPowerOff();
        data.photoMs = millis() - started;
        return false;
    }
    sensor_t *sensor = esp_camera_sensor_get();
    data.cameraModel = cameraModelName(sensor ? sensor->id.PID : 0);
    Serial.printf("Camera model: %s\n", data.cameraModel.c_str());
    camera_fb_t *frame = esp_camera_fb_get();
    if (frame) {
        if (!SD.exists("/camera")) SD.mkdir("/camera");
        char path[48];
        snprintf(path, sizeof(path), "/camera/%lu.jpg", (unsigned long)wakeCount);
        File image = SD.open(path, FILE_WRITE);
        if (image) {
            saved = image.write(frame->buf, frame->len) == frame->len;
            image.close();
            Serial.printf("Photo %s (%u bytes)\n", saved ? "saved" : "write failed", (unsigned)frame->len);
        }
        esp_camera_fb_return(frame);
    }
    // Always release the camera driver and its regulator after one capture.
    esp_camera_deinit();
    cameraPowerOff();
    updateSdStats(data);
    data.photoMs = millis() - started;
    Serial.printf("Photo step finished in %lu ms\n", (unsigned long)data.photoMs);
    return saved;
}

void appendLog(WakeData &data)
{
    if (!data.sdMounted && !setupSd(data)) return;
    File log = SD.open("/issue540.csv", FILE_APPEND);
    if (!log) return;
    if (log.size() == 0) log.println("wake,battery_adc_mv,solar_adc_mv,battery_cbc_mv,modem_wake_ms,network_ms,gps_ms,photo_ms,total_to_gotify_ms,sim_ready,registered,gps_fix,gotify,photo,sd_mounted,sd_free_bytes,camera_model,next_wakeup_utc,modem_resets");
    log.printf("%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%d,%d,%d,%d,%d,%d,%llu,%s,%s,%lu\n",
               (unsigned long)wakeCount, (unsigned long)data.batteryAdcMv,
               (unsigned long)data.solarAdcMv, (unsigned long)data.batteryCbcMv,
               (unsigned long)data.modemWakeMs, (unsigned long)data.networkMs,
               (unsigned long)data.gpsMs, (unsigned long)data.photoMs,
               (unsigned long)data.totalToGotifyMs, data.simReady, data.registered,
               data.gpsFix, data.gotifySent, data.photoSaved,
               data.sdMounted, (unsigned long long)data.sdFreeBytes,
               data.cameraModel.c_str(), data.nextWakeUtc.c_str(),
               (unsigned long)modemResetCount);
    log.close();
}

void setup()
{
    uint32_t cycleStartedMs = millis();
    Serial.begin(115200);
    delay(100);
    wakeCount++;
    Serial.println("STEP 0: boot/wake sequence started");
    Serial.printf("\nWake %lu, reset cause=%d\n", (unsigned long)wakeCount, esp_sleep_get_wakeup_cause());

    analogSetAttenuation(ADC_11db);
    analogReadResolution(12);
    WakeData data;
    data.gps = GPSInfo{};
    data.batteryAdcMv = readVoltageMv(BOARD_BAT_ADC_PIN);
    Serial.printf("Startup battery ADC=%lu mV (cutoff=%u mV)\n", (unsigned long)data.batteryAdcMv, BATTERY_CUTOFF_MV);
    if (data.batteryAdcMv <= BATTERY_CUTOFF_MV) {
        Serial.println("STEP battery: voltage too low, modem will not be started");
        enterDeepSleep("battery <= 3.2 V; modem not started");
    }

    Serial.println("STEP 1: waking modem");
    if (!startModem(data)) enterDeepSleep("modem boot timeout");
    Serial.println("STEP 2: checking SIM/CPIN");
    if (!waitForSim(data)) {
        modem.poweroff();
        enterDeepSleep("CPIN/SIM error");
    }
#if defined(LILYGO_SIM7080G_S3_STAN)
    Serial.println("STEP 3: recording power measurements before GNSS");
    readVoltages(data);
    Serial.println("STEP 4: acquiring GPS before cellular PDP activation");
    acquireGps(data);
    Serial.println("STEP 5: GNSS is off; registering on cellular network");
    prepareNetworkMode();
    if (!waitForNetwork(data)) {
        modem.poweroff();
        enterDeepSleep("network registration/PDP timeout");
    }
#else
    Serial.println("STEP 3: registering on cellular network");
    prepareNetworkMode();
    if (!waitForNetwork(data)) {
        modem.poweroff();
        enterDeepSleep("network registration/PDP timeout");
    }
    Serial.println("STEP 4: recording power measurements");
    readVoltages(data);
    Serial.println("STEP 5: starting GPS acquisition");
    acquireGps(data);
#endif
    resolveWakeTime(data);
    Serial.printf("Current UTC: %s, source=%s\n", data.eventUtc.c_str(),
                  data.timeSource.c_str());
    Serial.printf("Next wake UTC: %s (in %llu s)\n", data.nextWakeUtc.c_str(), SLEEP_SECONDS);
    Serial.println("STEP 6: mounting SD and reading capacity");
    setupSd(data);
    Serial.println("STEP 7: capturing photo");
    if (data.sdMounted) {
        if (data.sdFreeBytes < PHOTO_MIN_FREE_BYTES) {
            data.cameraModel = "SKIPPED_LOW_SD";
            Serial.printf("Photo skipped: SD free space %llu bytes is below %llu-byte safety threshold\n",
                          (unsigned long long)data.sdFreeBytes,
                          (unsigned long long)PHOTO_MIN_FREE_BYTES);
        } else {
            data.photoSaved = capturePhoto(data);
        }
    } else {
        data.cameraModel = "SD_NOT_MOUNTED";
        Serial.println("Photo skipped because SD is not mounted");
    }
    Serial.println("STEP 8: posting telemetry");
    data.gotifySent = sendGotify(data, cycleStartedMs);
    Serial.printf("Wake to Gotify request start: %lu ms\n", (unsigned long)data.totalToGotifyMs);
    appendLog(data);

    Serial.println("STEP 9: powering off modem and entering deep sleep");
    modem.poweroff();
    delay(300);
    enterDeepSleep("cycle complete");
}

void loop() {}

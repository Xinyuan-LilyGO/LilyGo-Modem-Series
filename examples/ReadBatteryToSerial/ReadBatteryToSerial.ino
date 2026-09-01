/**
 * @file      ReadBattery.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2026  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2026-03-24
 * @note      Only support T-A7670 ,T-A7608X, T-SIM7670G board , not support T-Call A7670 , T-PCIE-A7670
 *
 *            T-SIM7600 series ,T-SIM7670G ：When the USB is connected, the battery mV is 0 because the battery voltage cannot be read when the USB is plugged in.
 * 
 * Use an external serial bridge to monitor changes in battery voltage.
 *
 *  Platformio User: In platformio.ini, enable the -UARDUINO_USB_CDC_ON_BOOT field in the [esp32s3_base] section,
 *             and add a semicolon before -DARDUINO_USB_CDC_ON_BOOT=1 to disable USB CDC output and use hardware serial port to output messages.
 *  ArduinoIDE User: USB CDC On Boot -> set Disabled
 *
 *  ISSUE: https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/issues/464#issuecomment-4114996364
 */
#include <Arduino.h>
#include <esp32-hal-adc.h>
#include "utilities.h"


#ifndef BOARD_BAT_ADC_PIN
#error "No support this board"
#endif

#define uS_TO_S_FACTOR          1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP           10          /* Time ESP32 will go to sleep (in seconds) */

char buf[256];


void setup()
{
    Serial.begin(115200); // Set console baud rate

#ifdef BOARD_POWERON_PIN
    /* Set Power control pin output
    * * @note      Known issues, ESP32 (V1.2) version of T-A7670, T-A7608,
    *            when using battery power supply mode, BOARD_POWERON_PIN (IO12) must be set to high level after esp32 starts, otherwise a reset will occur.
    * */
    pinMode(BOARD_POWERON_PIN, OUTPUT);
    digitalWrite(BOARD_POWERON_PIN, HIGH);
#endif

    // You don't need to set it, because the values ​​are all default. The current version is Arduino 3.0.4, and the subsequent versions are uncertain.

    analogSetAttenuation(ADC_11db);

    analogReadResolution(12);

#if CONFIG_IDF_TARGET_ESP32
    analogSetWidth(12);
#endif

    Serial.println("-----------------------------");
    Serial.println("Start to read battery voltage output message to hardware serial");
    Serial.println("UART Bridge connection method");
    Serial.println("ESP32 TX  --->  UART Bridge RX");
    Serial.println("ESP32 RX  --->  UART Bridge TX");
    Serial.println("Platformio User: In platformio.ini, enable the -UARDUINO_USB_CDC_ON_BOOT field in the [esp32s3_base] section,");
    Serial.println("    and add a semicolon before -DARDUINO_USB_CDC_ON_BOOT=1 to disable USB CDC output and use hardware serial port to output messages.");
    Serial.println("ArduinoIDE User: USB CDC On Boot -> set Disabled");
    Serial.println("-----------------------------");
}

void loop()
{
    //only send data when connected

    uint32_t timeNow = millis() / 1000;
    Serial.print("[");
    Serial.print(timeNow);
    Serial.print("] ");
    esp_sleep_wakeup_cause_t  wakeup_reason = esp_sleep_get_wakeup_cause();
    switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("Wakeup caused by timer");
        break;
    case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println("Wakeup caused by external signal");
        break;
    case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println("Wakeup caused by external signal");
        break;
    default:
        Serial.println("Wakeup caused by unknown reason");
        break;
    }

    uint32_t battery_voltage = analogReadMilliVolts(BOARD_BAT_ADC_PIN);
    battery_voltage *= 2;   //The hardware voltage divider resistor is half of the actual voltage, multiply it by 2 to get the true voltage

#ifdef BOARD_SOLAR_ADC_PIN
    uint32_t solar_voltage = analogReadMilliVolts(BOARD_SOLAR_ADC_PIN);
    solar_voltage *= 2;     //The hardware voltage divider resistor is half of the actual voltage, multiply it by 2 to get the true voltage
    snprintf(buf, 256, "Battery:%umV \tSolar:%umV",  battery_voltage, solar_voltage);
#else
    snprintf(buf, 256, "Battery:%umV ",  battery_voltage);
#endif

    // When connected to the USB, the battery voltage data read is not the real battery voltage,
    // so the battery voltage is sent to the UDP Server through UDP. When using it, please disconnect the USBC
    Serial.print("[");
    Serial.print(timeNow);
    Serial.print("] ");
    Serial.println(buf);
    Serial.print("[");
    Serial.print(timeNow);
    Serial.print("] ");
    Serial.printf("Go to sleep for %u seconds\n", TIME_TO_SLEEP);
    Serial.println("-----------------------------");
    Serial.flush();
    delay(120);
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    esp_light_sleep_start();
}

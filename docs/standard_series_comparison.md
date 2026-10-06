<div align="center" markdown="1">
  <img src="../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo Standard Series🌟</h1>

<div align="center">

[English](./standard_series_comparison.md) | [中文](./cn/standard_series_comparison_cn.md)

</div>

---

# LilyGo Standard Series Comparison

## Overview

This document provides a detailed comparison of the LilyGo Standard series development boards, highlighting their common features and differences to help users select the most suitable model.

The Standard series are cellular IoT development boards based on ESP32-S3, featuring unified hardware design and pin layout with support for various cellular modules.

## Standard Series Product List

| Product Model          | Cellular Module | Deep Sleep Current |
| ---------------------- | --------------- | ------------------ |
| T-A7670X-S3-Standard   | A7670X          | 314uA              |
| T-SIM7670G-S3-Standard | SIM7670G        | 147uA              |
| T-SIM7000G-S3-Standard | SIM7000G        | 166uA              |
| T-SIM7080G-S3-Standard | SIM7080G        | 128uA              |
| T-SIM7600G-S3-Standard | SIM7600G-H R2   | 128uA              |

## Common Features

All Standard series products share the following features:

### Hardware Platform
- **Main Controller**: ESP32-S3-WROOM-1 (NR16R2)
- **Flash**: 16MB (Quad-SPI)
- **PSRAM**: 2MB (Quad-SPI)

### Functional Features
- ✅ QWIIC Interface (I2C/UART)
- ✅ Seamless Power Switching (USB-C/Battery/Solar)
- ✅ GNSS Routing to SOC
- ✅ eSIM Pad Support
- ✅ BMS Battery Management System
- ✅ Camera Interface (24 Pin FPC)
- ✅ Pin-Compatible Design
- ✅ Onboard 2W (4 ohms) audio amplifier (A7670X series)

### Electrical Parameters
| Parameter                    | Specification |
| ---------------------------- | ------------- |
| USB-C Input Voltage          | 4.5V ~ 5.5V   |
| VBUS Pin Input Voltage       | 4.5V ~ 5.5V   |
| Solar Input Voltage          | 5V ~ 6V       |
| Max Charging Current         | 500mA         |
| Battery Voltage              | 3.7V          |
| Battery Type                 | Single-cell rechargeable Li-ion/LiPo (4.2 V full-charge) |
| Battery Holder Voltage Range | 3.4V ~ 4.3V   |

> \[!IMPORTANT]
>
> Do not use or charge LiFePO4 batteries, or any battery with a full-charge voltage other than 4.2 V, in these devices. These devices support only single-cell rechargeable Li-ion/LiPo batteries with a 4.2 V full-charge voltage.

### Connectors
- JST 2.0mm Solar Interface
- 24 Pin 0.5mm FPC Camera Interface
- QWIIC I2C Interface
- QWIIC UART/I2C Interface
- JST 1.0mm Speaker Interface (selected models)
- JST 1.0mm Microphone Interface (selected models)
- JST 1.0mm RTC Battery Interface (selected models)

### Buttons
- BOOT: Custom Function/Download Mode
- RST: Reset Button
- SBOOT: Module Upgrade Mode

### Antenna Interfaces
- LTE Main Antenna Interface
- GNSS Active Antenna Interface

### LED Indicators
- MODEM STATE (Red)
- MODEM NET (Red)
- CHARGE LED (Red)
- CHARGE DONE LED (Green)

## Key Differences

### 1. Cellular Module Comparison

| Feature    | A7670X | SIM7670G | SIM7000G | SIM7080G | SIM7600G-H R2 |
| ---------- | ------ | -------- | -------- | -------- | ------------- |
| GPS        | ✅*     | ✅        | ✅        | ✅        | ✅             |
| Phone Call | ✅*     | ❌        | ❌        | ❌        | ✅             |
| SMS        | ✅*     | ✅**      | GSM Only | ❌        | ✅             |
| LTE-FDD    | ✅      | ✅        | ✅        | ✅        | ✅             |
| LTE-TDD    | ❌      | ✅        | ❌        | ❌        | ✅             |
| WCDMA      | ❌      | ❌        | ❌        | ❌        | ✅             |
| GSM        | ✅*     | ❌        | ✅        | ❌        | ✅             |
| Cat-M      | ❌      | ❌        | ✅        | ✅        | ❌             |
| Cat-NB     | ❌      | ❌        | ✅        | ✅        | ❌             |

*Depends on specific module version

**Requires operator base station to support SMS Over SGS service

### 2. GNSS PPS Support

| Product Model          | GNSS PPS |
| ---------------------- | -------- |
| T-A7670X-S3-Standard   | ✅        |
| T-SIM7670G-S3-Standard | ✅        |
| T-SIM7000G-S3-Standard | ❌        |
| T-SIM7080G-S3-Standard | ❌        |
| T-SIM7600G-S3-Standard | ❌        |

### 3. Frequency Band Support

#### T-A7670X-S3-Standard
Supports different frequency bands based on specific module version:
- A7670E-FASE: LTE-FDD B1/B3/B5/B7/B8/B20, GSM 900/1800
- A7670SA-FASE: LTE-FDD B1/B2/B3/B4/B5/B7/B8/B28/B66, GSM 850/900/1800/1900
- A7670G-LLSE: LTE-FDD B1/B2/B3/B4/B5/B7/B8/B20/B28/B66, LTE-TDD B34/B38/B39/B40/B41, GSM 850/900/1800/1900

#### T-SIM7670G-S3-Standard
- LTE-FDD: B1/B2/B3/B4/B5/B7/B8/B12/B13/B18/B19/B20/B25/B26/B28/B66/B71
- LTE-TDD: B34/B38/B39/B40/B41

#### T-SIM7000G-S3-Standard
- Cat-M: B1/B2/B3/B4/B5/B8/B12/B13/B18/B19/B20/B26/B28/B39
- Cat-NB: B1/B2/B3/B5/B8/B12/B13/B17/B18/B19/B20/B26/B28
- GSM: 850/900/1800/1900MHz

#### T-SIM7080G-S3-Standard
- Cat-M: B1/B2/B3/B4/B5/B8/B12/B13/B14/B18/B19/B20/B25/B26/B27/B28/B66/B85
- Cat-NB: B1/B2/B3/B4/B5/B8/B12/B13/B18/B19/B20/B25/B26/B28/B66/B71/B85

#### T-SIM7600G-S3-Standard
- LTE-FDD: B1/B2/B3/B4/B5/B7/B8/B12/B13/B18/B19/B20/B25/B26/B28/B66
- LTE-TDD: B34/B38/B39/B40/B41
- WCDMA: B1/B2/B4/B5/B6/B8/B19
- GSM: 850/900/1800/1900MHz

### 4. GPS Antenna Power Control

Different models use different AT commands to control GPS antenna power:

| Product Model          | GPIO      | Enable Command                | Disable Command               |
| ---------------------- | --------- | ----------------------------- | ----------------------------- |
| T-A7670X-S3-Standard   | 1         | `AT+CGDRT=1,1; AT+CGSETV=1,1` | `AT+CGDRT=1,1; AT+CGSETV=1,0` |
| T-SIM7670G-S3-Standard | 1         | `AT+CGDRT=1,1; AT+CGSETV=1,1` | `AT+CGDRT=1,1; AT+CGSETV=1,0` |
| T-SIM7000G-S3-Standard | 48        | `AT+CGPIO=0,48,1,1`           | `AT+CGPIO=0,48,1,0`           |
| T-SIM7080G-S3-Standard | 5         | `AT+SGPIO=0,5,1,1`            | `AT+SGPIO=0,5,1,0`            |
| T-SIM7600G-S3-Standard | AUX Power | `AT+CVAUXV=2800; AT+CVAUXS=1` | `AT+CVAUXS=0`                 |


> \[!IMPORTANT]
>
> A7670G+GPS orders use an external GPS module and can only use [S3_StandardSeries_External_GPS_Shield Example](../../../../examples/S3_StandardSeries_External_GPS_Shield/S3_StandardSeries_External_GPS_Shield.ino). Other GPS examples cannot be used.
> 

### 5. Arduino IDE Configuration

When using Arduino IDE, uncomment the corresponding macro definition in the `utilities.h` file:

| Product Model          | Macro Definition                  |
| ---------------------- | --------------------------------- |
| T-A7670X-S3-Standard   | `#define LILYGO_A7670X_S3_STAN`   |
| T-SIM7670G-S3-Standard | `#define LILYGO_SIM7670G_S3_STAN` |
| T-SIM7000G-S3-Standard | `#define LILYGO_SIM7000G_S3_STAN` |
| T-SIM7080G-S3-Standard | `#define LILYGO_SIM7080G_S3_STAN` |
| T-SIM7600G-S3-Standard | `#define LILYGO_SIM7600X_S3_STAN` |

## Selection Guide

### For Phone Call Functionality
- **T-A7670X-S3-Standard**: Supports phone calls (depends on module version)
- **T-SIM7600G-S3-Standard**: Supports phone calls (requires audio expansion kit)

### For Low Power Applications
- **T-SIM7080G-S3-Standard**: Lowest deep sleep current (128uA)
- **T-SIM7600G-S3-Standard**: Lowest deep sleep current (128uA)

### For Cat-M/NB-IoT Support
- **T-SIM7000G-S3-Standard**: Supports Cat-M and Cat-NB
- **T-SIM7080G-S3-Standard**: Supports Cat-M and Cat-NB

### For Global Frequency Band Support
- **T-SIM7670G-S3-Standard**: Supports the widest range of LTE bands
- **T-SIM7600G-S3-Standard**: Supports LTE, WCDMA, and GSM

### For GNSS PPS Functionality
- **T-A7670X-S3-Standard**: Supports GNSS PPS
- **T-SIM7670G-S3-Standard**: Supports GNSS PPS

## Resource Links

Detailed documentation for each model:
- [T-A7670X-S3-Standard](./en/esp32s3/a7670x-s3-standard/README.MD)
- [T-SIM7670G-S3-Standard](./en/esp32s3/sim7670g-s3-standard/README.MD)
- [T-SIM7000G-S3-Standard](./en/esp32s3/sim7000g-s3-standard/README.MD)
- [T-SIM7080G-S3-Standard](./en/esp32s3/sim7080-s3-standard/README.MD)
- [T-SIM7600G-S3-Standard](./en/esp32s3/sim7600g-s3-standard/README.MD)

Hardware Resources:
- [Schematics](./schematic/standard/)
- [3D Models](./dimensions/Standard/)
- [Antenna Specifications](./datasheet/)

## FAQ

### Are all Standard series products pin-compatible?
Yes, all Standard series products use the same pin layout and are compatible with each other.

### How to determine the specific version of my module?
Send the AT command `AT+SIMCOMATI` to return the firmware version and hardware version.

### What is the deep sleep current test method?
The deep sleep current test records can be found in [DeepSleep.ino](../examples/DeepSleep/DeepSleep.ino).

### Can other GPS antennas be used?
External GPS antennas must be active GPS antennas supporting 3.3V power supply. For example, [MK-76](https://www.rfmw.com/datasheets/sanav/mk-76.pdf) supports 2.5-5.5V and is compatible with most active GPS antennas.

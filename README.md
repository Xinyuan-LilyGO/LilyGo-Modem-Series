<div align="center" markdown="1">
  <img src=".github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo-Modem-Series🌟</h1>

<div align="center">

[English](./README.md) | [中文](./README_cn.md)

</div>

[![PlatformIO CI](https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/actions/workflows/platformio.yml/badge.svg)](https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/actions/workflows/platformio.yml)

# News

- 2025/09/19 : Added SIM7070G support, compatible with SIM7080G
- 2025/08/07 : Completed support for SIM7080G series
- 2025/07/26 : Add **T-SimShield** support, please refer to the [document](./docs/en/SimshieldUsageGuide/README.md) here for quick setup
- 2025/07/10 : The example has completed most of the support for SIM7000G. For non-encrypted MQTT, please refer to the description above the example. Some of them are not supported.
- 2025/07/09 : Completed support for SIM7600 series
- The TinyGSM used in the example is a [fork](https://github.com/lewisxhe/TinyGSM) to support A7670,A7608,SIM7672G,SIM7670G, If you use the master branch, the compilation will not go smoothly

> \[!IMPORTANT]
> If you encounter a problem during use, first check whether the modem's current firmware version is the latest, and then search for [issues](https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/issues) to see if there are similar issues.
>

## ESP32 Version Get Started

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0;">
  <tr style="border: 0;">
    <!-- T-A7670X -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/a7670-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q334-T-A7670E-ESP32.png" alt="T-A7670X-ESP32" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-A7670X Quick Start</div>
      </a>
    </td>
    <!-- T-A7608X -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/a7608-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q344-T-A7608-ESP32.png" alt="T-A7608X-ESP32" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-A7608X Quick Start</div>
      </a>
    </td>
    <!-- T-SIM7000G -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/sim7000-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q141-SIM7000G-ESP32.png" alt="T-SIM7000G-ESP32" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7000G Quick Start</div>
      </a>
    </td>
  </tr>
</table>

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-SIM7070G-ESP32 -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/sim7070-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q323-T-SIM7070G-ESP32.png" alt="T-SIM7070G-ESP32" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7070G Quick Start</div>
      </a>
    </td>
    <!-- T-SIM7600X -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/sim7600-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H503-T-SIM7600G-ESP32.png" alt="T-SIM7600X" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7600X Quick Start</div>
      </a>
    </td>
    <!-- T-Call-A7670X -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/t-call-a7670x/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H700-T-Call-A7670-ESP32.png" alt="T-Call-A7670X" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-Call-A7670X Quick Start</div>
      </a>
    </td>
  </tr>
</table>

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-PCIE-Series -->
    <td style="padding: 10px 20px; width: 50%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/pcie-series-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q415-PCIE-ESP32.png" alt="T-PCIE-Series" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-PCIE-Series Quick Start</div>
      </a>
    </td>
    <!-- T-InterNetCom -->
    <td style="padding: 10px 20px; width: 50%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/t-internet-com-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q329-T-Internet-COM.png" alt="T-Internet-COM" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-Internet-COM Quick Start</div>
      </a>
    </td>
</table>

## ESP32S3 Version Get Started

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-A7608-S3 -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/a7608x-s3/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H694-T-A7608-S3.png" alt="T-A7608-S3" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-A7608X-ESP32S3 Quick Start</div>
      </a>
    </td>
    <!-- T-SIM7670G-ESP32S3 -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/sim7670g-s3/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H707-T-SIM7670G-ESP32S3.png" alt="T-SIM7670G-ESP32S3" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7670G-ESP32S3 Quick Start</div>
      </a>
    </td>
    <!-- T-Eth-Elite-ESP32S3 -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/t-eth-elite-s3/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H744-T-ETH-Elite-LTE.png" alt="T-Eth-Elite-ESP32S3" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-Eth-Elite Quick Start</div>
      </a>
    </td>
  </tr>
  
</table>

## ESP32S3 Version Standard Series Get Started

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-A7670X-S3-Standard -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/a7670x-s3-standard/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H799-01-T-A7670X-S3-Standard.png" alt="T-A7670X-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-A7670X-S3-Standard Quick Start</div>
      </a>
    </td>
    <!-- T-SIM7670G-S3-Standard -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/sim7670g-s3-standard/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H802-T-SIM7670G-S3-Standard.png" alt="T-SIM7670G-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7670G-S3-Standard Quick Start</div>
      </a>
    </td>
    <!-- T-SIM7000G-S3-Standard -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/sim7000g-s3-standard/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H794-T-SIM7000G-S3-Standard.png" alt="T-SIM7000G-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7000G-S3-Standard Quick Start</div>
      </a>
    </td>
  </tr>
</table>

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-SIM7080G-S3-Standard -->
    <td style="padding: 10px 20px; width: 50%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/sim7080-s3-standard/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H795T-SIM7080G-S3-Standard.png" alt="T-SIM7080G-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7080G-S3-Standard Quick Start</div>
      </a>
    </td>
    <!-- T-SIM7600G-S3-Standard -->
    <td style="padding: 10px 20px; width: 50%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/sim7600g-s3-standard/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H803-T-SIM7600G-S3-Standard.png" alt="T-SIM7600G-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7600G-S3-Standard Quick Start</div>
      </a>
    </td>
  </tr>
</table>

## Sim Series Shield

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-SimShield -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/SimshieldUsageGuide/README.md" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H783-SimShield.png" alt="T-A7670X-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">SimShield Usage Guide</div>
      </a>
    </td>
    <!-- T-SimHat Relay -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="https://lilygo.cc/products/lilygo%C2%AE-t-simhat-can-rs485-relay-5v" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H607-T-SIM-Hat.png" alt="T-SIM7670G-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SimHat RelayUsage Guide</div>
      </a>
    </td>
    <!-- T-SimHat Can/RS485 -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="https://lilygo.cc/products/lilygo%C2%AE-t-simhat-can-rs485-relay-5v?variant=42200124752053" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H559-T-SIM-Can.png" alt="T-SimHat Can/RS485" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SimHat Can/RS485 Usage Guide</div>
      </a>
    </td>
  </tr>
</table>

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-SIM7600G-S3-Standard -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/shield/n322-t-sim7600g-s3-standard-expansionkit/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H803-N322.png" alt="T-SIM7600G-S3-Standard-ExpansionKit" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7600G-S3-Standard-ExpansionKit Usage Guide</div>
      </a>
    <!-- DC-Shield -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/shield/t-dc-shield/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H812-DC-Shield.png" alt="T-SimDcShield" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SimDcShield Usage Guide</div>
      </a>
    </td>
    </td>
    <!-- T-BAT -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/shield/t-bat/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/T-BAT.png" alt="T-SIM7600G-S3-Standard-ExpansionKit" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-BAT Usage Guide</div>
      </a>
    </td>
</table>

<!-- - 🔧 **[SimShield Usage Guide](./docs/en/SimshieldUsageGuide/README.md)** -->

## Standard Series Comparison

- 🔧 **[Standard Series Selection Comparison](./docs/standard_series_comparison.md)**

## Modem firmware Upgrade Guide

- 🔧 **[A7670/A7608 Upgrade Guide](./docs/update_fw.md)**
- 🔧 **[SIM7670G Upgrade Guide](./docs/en/upgrade/sim7670g/sim7670g_upgrade.md)**
- 🔧 **[SIM7000G Upgrade Guide](./docs/en/esp32/sim7000-esp32/upgrade/sim7000_upgrade.md)**
- 🔧 **[SIM7080G Upgrade Guide](./docs/en/esp32s3/sim7080-s3-standard/upgrade/README.MD)**
- 🔧 **[SIM7600X Upgrade Guide](./docs/en/esp32/sim7600-esp32/upgrade/sim7600_upgrade.md)**


## Model Comparison

- ⁉️ **[Differences between different versions and models](./docs/model_comparison.md)**

## Modem firmware bug summary

- 🐞 **[Modem firmware bug summary](./docs/simcom_firmware_bug.md)**

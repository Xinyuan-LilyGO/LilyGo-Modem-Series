<div align="center" markdown="1">
  <img src=".github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo-Modem-Series🌟</h1>

<div align="center">

[English](./README.md) | [中文](./README_cn.md)

</div>

[![PlatformIO CI](https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/actions/workflows/platformio.yml/badge.svg)](https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/actions/workflows/platformio.yml)

# 最新动态

- 2025/09/19：新增 SIM7070G 支持，兼容 SIM7080G
- 2025/08/07：完成 SIM7080G 系列支持
- 2025/07/26：新增 **T-SimShield** 支持，请参阅[文档](./docs/en/SimshieldUsageGuide/README.md)快速上手
- 2025/07/10：示例已完成大部分 SIM7000G 支持。非加密 MQTT 请参阅示例上方说明，部分示例暂不支持。
- 2025/07/09：完成 SIM7600 系列支持
- 示例中使用的 TinyGSM 为 [fork 版本](https://github.com/lewisxhe/TinyGSM)，用于支持 A7670、A7608、SIM7672G、SIM7670G。如使用主线版本，编译将无法正常进行。

> \[!IMPORTANT\]
> 如遇问题，请先检查模块固件是否为最新版本，然后在 [issues](https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/issues) 中搜索是否有类似问题。
>

## ESP32 版本快速入门

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0;">
  <tr style="border: 0;">
    <!-- T-A7670X -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/a7670-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q334-T-A7670E-ESP32.png" alt="T-A7670X-ESP32" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-A7670X 快速入门</div>
      </a>
    </td>
    <!-- T-A7608X -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/a7608-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q344-T-A7608-ESP32.png" alt="T-A7608X-ESP32" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-A7608X 快速入门</div>
      </a>
    </td>
    <!-- T-SIM7000G -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/sim7000-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q141-SIM7000G-ESP32.png" alt="T-SIM7000G-ESP32" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7000G 快速入门</div>
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
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7070G 快速入门</div>
      </a>
    </td>
    <!-- T-SIM7600X -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/sim7600-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H503-T-SIM7600G-ESP32.png" alt="T-SIM7600X" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7600X 快速入门</div>
      </a>
    </td>
    <!-- T-Call-A7670X -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/t-call-a7670x/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H700-T-Call-A7670-ESP32.png" alt="T-Call-A7670X" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-Call-A7670X 快速入门</div>
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
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-PCIE 系列快速入门</div>
      </a>
    </td>
    <!-- T-InterNetCom -->
    <td style="padding: 10px 20px; width: 50%; border: 0; background: transparent;">
      <a href="./docs/en/esp32/t-internet-com-esp32/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/Q329-T-Internet-COM.png" alt="T-Internet-COM" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-Internet-COM 快速入门</div>
      </a>
    </td>
</table>

## ESP32S3 版本快速入门

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-A7608-S3 -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/a7608x-s3/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H694-T-A7608-S3.png" alt="T-A7608-S3" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-A7608X-ESP32S3 快速入门</div>
      </a>
    </td>
    <!-- T-SIM7670G-ESP32S3 -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/sim7670g-s3/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H707-T-SIM7670G-ESP32S3.png" alt="T-SIM7670G-ESP32S3" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7670G-ESP32S3 快速入门</div>
      </a>
    </td>
    <!-- T-Eth-Elite-ESP32S3 -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/t-eth-elite-s3/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H744-T-ETH-Elite-LTE.png" alt="T-Eth-Elite-ESP32S3" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-Eth-Elite 快速入门</div>
      </a>
    </td>
  </tr>
</table>

## ESP32S3 Standard 系列快速入门

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-A7670X-S3-Standard -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/a7670x-s3-standard/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H799-01-T-A7670X-S3-Standard.png" alt="T-A7670X-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-A7670X-S3-Standard 快速入门</div>
      </a>
    </td>
    <!-- T-SIM7670G-S3-Standard -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/sim7670g-s3-standard/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H802-T-SIM7670G-S3-Standard.png" alt="T-SIM7670G-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7670G-S3-Standard 快速入门</div>
      </a>
    </td>
    <!-- T-SIM7000G-S3-Standard -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/sim7000g-s3-standard/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H794-T-SIM7000G-S3-Standard.png" alt="T-SIM7000G-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7000G-S3-Standard 快速入门</div>
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
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7080G-S3-Standard 快速入门</div>
      </a>
    </td>
    <!-- T-SIM7600G-S3-Standard -->
    <td style="padding: 10px 20px; width: 50%; border: 0; background: transparent;">
      <a href="./docs/en/esp32s3/sim7600g-s3-standard/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H803-T-SIM7600G-S3-Standard.png" alt="T-SIM7600G-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7600G-S3-Standard 快速入门</div>
      </a>
    </td>
  </tr>
</table>

## Sim 系列扩展板

<table style="width: 100%; border-collapse: collapse; text-align: center; border: 0; border-spacing: 0; margin: 20px 0;">
  <tr style="border: 0;">
    <!-- T-SimShield -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/SimshieldUsageGuide/README.md" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H783-SimShield.png" alt="T-A7670X-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">SimShield 使用指南</div>
      </a>
    </td>
    <!-- T-SimHat Relay -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="https://lilygo.cc/products/lilygo%C2%AE-t-simhat-can-rs485-relay-5v" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H607-T-SIM-Hat.png" alt="T-SIM7670G-S3-Standard" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SimHat 继电器版快速入门</div>
      </a>
    </td>
    <!-- T-SimHat Can/RS485 -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="https://lilygo.cc/products/lilygo%C2%AE-t-simhat-can-rs485-relay-5v?variant=42200124752053" style="text-decoration: none; display: block;">
        <img src="./images/product/png/H559-T-SIM-Can.png" alt="T-SimHat Can/RS485" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SimHat Can/RS485 快速入门</div>
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
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-SIM7600G-S3-Standard 扩展套件快速入门</div>
      </a>
    </td>
    <!-- T-BAT -->
    <td style="padding: 10px 20px; width: 33.33%; border: 0; background: transparent;">
      <a href="./docs/en/shield/t-bat/README.MD" style="text-decoration: none; display: block;">
        <img src="./images/product/png/T-BAT.png" alt="T-SIM7600G-S3-Standard-ExpansionKit" width="200" style="border: 0;"/>
        <div style="color: #FFFF; font-weight: 600; margin-top: 8px;">T-BAT 快速入门</div>
      </a>
    </td>
</table>

## Standard 系列对比

- 🔧 **[Standard 系列选型对比](./docs/cn/standard_series_comparison_cn.md)**

## 模块固件升级指南

- 🔧 **[A7670/A7608 升级指南](./docs/update_fw.md)**
- 🔧 **[SIM7670G 升级指南](./docs/en/upgrade/sim7670g/sim7670g_upgrade.md)**
- 🔧 **[SIM7000G 升级指南](./docs/en/esp32/sim7000-esp32/upgrade/sim7000_upgrade.md)**
- 🔧 **[SIM7080G 升级指南](./docs/en/esp32s3/sim7080-s3-standard/upgrade/README.MD)**
- 🔧 **[SIM7600X 升级指南](./docs/en/esp32/sim7600-esp32/upgrade/sim7600_upgrade.md)**

## 型号对比

- ⁉️ **[不同版本和型号之间的区别](./docs/model_comparison.md)**

## 模块固件 Bug 汇总

- 🐞 **[模块固件 Bug 汇总](./docs/simcom_firmware_bug.md)**

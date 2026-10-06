<div align="center" markdown="1">
  <img src="../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo Standard Series🌟</h1>

<div align="center">

[English](../standard_series_comparison.md) | [中文](./standard_series_comparison_cn.md)

</div>

---

# LilyGo Standard系列比较

## 概述

本文档详细介绍LilyGo Standard系列开发板的共同特性与差异，帮助用户选择最适合的型号。

Standard系列是LilyGo推出的基于ESP32-S3的蜂窝物联网开发板，具有统一的硬件设计和引脚布局，支持多种蜂窝模块。

## Standard系列产品列表

| 产品型号               | 蜂窝模块      | 深度睡眠电流 |
| ---------------------- | ------------- | ------------ |
| T-A7670X-S3-Standard   | A7670X        | 314uA        |
| T-SIM7670G-S3-Standard | SIM7670G      | 147uA        |
| T-SIM7000G-S3-Standard | SIM7000G      | 166uA        |
| T-SIM7080G-S3-Standard | SIM7080G      | 128uA        |
| T-SIM7600G-S3-Standard | SIM7600G-H R2 | 128uA        |

## 共同特性

所有Standard系列产品共享以下特性：

### 硬件平台
- **主控芯片**: ESP32-S3-WROOM-1 (NR16R2)
- **Flash**: 16MB (Quad-SPI)
- **PSRAM**: 2MB (Quad-SPI)

### 功能特性
- ✅ QWIIC接口 (I2C/UART)
- ✅ 无缝电源切换 (USB-C/电池/太阳能)
- ✅ GNSS路由到SOC
- ✅ eSIM焊盘支持
- ✅ BMS电池管理系统
- ✅ 摄像头接口 (24 Pin FPC)
- ✅ 引脚兼容设计
- ✅ 板载2W(4欧姆)音频放大器(A7670X系列)

### 电气参数
| 参数             | 规格        |
| ---------------- | ----------- |
| USB-C输入电压    | 4.5V ~ 5.5V |
| VBUS引脚输入电压 | 4.5V ~ 5.5V |
| 太阳能输入电压   | 5V ~ 6V     |
| 充电最大电流     | 500mA       |
| 电池电压         | 3.7V        |
| 电池类型         | 仅限单节可充电锂离子/锂聚合物（Li-ion/LiPo）电池（充满电压 4.2 V） |
| 电池座电压范围   | 3.4V ~ 4.3V |

> \[!IMPORTANT]
>
> 请勿在这些设备中使用或充电磷酸铁锂（LiFePO4）电池，或任何充满电压不是 4.2 V 的电池；这些设备仅支持充满电压为 4.2 V 的单节可充电锂离子/锂聚合物电池。

### 接口
- JST 2.0mm 太阳能接口
- 24 Pin 0.5mm FPC摄像头接口
- QWIIC I2C接口
- QWIIC UART/I2C接口
- JST 1.0mm 扬声器接口 (部分型号)
- JST 1.0mm 麦克风接口 (部分型号)
- JST 1.0mm RTC电池接口 (部分型号)

### 按钮
- BOOT: 自定义功能/下载模式
- RST: 复位按钮
- SBOOT: 模块升级模式

### 天线接口
- LTE主天线接口
- GNSS有源天线接口

### LED指示灯
- MODEM STATE (红色)
- MODEM NET (红色)
- CHARGE LED (红色)
- CHARGE DONE LED (绿色)

## 主要差异

### 1. 蜂窝模块对比

| 特性     | A7670X | SIM7670G | SIM7000G  | SIM7080G | SIM7600G-H R2 |
| -------- | ------ | -------- | --------- | -------- | ------------- |
| GPS      | ✅*     | ✅        | ✅         | ✅        | ✅             |
| 电话通话 | ✅*     | ❌        | ❌         | ❌        | ✅             |
| SMS      | ✅*     | ✅**      | 仅GSM(2G) | ❌        | ✅             |
| LTE-FDD  | ✅      | ✅        | ✅         | ✅        | ✅             |
| LTE-TDD  | ❌      | ✅        | ❌         | ❌        | ✅             |
| WCDMA    | ❌      | ❌        | ❌         | ❌        | ✅             |
| GSM      | ✅      | ❌        | ✅         | ❌        | ✅             |
| Cat-M    | ❌      | ❌        | ✅         | ✅        | ❌             |
| Cat-NB   | ❌      | ❌        | ✅         | ✅        | ❌             |

*取决于具体模块版本

**需要运营商基站支持SMS Over SGS服务

### 2. GNSS PPS支持

| 产品型号               | GNSS PPS |
| ---------------------- | -------- |
| T-A7670X-S3-Standard   | ✅        |
| T-SIM7670G-S3-Standard | ✅        |
| T-SIM7000G-S3-Standard | ❌        |
| T-SIM7080G-S3-Standard | ❌        |
| T-SIM7600G-S3-Standard | ❌        |

### 3. 频段支持

#### T-A7670X-S3-Standard
根据具体模块版本支持不同频段：
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

### 4. GPS天线电源控制

不同型号使用不同的AT命令控制GPS天线电源：

| 产品型号               | GPIO      | 启用命令                      | 禁用命令                      |
| ---------------------- | --------- | ----------------------------- | ----------------------------- |
| T-A7670X-S3-Standard   | 1         | `AT+CGDRT=1,1; AT+CGSETV=1,1` | `AT+CGDRT=1,1; AT+CGSETV=1,0` |
| T-SIM7670G-S3-Standard | 1         | `AT+CGDRT=1,1; AT+CGSETV=1,1` | `AT+CGDRT=1,1; AT+CGSETV=1,0` |
| T-SIM7000G-S3-Standard | 48        | `AT+CGPIO=0,48,1,1`           | `AT+CGPIO=0,48,1,0`           |
| T-SIM7080G-S3-Standard | 5         | `AT+SGPIO=0,5,1,1`            | `AT+SGPIO=0,5,1,0`            |
| T-SIM7600G-S3-Standard | AUX Power | `AT+CVAUXV=2800; AT+CVAUXS=1` | `AT+CVAUXS=0`                 |

> \[!IMPORTANT]
>
> A7670G+GPS 使用外置 GPS 模块，只能使用 [S3_StandardSeries_External_GPS_Shield Example](../../../../examples/S3_StandardSeries_External_GPS_Shield/S3_StandardSeries_External_GPS_Shield.ino)示例.其他 GPS 示例无法使用。
>

### 5. Arduino IDE配置

在Arduino IDE中使用时，需要在`utilities.h`文件中取消注释对应的宏定义：

| 产品型号               | 宏定义                            |
| ---------------------- | --------------------------------- |
| T-A7670X-S3-Standard   | `#define LILYGO_A7670X_S3_STAN`   |
| T-SIM7670G-S3-Standard | `#define LILYGO_SIM7670G_S3_STAN` |
| T-SIM7000G-S3-Standard | `#define LILYGO_SIM7000G_S3_STAN` |
| T-SIM7080G-S3-Standard | `#define LILYGO_SIM7080G_S3_STAN` |
| T-SIM7600G-S3-Standard | `#define LILYGO_SIM7600X_S3_STAN` |

## 选型建议

### 需要电话通话功能
- **T-A7670X-S3-Standard**: 支持电话通话（取决于模块版本）
- **T-SIM7600G-S3-Standard**: 支持电话通话（需要音频扩展包）

### 需要低功耗应用
- **T-SIM7080G-S3-Standard**: 深度睡眠电流最低（128uA）
- **T-SIM7600G-S3-Standard**: 深度睡眠电流最低（128uA）

### 需要Cat-M/NB-IoT支持
- **T-SIM7000G-S3-Standard**: 支持Cat-M和Cat-NB
- **T-SIM7080G-S3-Standard**: 支持Cat-M和Cat-NB

### 需要全球频段支持
- **T-SIM7670G-S3-Standard**: 支持最广泛的LTE频段
- **T-SIM7600G-S3-Standard**: 支持LTE、WCDMA和GSM

### 需要GNSS PPS功能
- **T-A7670X-S3-Standard**: 支持GNSS PPS
- **T-SIM7670G-S3-Standard**: 支持GNSS PPS

## 资源链接

各型号详细文档：
- [T-A7670X-S3-Standard](../en/esp32s3/a7670x-s3-standard/README.MD)
- [T-SIM7670G-S3-Standard](../en/esp32s3/sim7670g-s3-standard/README.MD)
- [T-SIM7000G-S3-Standard](../en/esp32s3/sim7000g-s3-standard/README.MD)
- [T-SIM7080G-S3-Standard](../en/esp32s3/sim7080-s3-standard/README.MD)
- [T-SIM7600G-S3-Standard](../en/esp32s3/sim7600g-s3-standard/README.MD)

硬件资源：
- [原理图](../../docs/schematic/standard/)
- [3D模型](../../docs/dimensions/Standard/)
- [天线规格](../../docs/datasheet/)

## 常见问题

### 所有Standard系列的引脚布局是否相同？
是的，所有Standard系列产品都使用相同的引脚布局，可以相互兼容。

### 如何确定我的模块具体版本？
发送AT命令`AT+SIMCOMATI`可以返回固件版本和硬件版本。

### 深度睡眠电流测试方法是什么？
深度睡眠电流测试记录可以在[DeepSleep.ino](../examples/DeepSleep/DeepSleep.ino)中找到。

### 是否可以使用其他GPS天线？
外部GPS天线必须是支持3.3V供电的有源GPS天线。例如，[MK-76](https://www.rfmw.com/datasheets/sanav/mk-76.pdf)支持2.5-5.5V，兼容大多数有源GPS天线。

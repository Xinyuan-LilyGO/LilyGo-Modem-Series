<div align="center" markdown="1">
  <img src="../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟Sim Shield 使用指南🌟</h1>

<div align="center">

[English](../../en/SimshieldUsageGuide/README.md) | [中文](./README.md)

</div>

---

* SimShield 是 Sim 系列的扩展板，包含三路电流检测、LoRa 收发器和宽范围直流输入。它支持全系列 LilyGo T-Sim 扩展板。

> \[!IMPORTANT]
>
> 警告：上电时必须检查跳线帽和拨码开关。
> 选择错误可能导致损坏
>

### ⚡ 电气参数

| 特性                                | 详情                       |
| ----------------------------------- | -------------------------- |
| ⚡DC 接口允许输入电压                | 7~36V                      |
| ⚡电池接口允许输入电压               | 4.2V                       |
| 🔋电池类型                           | 仅限单节可充电锂离子/锂聚合物（Li-ion/LiPo）电池（充满电压 4.2 V） |
| ⚡充电电流                           | 由主板提供                 |
| ⚡+5V                                | 最大电流可达 2A            |
| ⚡+3V3                               | 由主板提供                 |

> \[!IMPORTANT]
>
> 请勿在本设备中使用或充电磷酸铁锂（LiFePO4）电池，或任何充满电压不是 4.2 V 的电池；本设备仅支持充满电压为 4.2 V 的单节可充电锂离子/锂聚合物电池。

* 建议不要将 +3V3 引脚连接到电流超过 100mA 的外设，因为不同主板提供的电流不同。

## SIM7000G/A7670X/A7608X ESP32

![SIM7000_A7608_A7670_ESP32](../../en/SimshieldUsageGuide/images/SIM7000_A7608_A7670_ESP32.png)

1. **J25** 短接 **IO** -> **LP2**
2. **J21** 短接 **RP1** -> **5V**
3. **SW3** 拨到 **ON**，其余 **SW1、SW2 和 SW4** 不得处于 ON 位置。

### 适用型号

1. [SIM7000G-ESP32 版本](https://lilygo.cc/products/t-sim7000g?_pos=1&_sid=d79d65953&_ss=r)
2. [A7608X-ESP32 版本](https://lilygo.cc/products/t-a7608e-h?variant=43275846090933)
3. [A7670X-ESP32 版本](https://lilygo.cc/products/t-sim-a7670e?_pos=1&_sid=f2986df37&_ss=r&variant=42534734495925)

> \[!IMPORTANT]
>
> A7670X/A7608X 主板需要拆除电阻才能使用 SimShield。请参阅此链接了解[如何拆除电阻](https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/issues/160#issuecomment-2409860411)
>
> SIM7000G 没有此限制。
>

### 引脚图

| SIM7000G/A7670X/A7608X ESP32 | GPIO |
| ---------------------------- | ---- |
| SIMSHIELD_MOSI               | 23   |
| SIMSHIELD_MISO               | 19   |
| SIMSHIELD_SCK                | 18   |
| SIMSHIELD_SD_CS              | 32   |
| SIMSHIELD_RADIO_BUSY         | 39   |
| SIMSHIELD_RADIO_CS           | 5    |
| SIMSHIELD_RADIO_IRQ          | 34   |
| SIMSHIELD_RADIO_RST          | 15   |
| SIMSHIELD_RS_RX              | 13   |
| SIMSHIELD_RS_TX              | 14   |
| SIMSHIELD_SDA                | 21   |
| SIMSHIELD_SCL                | 22   |

## SIM7600X ESP32

![SIM7600_ESP32](../../en/SimshieldUsageGuide/images/SIM7600_ESP32.png)

1. **J25** 短接 **IO** -> **BAT**
2. **J21** 短接 **RP2** -> **5V**
3. **SW3** 拨到 **ON**，其余 **SW1、SW2 和 SW4** 不得处于 ON 位置。

> \[!IMPORTANT]
> SIM7600 排针为 15 针，插入位置必须在箭头所指处。
>

### 适用型号

1. [SIM7600X-ESP32 版本](https://lilygo.cc/products/t-sim7600?_pos=1&_sid=7474cd3cf&_ss=r&variant=42358717939893)

### 引脚图

| SIM7600X ESP32       | GPIO | 调制解调器           |
| -------------------- | ---- | -------------------- |
| SIMSHIELD_MOSI       | 23   |                      |
| SIMSHIELD_MISO       | 19   |                      |
| SIMSHIELD_SCK        | 18   |                      |
| SIMSHIELD_SD_CS      | 32   | SIM7600 DTR PIN      |
| SIMSHIELD_RADIO_BUSY | 39   |                      |
| SIMSHIELD_RADIO_CS   | 5    |                      |
| SIMSHIELD_RADIO_IRQ  | 34   | SIM7600 STATUS PIN   |
| SIMSHIELD_RADIO_RST  | 14   |                      |
| SIMSHIELD_RS_RX      | 12   | SIM7600 LED PIN      |
| SIMSHIELD_RS_TX      | 13   |                      |
| SIMSHIELD_SDA        | 21   |                      |
| SIMSHIELD_SCL        | 22   |                      |

> \[!IMPORTANT]
>
> SIM7600 的 DTR (IO32)、STATUS (IO34) 和 ON BOARD LED (IO12) 已重新分配给 SimShield。请不要将这三个 GPIO 用于其他用途。
>
>

## SIM7670G ESP32S3

![SIM7670G_ESP32S3](../../en/SimshieldUsageGuide/images/SIM7670G_ESP32S3.png)

1. **J25** 短接 **IO** -> **LP2**
2. **J21** 短接 **RP1** -> **5V**
3. **SW2** 拨到 **ON**，其余 **SW1、SW3 和 SW4** 不得处于 ON 位置。

### 适用型号

1. [SIM7670G-ESP32S3 版本](https://lilygo.cc/products/t-sim-7670g-s3?_pos=1&_sid=2be878e69&_ss=r)

### 引脚图

| SIM7670G ESP32S3     | GPIO |
| -------------------- | ---- |
| SIMSHIELD_MOSI       | 15   |
| SIMSHIELD_MISO       | 7    |
| SIMSHIELD_SCK        | 16   |
| SIMSHIELD_SD_CS      | 46   |
| SIMSHIELD_RADIO_BUSY | 38   |
| SIMSHIELD_RADIO_CS   | 39   |
| SIMSHIELD_RADIO_IRQ  | 6    |
| SIMSHIELD_RADIO_RST  | 40   |
| SIMSHIELD_RS_RX      | 41   |
| SIMSHIELD_RS_TX      | 42   |
| SIMSHIELD_SDA        | 2    |
| SIMSHIELD_SCL        | 1    |

## A7608X ESP32S3

![A7608_ESP32S3](../../en/SimshieldUsageGuide/images/A7608_ESP32S3.png)

1. **J25** 短接 **IO** -> **LP2**
2. **J21** 不连接
3. **SW2** 拨到 **ON**，其余 **SW1、SW3 和 SW4** 不得处于 ON 位置。

### 适用型号

1. [A7608X-ESP32S3 版本](https://lilygo.cc/products/t-a7608e-h?_pos=1&_sid=e4fd02f43&_ss=r)

### 引脚图

| A7608X ESP32S3       | GPIO |
| -------------------- | ---- |
| SIMSHIELD_MOSI       | 11   |
| SIMSHIELD_MISO       | 10   |
| SIMSHIELD_SCK        | 12   |
| SIMSHIELD_SD_CS      | 45   |
| SIMSHIELD_RADIO_BUSY | 38   |
| SIMSHIELD_RADIO_CS   | 39   |
| SIMSHIELD_RADIO_IRQ  | 9    |
| SIMSHIELD_RADIO_RST  | 40   |
| SIMSHIELD_RS_RX      | 41   |
| SIMSHIELD_RS_TX      | 42   |
| SIMSHIELD_SDA        | 2    |
| SIMSHIELD_SCL        | 1    |

## SIM7080G ESP32S3 PMU 版本

![SIM7080G_ESP32S3](../../en/SimshieldUsageGuide/images/SIM7080G_ESP32S3.png)

1. **J25** 不连接
2. **J21** 不连接
3. **SW4** 拨到 **ON**，其余 **SW1、SW2 和 SW3** 不得处于 ON 位置。

> \[!IMPORTANT]
>
> 1. SIM7080G-ESP32S3 版本未引出电池外部引脚。SimShield 的电池外部功能无法使用。18650 电池座的正极需要焊接至左侧引脚。图片中 +BAT 指向电池正极的焊接方向。
>
> 2. SIM7080G-ESP32S3 版本板载 18650 电池座与 SimShield 冲突。安装前必须拆除电池座。
>
> 3. SIM7080G PMU 版本在排针方面与其他版本不完全兼容。因此，连接到 SIMShield 时，`DC5` 和 `VSYS` 引脚不得连接到 `SIM Shield`；即 `DC5` 和 `VSYS` 引脚必须为空。
>
> 4. SIM7080G PMU 版本未引出 5V 输入引脚。附带的 2.00mm 线需要焊接至下图所示主板上的位置，以便板子接受 5V 电源输入。
>

![H606-SIM7080](../../en/SimshieldUsageGuide/images/H606-SIM7080.png)

### 适用型号

1. [SIM7080G-ESP32S3 版本](https://lilygo.cc/products/t-sim7080-s3?_pos=1&_sid=7d3cc194f&_ss=r)

### 引脚图

| SIM7080G ESP32S3     | GPIO |
| -------------------- | ---- |
| SIMSHIELD_MOSI       | 11   |
| SIMSHIELD_MISO       | 13   |
| SIMSHIELD_SCK        | 12   |
| SIMSHIELD_SD_CS      | 21   |
| SIMSHIELD_RADIO_BUSY | 48   |
| SIMSHIELD_RADIO_CS   | 45   |
| SIMSHIELD_RADIO_IRQ  | 8    |
| SIMSHIELD_RADIO_RST  | 47   |
| SIMSHIELD_RS_RX      | 2    |
| SIMSHIELD_RS_TX      | 1    |
| SIMSHIELD_SDA        | 44   |
| SIMSHIELD_SCL        | 43   |

## SIM7000G/A7670X/SIM7670G/SIM7080G Standard 系列

![SIM7000_A7608_A7670_ESP32](../../en/SimshieldUsageGuide/images/Standard%20Series.png)

1. **J25** 短接 **IO** -> **LP2**
2. **J21** 短接 **RP1** -> **5V**
3. **SW1** 拨到 **ON**，其余 **SW2、SW3 和 SW4** 不得处于 ON 位置。

### 适用型号

1. [即将推出](https://lilygo.cc/)

### 引脚图

| SIM7000G/A7670X/SIM7670G/SIM7080G Standard 系列 | GPIO |
| ------------------------------------------------ | ---- |
| SIMSHIELD_MOSI                                   | 11   |
| SIMSHIELD_MISO                                   | 13   |
| SIMSHIELD_SCK                                    | 12   |
| SIMSHIELD_SD_CS                                  | 37   |
| SIMSHIELD_RADIO_BUSY                             | 15   |
| SIMSHIELD_RADIO_CS                               | 38   |
| SIMSHIELD_RADIO_IRQ                              | 14   |
| SIMSHIELD_RADIO_RST                              | 39   |
| SIMSHIELD_RS_RX                                  | 40   |
| SIMSHIELD_RS_TX                                  | 41   |
| SIMSHIELD_SDA                                    | 3    |
| SIMSHIELD_SCL                                    | 2    |

* Standard 系列无论调制解调器型号如何，都使用相同的 GPIO

# 将电池连接到主板

* 按照下图所示方法短接跳线帽，将外部电池接口路由到主板电池接口并跳过电流检测。

![BATTERY_SOKECT](../../en/SimshieldUsageGuide/images/BATTERY_SOKECT.png)

## 监控电池充放电跳线设置

* 下图中的垂直跳线帽将电池电流路由到 INA3221 通道 2，通过读取 INA3221 传感器可以监控电池充放电电流。**此时不要在压接端子接口上连接任何东西。**
* 如果未连接跳线帽，则监控压接端子接口电流

![Monitor battery charging and discharging jumper](../../en/SimshieldUsageGuide/images/battery_current_detection_mode.png)

## 5V 2.00mm 2Pin 供电接口

* 此端口用于外部供电，无其他功能。
* 您也可以使用相同的 JST 2.0mm 线缆直接连接到主板太阳能端口进行充电，**但请确保 J21 跳线帽未连接**。
* 使用 JST 2.0 线缆充电可减少 SimShield 二极管上的压降。但是，使用 J21 供电会增加直流电源输入压降。如果没有太阳能，将 JST 2.0 端口连接到太阳能输入端口是更好的选择。

## SD 卡接口

* SimShield 重新映射了 SPI 接口。使用 SimShield 后，不要将 SD 卡插入主板。请将 SD 卡插入 SimShield。

## RS485 接口

* RS485 使用硬件自动发送接收控制，建议使用低于 115200 的通信波特率

## I2C 接口

* [0.96 英寸 OLED 显示屏](https://lilygo.cc/products/0-96-inch-oled?_pos=1&_sid=61234aa32&_ss=r)
* I2C 接口适用于连接到常规接口的 OLED 屏幕。请注意 OLED 接口有两种线序。请确保线序正确。请参阅此[链接](https://lilygo.cc/products/0-96-inch-oled?_pos=1&_sid=61234aa32&_ss=r)了解 OLED 接口

## SPI 接口

* SPI 接口引出 SD 卡/无线模块的 SPI 总线接口

## 电流检测

![interface](../../en/SimshieldUsageGuide/images/intervface.png)

* 如果电流检测通道 2 的跳线选择为电池检测通道，则外部接线端子不可用。
* 通道 3 和通道 1 可自由使用。端子的 **IN+** 为电流流入方向，**G** 为负载的 **GND**，**IN-** 为电流从负载流出方向。

## 接口说明

| 名称          | 详情                                         |
| ------------- | -------------------------------------------- |
| INPUT:7~36V   | 直流输入，范围 7 ~ 36 V                      |
| OUTPUT:5V     | 仅在直流输入时才会输出 5V 电压               |
| VBAT:+4.2V-   | 电池输入接口，最大 4.2V                      |
| IN+ G IN- CH2 | 电流检测通道 2                               |
| IN+ G IN- CH3 | 电流检测通道 3                               |
| IN+ G IN- CH1 | 电流检测通道 1                               |

* **电池输入接口与板载 18650 并联。如果连接外部电池，请不要在 18650 插座上安装电池。**
* **电流检测通道 1（如果通过跳线帽连接电池，则此通道不可用）**

## 示例

1. [SimShield_LoRaWAN](../../../examples/SimShield_LoRaWAN/README.MD)
2. [SimShield_LoRaReceive](../../../examples/SimShield_LoRaReceive/SimShield_LoRaReceive.ino)
3. [SimShield_LoRaTransmit](../../../examples/SimShield_LoRaTransmit/SimShield_LoRaTransmit.ino)
4. [SimShieldCurrentSensor](../../../examples/SimShieldCurrentSensor/SimShieldCurrentSensor.ino)
5. [SimShieldFactory](../../../examples/SimShieldFactory/SimShieldFactory.ino)
6. [SerialRS485](../../../examples/SerialRS485/SerialRS485.ino)

## 原理图

[T-SimShield-Rev1.0 原理图](../../../schematic/shield/T-SimShield-Rev1.0.pdf)

## 数据手册

[太阳能电池板规格](./../../../datasheet/3D5ETR00372_233153V01_20250828.pdf)

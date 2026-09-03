<div align="center">

[English](../../../en/esp32s3/a7670x-s3-standard/README.MD) | [中文](./README.MD)

</div>

<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo T-A7670X-S3-Standard🌟</h1>

## 概述

* 本页介绍 `LilyGo T-A7670X-S3-Standard` 相关的硬件参数

### 产品

| Product                   | SOC              | Flash          | PSRAM         |
| ------------------------- | ---------------- | -------------- | ------------- |
| [T-A7670X-S3-Standard][1] | ESP32-S3-WROOM-1 | 16MB(Quad-SPI) | 2MB(Quad-SPI) |

[1]: https://lilygo.cc/products/t-sim-t-a-series-standard-edition?variant=52513685471413


### 模块差异

| 型号           | GPS | 电话 | SMS | Frequency band                                                                                                     |
| --------------- | --- | ---------- | --- | ------------------------------------------------------------------------------------------------------------------ |
| A7670E-FASE     | ✅   | ✅          | ✅   | LTE-FDD:B1/B3/B5/B7/B8/B20  GSM:900/1800                                                                           |
| A7670SA-FASE    | ✅   | ✅          | ✅   | LTE-FDD:B1/B2/B3/B4/B5/B7/B8/B28/B66  GSM:850/900/1800/1900                                                        |
| A7670E-LNXY-UBL | ❌   | ❌          | ❌   | LTE-FDD:B1/B3/B5/B7/B8/B20                                                                                         |
| A7670E-LNMV     | ❌   | ❌          | ❌   | LTE-FDD:B1/B3/B5/B7/B8/B20                                                                                         |
| A7670SA-LASE    | ❌   | ✅          | ✅   | LTE-FDD:B1/B2/B3/B4/B5/B7/B8/B28/B66  GSM:850/900/1800/1900                                                        |
| A7670SA-LASC    | ❌   | ✅          | ✅   | LTE-FDD:B1/B2/B3/B4/B5/B7/B8/B28/B66  GSM:850/900/1800/1900                                                        |
| A7670G-LLSE     | ❌   | ✅          | ✅   | LTE-FDD:B1/B2/B3/B4/B5/B7/B8/B20/B28/B66  LTE-TDD:B34/B38/B39/B40/B41 GSM:850/900/1800/1900                        |
| A7670G-LABE     | ❌   | ✅          | ✅   | LTE-FDD:B1/B2/B3/B4/B5/B7/B8/B12/B13/B18/B19/B20/B25/B26/B28/B66 LTE-TDD:B34/B38/B39/B40/B41 GSM:850/900/1800/1900 |
| A7670E-LASE     | ❌   | ✅          | ✅   | LTE-FDD:B1/B3/B5/B7/B8/B20  GSM:900/1800                                                                           |

> \[!IMPORTANT]
> 如何检查模块的具体型号版本？发送 AT+SIMCOMATI 可以返回使用的固件版本和硬件版本。
>
> 请注意，GNSS IPEX 天线连接器是否在 PCB 上取决于实际的模块版本。 The A7670G modem does not have internal GPS functionality, regardless of whether GPS is included in your order. If you purchased the A7670G with GPS, you will need to use an external GPS module.
> A7670G+GPS orders use an external GPS module and can only use [S3_StandardSeries_External_GPS_Shield Example](../../../../examples/S3_StandardSeries_External_GPS_Shield/S3_StandardSeries_External_GPS_Shield.ino). Other GPS examples cannot be used.
> 
> The image below clearly shows that if a GPS module is included on the side, then it's a version with an external GPS module.

<img src="../../../../images/product/png/H799-01-T-A7670X-S3-Standard-GPS.png" alt="T-A7670X-S3-Standard-GPS" width="320" style="border: 0;"/>


### PlatformIO 快速入门

1. 安装 [Visual Studio Code](https://code.visualstudio.com/) 和 [Python](https://www.python.org/)
2. 在 `Visual Studio Code` 扩展中搜索 `PlatformIO` 插件并安装。
3. 安装完成后，需要重启 `Visual Studio Code`
4. 重启 `Visual Studio Code` 后，选择左上角的 `文件` -> `打开文件夹` -> 选择 `LilyGo-Modem-Series` 目录
5. 等待第三方依赖库安装完成
6. 点击 `platformio.ini` 文件，在 `platformio` 栏中
7. Cancel the `;` symbol in front of the line `default_envs = T-A7670X-S3-Standard` and use `T-A7670X-S3-Standard` as the default environment
8. 取消注释 `src_dir = xxxx` 中的一行，确保只有一行有效。例如，要启用 `src_dir = examples/ATdebug`，删除前面的 `;` 符号并保存文件。现在将编译 ATDebug 示例。
9. 点击左下角的 (✔) 符号进行编译
10. Connect the board to the computer `ESP-USB` , `Modem-USB` is used for module firmware upgrade
11. 点击 (→) 上传固件
12. 点击（插头符号）监控串口输出
13. 如果无法写入，或 USB 设备持续闪烁，请查看下方的 **常见问题**

### Arduino IDE 快速入门

1. 安装 [Arduino IDE](https://www.arduino.cc/en/software)
2. 安装 [Arduino ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
3. 将 `lib` 目录中的所有文件夹复制到 `Sketchbook location` 目录。如何找到您自己的库位置，[请查看这里](https://support.arduino.cc/hc/en-us/articles/4415103213714-Find-sketches-libraries-board-cores-and-other-files-on-your-computer)
    * Windows: `C:\Users\%USERNAME%\Documents\Arduino\libraries`
    * MacOS: `$HOME/Documents/Arduino/libraries`
    * Linux: `$HOME/Arduino/libraries`
4. 打开相应的示例
    * 打开下载的 `LilyGo-Modem-Series`
    * 打开 `examples`
    * 选择示例文件并打开以 `ino` 结尾的文件
5. 在 Arduino IDE 中，在工具项目中选择相应的开发板，点击下方列表中的相应选项进行选择

    | 名称                                 | 值                               |
    | ------------------------------------ | ----------------------------------- |
    | Board                                | **ESP32S3 Dev Module**              |
    | Port                                 | 您的端口                           |
    | USB CDC On Boot                      | Enable                              |
    | CPU Frequency                        | 240MHZ(WiFi)                        |
    | Core Debug Level                     | None                                |
    | USB DFU On Boot                      | Disable                             |
    | Erase All Flash Before Sketch Upload | Disable                             |
    | Flash Mode                           | QIO 80Mhz                           |
    | Flash Size                           | **16MB(128Mb)**                     |
    | Arduino Runs On                      | Core1                               |
    | USB Firmware MSC On Boot             | Disable                             |
    | Partition Scheme                     | **16M Flash (3MB APP/9.9MB FATFS)** |
    | PSRAM                                | **QSPI PSRAM**                      |
    | Upload Speed                         | 921600                              |
    | Programmer                           | **Esptool**                         |

     * `Partition Scheme` 请根据实际应用选择。例如选择 **16M Flash (3MB APP/9.9MB FATFS)** , 更多分区方案请查看[这里](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/partition-tables.html)

6. In the open sketch, select the `utilities.h` file and uncomment the line `// #define LILYGO_A7670X_S3_STAN`. Delete the `//` and save the file to use this board as the default configuration.

   ![board_select](../../../static/board_select.jpg)

7. 上传 sketch

> \[!IMPORTANT]
>
> 1. 无法上传任何代码？请查看下方的常见问题
> 2. 打开 Arduino IDE 时，会提示有新的库可以更新。请点击不更新。更新后无法保证能够编译、运行等。请确保开发板正常运行后再决定是否更新。要知道由于库的差异，更新后可能会出现问题，或者默认配置（如 TinyGSM）将被覆盖。
> 3. 如果更新后运行异常，请按照 Arduino 快速入门第 3 条删除 libraries 中的目录，并将 lib 中的文件夹重新拖入 libraries 目录。

### 📍 Pins Map

| 名称              | GPIO NUM             | 可用 |
| ----------------- | -------------------- | ---- |
| Modem TX          | 4                    | ❌    |
| Modem RX          | 5                    | ❌    |
| Modem RING        | 6                    | ❌    |
| Modem DTR         | 7                    | ❌    |
| Modem PWRKEY      | 46                   | ❌    |
| GPS RX            | 48                   | ❌    |
| GPS TX            | 45                   | ❌    |
| Modem RTS*        | 48                   | ❌    |
| Modem CTS*        | 45                   | ❌    |
| GPS PPS           | 17                   | ❌    |
| GPS Shield Wakeup | 0                    | ❌    |
| 电池 ADC 引脚   | 8                    | ❌    |
| 太阳能 ADC 引脚     | 18                   | ❌    |
| SD SCK            | 12                   | ❌    |
| SD MISO           | 13                   | ❌    |
| SD MOSI           | 11                   | ❌    |
| SD CS             | 10                   | ❌    |
| Power Save Mode   | 42                   | ❌    |
| Camera XCLK       | 21                   | ❌    |
| Camera SIOD       | 1  (default pull-up) | ❌    |
| Camera SIOC       | 41 (default pull-up) | ❌    |
| Camera VSYNC      | 9                    | ❌    |
| Camera HREF       | 14                   | ❌    |
| Camera PCLK       | 37                   | ❌    |
| Camera Y9         | 40                   | ❌    |
| Camera Y8         | 39                   | ❌    |
| Camera Y7         | 38                   | ❌    |
| Camera Y6         | 36                   | ❌    |
| Camera Y5         | 16                   | ❌    |
| Camera Y4         | 47                   | ❌    |
| Camera Y3         | 15                   | ❌    |
| Camera Y2         | 35                   | ❌    |
| Camera RESET      | See the tips below   | ❌    |
| Camera PWD        | See the tips below   | ❌    |
| Default SDA       | 3                    | ✅️    |
| Default SCL       | 2                    | ✅️    |

> \[!TIP]
>
> [ESP32-S3 Consolidated Pin Overview](https://documentation.espressif.com/esp32-s3_datasheet_en.pdf)
>
> Input/Output: Any GPIO not listed can be used as input/output.
>
> ADC Pins: Only pins 1-21 are allowed as ADC inputs.
>
> IO0/IO3/IO45/IO46 are Strapping Pins; their use is limited. Please see the **Strapping Pins** section of the [online documentation](https://documentation.espressif.com/esp32-s3_datasheet_en.pdf) for details.
>

| A7670G + L76K GPS Version Pin Maps   | GPIO |
| ------------------------------------ | ---- |
| GNSS WakeUp(A7670G-GPS Version Only) | 0    |
| GPS RX                               | 48   |
| GPS TX                               | 45   |
| GPS PPS                              | 17   |

* A7670G does not have GNSS functionality. If you purchase the version with GPS functionality, it's an external GPS version. The GPS pin is the same as the modem GNSS pin, except it also has a wakeup pin.
* **GNSS WakeUp** : Low level enters Standby mode, high level enters operating mode.
* **GNSS PPS**: 1 pulse per second

### 模块引脚

| 名称                         | GPIO NUM | 使能电平 | AT 命令                     |
| ---------------------------- | -------- | ------------ | ------------------------------ |
| GPS Ant Power Enable         | 1        | High         | `AT+CGDRT=1,1 ; AT+CGSETV=1,1` |
| Audio power amplifier Enable | 3        | High         | `AT+CGDRT=3,1 ; AT+CGSETV=3,1` |

> [!IMPORTANT]
> 🚨 **使用 GPS/GNSS 前必须先开启有源天线供电！** A7670X Standard 使用模块 GPIO1 控制天线电源；请先发送 `AT+CGDRT=1,1; AT+CGSETV=1,1` 开启供电，否则将无法定位或无法获得 GPS fix。不使用 GPS/GNSS 时，可发送 `AT+CGDRT=1,1; AT+CGSETV=1,0` 关闭天线供电以降低功耗。

* The `Power Save Mode pin` is used to set the power capability of the power supply. Setting it to HIGH enables maximum power output. Setting it to LOW reduces current consumption.
* If a camera is connected externally, there will be no free GPIO. If the camera is not used, the camera's GPIO can be used for other purposes.
* `SDA`, `SCL` can only be used as I2C function, not as other functions
* `GPS Shield Wakeup Pin` is only used when an external GPS module is connected. Otherwise, it is idle. It is not recommended to use this GPIO. This IO is connected only when using `A7670G + L76K GPS`, otherwise it is not connected
* The camera must be powered on to be detected, otherwise the camera cannot be used. For how to turn it on, please refer to the Camera example.
* Modem RTS/Modem CTS are not connected by default. They are connected to the GPS RX/TX of the Modem by default. If you need to use them, you need to short-circuit the RTS/CTS short-circuit pads on the back of the PCB, and then separate the GPS TX and RX pads.
* `Camera RESET` : To maximize GPIO usage, no GPIO is assigned to the camera reset pin, so a power cycle is used to reset the camera.
The power-on sequence is: power on all cameras -> power off all cameras -> delay 300 milliseconds -> power on all cameras -> delay 100 milliseconds.
* `Camera PWD` : In order to maximize the use of GPIO, all GPIOs are not assigned to the camera PWD Pin. When the camera is not in use, you only need to turn off the camera power to completely turn off the power supply of the camera.
* `Camera Pins` : if the camera is not used, then all the pins assigned to the camera by default can be freely allocated and used without restrictions
* `Audio power amplifier Enable`: When using audio playback or making calls, you must send `AT+CGDRT=3,1; AT+CGSETV=3,1` to set the modem's GPIO1 to a high level. When not in use, you can send `AT+CGDRT=3,1; AT+CGSETV=3,0` to turn off the power amplifier and save power.

### ⚡ Electrical parameters

| 特性                        | 详情   |
| ------------------------------- | --------- |
| 🔗USB-C input voltage range      | 4.5V~5.5V |
| 🔗VBUS Pin input voltage range   | 4.5V~5.5V |
| ⚡太阳能输入电压            | 5 ~ 6V    |
| ⚡USB-C/太阳能充电最大电流 | 500mA     |
| 🔋电池电压                | 3.7V      |
| 🔋Battery socket voltage range   | 3.4~4.3V  |
| 📍**VBUS** ( 排针)         | 5V        |
| 📍**VBAT** ( 排针)         | 4.2V      |

* 电池供电的最低电压取决于电池的放电能力。使用稳压器测试的最低供电电压可低至 2.7V（由于稳压器的低压稳定性）
* VBUS 引脚与 USB-C 端口在同一条线上。连接 USB-C 时，VBUS 引脚也会有电压。VBUS 引脚只能用于外部电源输入，不会向外供电。

> \[!TIP]
>
> 1. 板载 JST2.0 接口仅用于连接太阳能板为电池充电，不能通过此接口为开发板供电
> 2. 建议使用输出电压为 6V 或 5V、功率约 5-10W 的太阳能板。太阳能只能为电池充电。没有电池时，太阳能板无法供电。
> 请注意，这只是一个建议。不一定要使用 5-10W 的太阳能板。1W 也可以使用。
> 太阳能板的大小决定了太阳能充电的电流和速度。请注意，根据环境不同，
> 每天的日照时间可能不超过一小时。此时，如果太阳能板太小且光线不足，则无法充电。
> 3. 将 VBUS 引脚连接到 USB-C 电源。如果 USB-C 存在，VBUS 电压等于 USB-C 电压。如果 USB-C 不存在，VBUS 上没有电压。
> 4. 将 VBAT 引脚连接到电池正极。此引脚可用于直接将外部电池连接到 VBAT 引脚。使用外部电池时，除非电池参数与外部电池相似，否则最好不要将电池连接到开发板的 18650 电池座。连接到 VBAT 引脚的电池可以使用板载充电管理进行充电。
> 5. VBUS 引脚是除电池外唯一为开发板供电的接口；没有其他方式。
> 6. USB/VBUS 引脚输入必须能够提供至少 2A 的峰值电流，且电压不得低于 5V，否则将触发低压自动关机。

### ⚡Battery Protector Description

| 特性                | 详情  |
| ----------------------- | -------- |
| 过压阈值  | 4.30V    |
| 欠压阈值 | 2.4V     |
| Over-Charge Current     | 3.6A     |
| 过放电流  | 4.6A     |
| Short-Circuit Current   | 2 × 4.6A |

> \[!IMPORTANT]
> 请注意，连接 18650 电池时开发板不会开机。要激活电池供电，可以使用以下方法激活 BMS。
>
> 方法：插入标记为 ESP-USB 的 USB-C 端口。请注意，Modem-USB 端口不会为开发板供电或充电。
>
> 请注意，即使电源开关关闭，您仍需要按照上述方法激活 BMS 才能为开发板供电。
> 如果您短暂关闭电源开关，重新打开也会重新连接电池电源，无需重新连接 USB 端口来激活 BMS。

### 连接器说明

| 按钮                     | 功能                      | 位置   |
| -------------------------- | ----------------------------- | ---------- |
| JST 1.0mm `SPEK`           | Connect speakers              | PCB Bottom |
| JST 1.0mm `MIC`            | Connect condenser microphone  | PCB Bottom |
| JST 1.0mm `RTC`            | Connect 3~3.3V button battery | PCB Bottom |
| JST 2.0mm `Solar`          | 连接 5~6V 太阳能板 | PCB Top    |
| 24 Pin 0.5mm FPC Connector | 连接 OV2640/OV5640 摄像头  | PCB Top    |
| QWIIC                      | I2C 接口                 | PCB Bottom |
| QWUART or QWIIC            | UART or I2C 接口         | PCB Bottom |

* 摄像头型号支持 esp32 平台支持的摄像头
* `QWIIC I2C` : Fixed to I2C interface, cannot be changed to other functions , Examples see [QWIIC_I2C_Scan.ino](../../../../examples/QWIIC_I2C_Scan/QWIIC_I2C_Scan.ino)
* `QWIIC UART` : The default is ESP serial output, which can also be changed to the second I2C interface, I2C Example see [QWIIC_I2C_Scan.ino](../../../../examples/QWIIC_I2C_Scan/QWIIC_I2C_Scan.ino) / , Uart example see [QWIIC_UART_loopback.ino](../../../../examples/QWIIC_UART_loopback/QWIIC_UART_loopback.ino)
* `JST 2.0mm Solar` : This is the solar panel voltage input interface. This interface is only used as a solar or external power charging interface. It cannot be used to provide power to the motherboard after removing the battery.
* `JST 1.0mm SPEK`: This is the external speaker interface, the maximum output power of this interface is 8 ohms 1W
* `JST 1.0mm MIC`: This is an external condenser microphone interface for calls. The condenser microphone is directly connected to the modem. Only condenser microphones can be used, not digital microphones.
* `JST 1.0mm RTC`: This is the GPS backup power battery interface. If you do not connect this battery, the GPS will not have the hot start function. Connecting a battery to this interface will enable the GPS hot start function.

### 按钮说明

| 按钮               | 功能                            | 位置   |
| -------------------- | ----------------------------------- | ---------- |
| BOOT  (ESP32S3 back) | 可自定义功能/下载模式 | PCB Bottom |
| RST   (ESP32S3 back) | 复位设备按钮                | PCB Bottom |
| SBOOT(Near to modem) | 模块升级模式                  | PCB Bottom |

* **RST** and **BOOT** Located on the bottom of the ESP32 module
* **SBOOT** is located on the back near the modem module
* Press and hold the `BOOT` button before powering on. The board is now in waiting mode for downloading.
* Before powering on, keep the `SBOOT` button pressed to put the modem into firmware update mode.
* 以上命名方式以开发板丝印为准

### 天线说明

| 名称 | 功能                     |
| ---- | ---------------------------- |
| LTE  | LTE 主天线接口   |
| GNSS | GPS 有源天线接口 |

* 使用时，只需将佩戴的 LTE 天线连接到 LTE IPEX 第一代接口。AUX 天线不需要连接。
* 以上命名方式以开发板丝印为准

### LED 说明

| 功能        | 颜色                            | 状态                                                                  |
| --------------- | -------------------------------- | ---------------------------------------------------------------------- |
| 模块状态     | RED   (Near the modem)           | Startup:ON                                                             |
| 模块网络       | RED   (Near the modem)           | Network status indicator                                               |
| GPS PPS LED     | RED  (Near the modem)            | Starting:ON,Startup completed:OFF,Position fix:Flashes once per second |
| 充电 LED      | RED  (Near the battery switch)   | Charging:ON  Charging complete:OFF                                     |
| 充电完成 LED | GREEN  (Near the battery switch) | Charging:OFF  Charging complete:ON                                     |

* 未连接电池时 `CHARGE DONE LED` 保持常亮
* 模块状态灯和网络状态灯无法关闭

### eSIM

<img src="../../../../images/product/png/eSIM-Chip.png" alt="eSIM" width="480" style="border: 0;"/>

<img src="../../../../images/product/png/eSIM.png" alt="eSIM" width="480" style="border: 0;"/>

* eSIM 采用 QFN5*6-8 封装，支持 1.8V/3.3V。默认不安装，需要焊接。

### 资源

* [GPS 天线](../../../../datasheet/GPS%20Antenna%20Specifications.pdf)
* [LTE 天线](../../../../datasheet/LTE%20Antenna%20Specifications.pdf)
* [T-A7670X-S3-Standard 原理图](../../../../schematic/standard/T-A7670X-S3-Standard_Rev1.0.pdf)
* [SIMCOM 官方 A7670X 全部数据手册](https://cn.simcom.com/product/A7670X.html)
* [For A7670X series documentation，请访问 datasheet 目录。](../../../../datasheet/A7670X/)
* [L76K GPS 模块数据手册](../../../../datasheet/GPS/)
* [3D 模型](../../../../dimensions/Standard/T-A7670X-S3-Standard.7z)
* [尺寸 svg](../../../../dimensions/Standard/T-SIM7060G%20and%20A7670-S3-Standard.svg)

### 常见问题

* **升级模块固件**
  1. [T-A76XX 升级文档](../../../../docs/update_fw.md) / [Video](https://youtu.be/AZkm-Z7mKn8)

* **无法检测到 SIM 卡？**
   1. 需要先将 SIM 卡插入开发板，然后再开机检测 SIM 卡。如果顺序颠倒，将报告无法检测到 SIM 卡。

* **无法上传任何 sketch，请手动进入上传模式。**
   1. 通过 USB 线连接开发板
   2. Press and hold the **BOOT** button , While still pressing the **BOOT** button
   3. Press **RST** button
   4. Release the **RST** button
   5. Release the **BOOT** button
   6. 上传 sketch

* **板载开关的作用**
  1. 使用内部电池组时，开关将正常工作以控制开发板的电源开/关。但是，如果使用外部电池组并连接到 VBAT 引脚，开关将被旁路，这意味着唯一的关机方式是断开电池。
  2. 开关仅用于电池供电，插入 USB 时无效
  3. 要激活电池供电，请查看上方的 `电池保护说明`。

* **关于 VBUS 引脚**
  1. VBUS 引脚和 USB-C 在同一条线上。只有连接 USB-C 时，VBUS 才有电压
  2. 仅连接电池时，VBUS 没有电压输出
  3. 如果想连接外部电源而不连接 USB-C，VBUS 引脚是唯一的电压输入引脚。请注意，VBUS 引脚的最大输入为 5V，不要超过 5V

* 可以使用其他 GPS 天线吗？
  1. 外部 GPS 天线必须是 3.3V 供电的有源 GPS 天线。 For example, the [MK-76](https://www.rfmw.com/datasheets/sanav/mk-76.pdf) 支持 2.5-5.5V，兼容。大多数有源 GPS 天线支持 2.5-5.5V 供电。详情请参考 GPS 天线数据手册。

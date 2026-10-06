<div align="center">

[English](../../../en/esp32/pcie-series-esp32/README.MD) | [中文](./README.MD)

</div>

<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo PCI-E 系列 ESP32 版本🌟</h1>

## 概述

* 本页面介绍"LilyGo PCI-E 系列 ESP32 版本"

### 产品

| Product                             | SOC            | Flash          | PSRAM         |
| ----------------------------------- | -------------- | -------------- | ------------- |
| [T-PCIE Main board 4MB Version][1]  | ESP32-WROVER-E | 4MB(Quad-SPI)  | 8MB(Quad-SPI) |
| [T-PCIE Main board 16MB Version][2] | ESP32-WROVER-E | 16MB(Quad-SPI) | 8MB(Quad-SPI) |

[1]: https://lilygo.cc/products/a-t-pcie?variant=43043718725813
[2]: https://lilygo.cc/products/a-t-pcie?variant=42335921832117

### PlatformIO 快速入门

1. 首次使用需安装 **CH9102 USB 桥接** 驱动。
   * [Windows](https://www.wch-ic.com/downloads/CH343SER_ZIP.html)
   * [Mac OS](https://www.wch-ic.com/downloads/CH34XSER_MAC_ZIP.html)
2. 安装 [Visual Studio Code](https://code.visualstudio.com/) 和 [Python](https://www.python.org/)
3. 在 `Visual Studio Code` 扩展中搜索 `PlatformIO` 插件并安装。
4. 安装完成后，需要重启 `Visual Studio Code`
5. 重启 `Visual Studio Code` 后，选择左上角的 `文件` -> `打开文件夹` -> 选择 `LilyGo-Modem-Series` 目录
6. 等待第三方依赖库安装完成
7. 点击 `platformio.ini` 文件，在 `platformio` 栏中
8. 取消 `default_envs = T-PCIE-XXXX` 行前面的分号 `;`，并将 `T-PCIE-XXXX` 用作默认环境，名称 **XXXX** 请根据实际版本选择
9. 取消注释 `src_dir = xxxx` 中的一行，确保只有一行有效。例如，要启用 `src_dir = examples/ATdebug`，删除前面的 `;` 符号并保存文件。现在将编译 ATDebug 示例。
10. 点击左下角的 (✔) 符号进行编译
11. 将开发板通过 USB-C 接口连接到电脑。
12. 点击 (→) 上传固件
13. 点击（插头符号）监控串口输出
14. 如果无法写入，或 USB 设备持续闪烁，请查看下方的 **常见问题**

### Arduino IDE 快速入门

1. 首次使用需安装 **CH9102 USB 桥接** 驱动。
   * [Windows](https://www.wch-ic.com/downloads/CH343SER_ZIP.html)
   * [Mac OS](https://www.wch-ic.com/downloads/CH34XSER_MAC_ZIP.html)
2. 安装 [Arduino IDE](https://www.arduino.cc/en/software)
3. 安装 [Arduino ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
4. 将 `lib` 目录中的所有文件夹复制到 `Sketchbook location` 目录。如何找到您自己的库位置，[请查看这里](https://support.arduino.cc/hc/en-us/articles/4415103213714-Find-sketches-libraries-board-cores-and-other-files-on-your-computer)
    * Windows: `C:\Users\%USERNAME%\Documents\Arduino\libraries`
    * MacOS: `$HOME/Documents/Arduino/libraries`
    * Linux: `$HOME/Arduino/libraries`
5. 打开相应的示例
    * 打开下载的 `LilyGo-Modem-Series`
    * 打开 `examples`
    * 选择示例文件并打开以 `ino` 结尾的文件
6. 在 Arduino IDE 中，在工具项目中选择相应的开发板，点击下方列表中的相应选项进行选择

    | 名称                                 | 值                                   |
    | ------------------------------------ | ------------------------------------ |
    | Board                                | **ESP32 Dev Module**                 |
    | Port                                 | 您的端口                             |
    | CPU Frequency                        | 240MHZ(WiFi/BT)                      |
    | Core Debug Level                     | None                                 |
    | Erase All Flash Before Sketch Upload | Disable                              |
    | Events Run On                        | Core1                                |
    | Flash Frequency                      | 80MHZ                                |
    | Flash Mode                           | QIO                                  |
    | Flash Size                           | **4MB(32Mb)**                        |
    | JTAG Adapter                         | Disabled                             |
    | Arduino Runs On                      | Core1                                |
    | Partition Scheme                     | **Huge APP (3MB No OTA/1MB SPIFFS)** |
    | PSRAM                                | **Enable**                           |
    | Upload Speed                         | 921600                               |
    | Programmer                           | **Esptool**                          |

     * `Partition Scheme` 请根据实际应用选择。例如选择 **Huge APP (3MB No OTA/1MB SPIFFS)** , 更多分区方案请查看[这里](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/partition-tables.html)

7. 在打开的ino文件中，选择 `utilities.h` 文件，取消注释 `// #define LILYGO_T_PCIE_XXXX` 这行代码。删除 `//` 并保存文件，即可将此开发板设置为默认配置。名称 **XXXX** 请根据实际版本选择

   ![board_select](../../../static/board_select.jpg)

8. 上传 sketch

> \[!IMPORTANT]
>
> 1. 无法上传任何代码？请查看下方的常见问题
> 2. 打开 Arduino IDE 时，会提示有新的库可以更新。请点击不更新。更新后无法保证能够编译、运行等。请确保开发板正常运行后再决定是否更新。要知道由于库的差异，更新后可能会出现问题，或者默认配置（如 TinyGSM）将被覆盖。
> 3. 如果更新后运行异常，请按照 Arduino 快速入门第 4 条删除 libraries 中的目录，并将 lib 中的文件夹重新拖入 libraries 目录。

### 📍 Pins Map

| 名称                    | GPIO NUM | 可用 |
| ----------------------- | -------- | ---- |
| Modem DC booster enable | 25       | ❌    |
| Modem TX                | 27       | ❌    |
| Modem RX                | 26       | ❌    |
| Modem PWRKEY            | 4        | ❌    |
| Modem DTR               | 32       | ❌    |
| Modem RING              | 33       | ❌    |
| Board LED               | 12       | ❌    |
| PMIC IRQ                | 35       | ❌    |
| PMIC SDA                | 21       | ✅️    |
| PMIC SCL                | 22       | ✅️    |

* ESP32 型号 GPIO33 及以上只能设置为输入，不能设置为输出
* I2C引脚是固定的，无法更改。它们已经连接到电源管理集成电路（PMIC）。

### ⚡ Electrical parameters

| 特性                      | 详情   |
| ------------------------- | ------ |
| 🔗USB-C 输入电压           | 5V     |
| ⚡USB-C Charge Max Current | 1000mA |
| 🔋电池电压                 | 3.7V   |
| 🔋电池类型                 | 仅限单节可充电锂离子/锂聚合物（Li-ion/LiPo）电池（充满电压 4.2 V） |

> \[!IMPORTANT]
>
> 请勿在本设备中使用或充电磷酸铁锂（LiFePO4）电池，或任何充满电压不是 4.2 V 的电池；本设备仅支持充满电压为 4.2 V 的单节可充电锂离子/锂聚合物电池。

* 充电电流可通过 PMIC 调节，最大 1A

### 按钮说明

| 按钮                | 功能                                       |
| ------------------- | ------------------------------------------ |
| EN (Close to USB-C) | 复位设备按钮                               |
| PWR                 | 按住6秒钟可关闭设备，按住1秒钟可打开设备。 |

* 以上命名方式以开发板丝印为准

### 天线说明

|          | 功能             |
| -------- | ---------------- |
| SIM/MAIN | LTE 主天线接口   |
| GPS/GNSS | GPS 有源天线接口 |

* 以上命名方式以开发板丝印为准

### LED 说明

| 功能         | 颜色                          |
| ------------ | ----------------------------- |
| 模块状态     | RED   (On the modem)          |
| 模块网络状态 | RED    (On the modem)          |
| 充电 LED     | BLUE  (Near the ON BOARD LED) |

* 模块状态灯和网络状态灯无法关闭

### 资源

* [GPS 天线](../../../../datasheet/GPS%20Antenna%20Specifications.pdf)
* [LTE 天线](../../../../datasheet/LTE%20Antenna%20Specifications.pdf)

#### SIM7000X Series

* [T-SIM7000G 原理图](../../../../schematic/esp32/T-SIM7000G-200415.pdf)
* [SIMCOM 官方 SIM7000G 全部数据手册](https://cn.simcom.com/product/SIM7000X.html)
* [For SIM7000 series documentation，请访问 datasheet 目录。](../../../../datasheet/SIM7000/)

#### A7608X Series

* [SIMCOM 官方 A7608X 全部数据手册](https://cn.simcom.com/product/A7608X-H-E_SA.html)
* [For A7608 series documentation，请访问 datasheet 目录。](../../../../datasheet/A76XX/)

#### SIM7670G Series

* [SIMCOM 官方 A7670X 全部数据手册](https://cn.simcom.com/product/A7670X.html)
* [For A7670X series documentation，请访问 datasheet 目录。](../../../../datasheet/A76XX/)

#### SIM7600X Series

* [SIMCOM 官方 SIM7600X 全部数据手册](https://cn.simcom.com/product/SIM7600X.html)
* [For SIM7600 series documentation，请访问 datasheet 目录。](../../../../datasheet/SIM7600X/)

#### SIM7080G Series

* [SIMCOM 官方 SIM7080G-S3 全部数据手册](https://cn.simcom.com/product/SIM7080G.html)
* [For SIM7080G-S3 series documentation，请访问 datasheet 目录。](../../../../datasheet/SIM7080/)

### 常见问题

* **如果以上方法仍然无法上传 sketch，请按照以下方法测试 USB2TTL 通信是否正常。**
  1. 将 USB-C 连接到 PC
  2. 打开串口监视器，将波特率调整为 115200
  3. 按下开发板上的 RST 按钮重启
  4. 如果能看到启动信息，说明 USB2TTL 通信正常。如果串口监视器中没有任何显示，可能是 USB2TTL 桥接损坏

* **升级模块固件** 请参考这里
  1. [T-SIM7000G 升级文档](../sim7000-esp32/upgrade/sim7000_upgrade.md)
  2. [T-SIM7670G 升级文档](../../upgrade/sim7670g/sim7670g_upgrade.md)
  3. [T-A7670X   升级文档](../../../update_fw.md)
  4. [T-SIM7600X 升级文档](../sim7600-esp32/upgrade/sim7600_upgrade.md)
  5. [T-SIM7080G 升级文档](../../esp32s3/sim7080-s3-standard/upgrade/README.MD)

* **无法检测到 SIM 卡？**
   1. 需要先将 SIM 卡插入开发板，然后再开机检测 SIM 卡。如果顺序颠倒，将报告无法检测到 SIM 卡。

* **无法上传任何程序，请手动进入上传模式。**
   1. 通过 USB 线连接开发板
   2. 用导线将 GND 和 IO0 连接起来。
   3. 按下RST按钮
   4. 松开RST按钮
   5. 断开 IO0 与 GND 的连接
   6. 上传程序

* **板载开关的作用**
  1. 使用内部电池组时，开关将正常工作以控制开发板的电源开/关。但是，如果使用外部电池组并连接到 VBAT 引脚，开关将被旁路，这意味着唯一的关机方式是断开电池。
  2. 开关仅用于电池供电，插入 USB 时无效

* **关于 VBUS 引脚**
  1. VBUS 引脚和 USB-C 在同一条线上。只有连接 USB-C 时，VBUS 才有电压
  2. 仅连接电池时，VBUS 没有电压输出
  3. 如果想连接外部电源而不连接 USB-C，VBUS 引脚是唯一的电压输入引脚。请注意，VBUS 引脚的最大输入为 5V，不要超过 5V

* *Unable to put the modem into sleep mode**
  1. PCIE 系列必须移除 VBUS 电感/电阻才能让模块进入睡眠模式

  <img  height="480" width="480" src=./images/pcie.png>

* **SIM7600系列卡仅在下图红色高亮区域内有芯片，表示其具备语音通话功能。如果如下图所示，红色高亮区域为空，则表示其不具备语音通话功能。**

  <img  height="480" width="480" src=./images/sim7600-audio.png>

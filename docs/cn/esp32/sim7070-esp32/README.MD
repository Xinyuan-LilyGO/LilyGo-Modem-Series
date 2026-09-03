<div align="center">

[English](../../../en/esp32/sim7070-esp32/README.MD) | [中文](./README.MD)

</div>

<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo SIM7070G ESP32 版本🌟</h1>

## 概述

* 本页介绍 `LilyGo SIM7070G ESP32 Version` 相关的硬件参数

### 产品

| 产品                | SOC            | Flash         | PSRAM         |
| ------------------- | -------------- | ------------- | ------------- |
| [T-SIM7070G ESP32][1] | ESP32-WROVER-E | 4MB(Quad-SPI) | 8MB(Quad-SPI) |

[1]: https://lilygo.cc/products/t-sim7000g

### 模块差异

| 型号    | GPS | 短信 | 电话 | 频段(**Cat-M**)                                         | 频段(**Cat-NB**)                                    | 频段(**GSM**) |
| ------- | --- | --- | ---- | ----------------------------------------------------------------- | ------------------------------------------------------------- | ----------------------- |
| SIM7070G | ✅   | ❌   | ❌     | B1/B2/B3/B4/B5/B8/B12/B13/B14/B18/B19/B20/B25/B26/B27/B28/B66/B85 | B1/B2/B3/B4/B5/B8/B12/B13/B18/B19/B20/B25/B26/B28/B66/B71/B85 | 850/900/1800/1900MHz    |

> \[!IMPORTANT]
> SIM7070G 的 GPS 和蜂窝功能不能同时启用，否则无法进行 GPS 定位。必须禁用蜂窝定位后才能进行定位。两者互斥。
>

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
8. 取消 `default_envs = T-SIM7070G` 行前面的 `;` 符号，将 `T-SIM7070G` 作为默认环境
9. 取消注释 `src_dir = xxxx` 中的一行，确保只有一行有效。例如，要启用 `src_dir = examples/ATdebug`，删除前面的 `;` 符号并保存文件。现在将编译 ATDebug 示例。
10. 点击左下角的 (✔) 符号进行编译
11. 将开发板通过 USB-C 连接到电脑
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

    | 名称                                   | 值                                   |
    | -------------------------------------- | ------------------------------------ |
    | Board                                | **ESP32 Dev Module**                 |
    | Port                                 | 您的端口                               |
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

     * `Partition Scheme` 请根据实际应用选择。例如选择 **Huge APP (3MB No OTA/1MB SPIFFS)**，更多分区方案请查看[这里](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/partition-tables.html)

7. 在打开的 sketch 中，选择 `utilities.h` 文件，取消注释 `// #define LILYGO_T_SIM7070G` 行。删除 `//` 并保存文件，即可将此开发板作为默认配置。

   ![board_select](../../../static/board_select.jpg)

8. 上传 sketch

> \[!IMPORTANT]
>
> 1. 请勿使用 USB-C 转 USB-C 为主板供电。请使用 USB-A 转 USB-C 为主板供电。Apple 电脑的 USB-C 端口无法直接为主板供电。
> 2. 无法上传任何代码？请查看下方的常见问题
> 3. 打开 Arduino IDE 时，会提示有新的库可以更新。请点击不更新。更新后无法保证能够编译、运行等。请确保开发板正常运行后再决定是否更新。要知道由于库的差异，更新后可能会出现问题，或者默认配置（如 TinyGSM）将被覆盖。
> 4. 如果更新后运行异常，请按照 Arduino 快速入门第 4 条删除 libraries 中的目录，并将 lib 中的文件夹重新拖入 libraries 目录。

### 📍 引脚图

| 名称            | GPIO NUM                     | 可用 |
| --------------- | ---------------------------- | ---- |
| Modem RING      | No connection                | ❌    |
| Modem TX        | 27                           | ❌    |
| Modem RX        | 26                           | ❌    |
| Modem PWRKEY    | 4                            | ❌    |
| Modem DTR       | 25                           | ❌    |
| Board LED       | 12                           | ❌    |
| SD SCK          | 14                           | ❌    |
| SD MISO         | 2                            | ❌    |
| SD MOSI         | 15                           | ❌    |
| SD CS           | 13                           | ❌    |
| 电池 ADC 引脚   | 35                           | ❌    |
| 太阳能 ADC 引脚 | 36                           | ❌    |
| GPS Enabled     | Modem Physical pin number 48 | ❌    |
| Default SDA     | 21                           | ✅️    |
| Default SCL     | 22                           | ✅️    |

* 外设电源控制引脚。使用 SD 或 modem 时，必须将此 GPIO 设置为高电平，否则这些功能无法使用。
* ESP32 型号 GPIO33 及以上只能设置为输入，不能设置为输出

> \[!IMPORTANT]
> ESP32 版本由于 SD 卡使用 IO2 作为 CS，插入 SD 卡时无法在 Arduino IDE 中上传软件，因此上传新代码时必须取出 SD 卡
>
> GPIO4(PWRKEY)、GPIO26(TX)、GPIO27(RX) 暴露在排针上。请勿在排针的 GPIO4 位置连接任何导线；保持未连接状态。
>
> GPIO25 (Modem DTR) 暴露在排针上。请勿在排针的 GPIO25 位置连接任何导线；保持未连接状态。
>

### 模块引脚

| 名称                  | GPIO NUM | 使能电平 | AT 命令          |
| --------------------- | -------- | ------------ | ------------------- |
| GPS 天线电源使能  | 48       | 高电平         | `AT+CGPIO=0,48,1,1` |
| GPS 天线电源禁用 | 48       | 低电平          | `AT+CGPIO=0,48,1,0` |

> [!IMPORTANT]
> 🚨 **使用 GPS/GNSS 前必须先开启有源天线供电！** SIM7070 使用模块物理 GPIO48 控制天线电源；请先发送 `AT+CGPIO=0,48,1,1` 开启供电，否则将无法定位或无法获得 GPS fix。不使用 GPS/GNSS 时，可发送 `AT+CGPIO=0,48,1,0` 关闭天线供电以降低功耗。

### ⚡ 电气参数

| 特性                        | 详情 |
| ------------------------------- | ------- |
| 🔗USB-C 输入电压            | 5V      |
| ⚡太阳能输入电压            | 5~6V    |
| ⚡USB-C/太阳能充电最大电流 | 500mA   |
| 🔋电池电压                | 3.7V    |
| 📍**VBUS** ( 排针)         | 5V      |
| 📍**VBAT** ( 排针)         | 4.2V    |

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

### ⚡电池保护说明

| 特性                | 详情    |
| ----------------------- | ---------- |
| 过压阈值  | 4.30V      |
| 欠压阈值 | 2.5V       |
| 过放电流  | 3A         |
| 芯片名称                | [DW01V][2] |

> \[!IMPORTANT]
>
> 在 USB 和电池之间切换时，开发板可能会重置并重启设备。这是正常的，因为开发板没有无缝电源切换解决方案。
>
> 此行为不受软件设置的影响。
>

### 按钮说明

| 按钮              | 功能                                                                             |
| ------------------- | ------------------------------------------------------------------------------------ |
| RST(靠近 modem) | 复位设备按钮                                                                 |
| PWR(靠近 modem) | 首次连接电池时，按 PWR 激活电池供电。 |

* 以上命名方式以开发板丝印为准

### 天线说明

|     | 功能                     |
| --- | ---------------------------- |
| SIM | LTE 主天线接口   |
| GPS | GPS 有源天线接口 |

* 以上命名方式以开发板丝印为准

### LED 说明

| 功能            | 颜色                            |
| ------------------- | -------------------------------- |
| 模块状态        | 红色   (靠近 modem)           |
| 模块网络状态 | 红色   (靠近 modem)           |
| 充电 LED          | 红色  (靠近电池开关)   |
| 充电完成 LED     | 绿色  (靠近电池开关) |
| 板载 LED        | 蓝色  (靠近 esp 模块)      |

* 模块状态灯和网络状态灯无法关闭

### 资源

* [GPS 天线](../../../../datasheet/GPS%20Antenna%20Specifications.pdf)
* [LTE 天线](../../../../datasheet/LTE%20Antenna%20Specifications.pdf)
* [T-SIM7070G 原理图](../../../../schematic/esp32/T-SIM7000G-200415.pdf)
* [SIMCOM 官方 SIM7070G 全部数据手册](https://www.simcom.com/product/SIM7070G.html)
* [SIM7000 系列文档，请访问 datasheet 目录。](../../../../datasheet/SIM7080/)
* [开发板尺寸](../../../../dimensions/esp32/T-SIM7000-ESP32.dxf)
* [外壳](../../../../dimensions/esp32/T-SIM7000-ESP32-Case.zip)

### 常见问题

* **如果以上方法仍然无法上传 sketch，请按照以下方法测试 USB2TTL 通信是否正常。**
  1. 将 USB-C 连接到 PC
  2. 打开串口监视器，将波特率调整为 115200
  3. 按下开发板上的 RST 按钮重启
  4. 如果能看到启动信息，说明 USB2TTL 通信正常。如果串口监视器中没有任何显示，可能是 USB2TTL 桥接损坏

* **升级模块固件**
  1. [T-SIM7070G 升级文档](../../upgrade/sim7070g/sim7070g_upgrade.md)

* **无法检测到 SIM 卡？**
   1. 需要先将 SIM 卡插入开发板，然后再开机检测 SIM 卡。如果顺序颠倒，将报告无法检测到 SIM 卡。

* **无法上传任何 sketch，请手动进入上传模式。**
   1. 通过 USB 线连接开发板
   2. 用导线将 GND 和 IO0 连接在一起
   3. 按 RST 按钮
   4. 释放 RST 按钮
   5. 断开 IO0 和 GND 的连接
   6. 上传 sketch

* **板载开关的作用**
  1. 使用内部电池组时，开关将正常工作以控制开发板的电源开/关。但是，如果使用外部电池组并连接到 VBAT 引脚，开关将被旁路，这意味着唯一的关机方式是断开电池。
  2. 开关仅用于电池供电，插入 USB 时无效

* **关于 VBUS 引脚**
  1. VBUS 引脚和 USB-C 在同一条线上。只有连接 USB-C 时，VBUS 才有电压
  2. 仅连接电池时，VBUS 没有电压输出
  3. 如果想连接外部电源而不连接 USB-C，VBUS 引脚是唯一的电压输入引脚。请注意，VBUS 引脚的最大输入为 5V，不要超过 5V

* 可以使用其他 GPS 天线吗？
  1. 外部 GPS 天线必须是 3.3V 供电的有源 GPS 天线。例如，[MK-76](https://www.rfmw.com/datasheets/sanav/mk-76.pdf) 支持 2.5-5.5V，兼容。大多数有源 GPS 天线支持 2.5-5.5V 供电。详情请参考 GPS 天线数据手册。

[2]: https://item.szlcsc.com/datasheet/DW01V/140050.html?spm=sc.it.pdf.fd&lcsc_vid=QgRWVldWE1dZAwECQFUMVgYHFFRdXlxWRlELVFQFTgMxVlNTT1hdUldfQ1JeXjsOAxUeFF5JWBYZEEoEHg8JSQcJGk4%3D

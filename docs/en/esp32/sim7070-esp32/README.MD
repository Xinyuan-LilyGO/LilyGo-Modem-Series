<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo SIM7070G ESP32 Version🌟</h1>

<div align="center">

[English](./README.MD) | [中文](../../../cn/esp32/sim7070-esp32/README.MD)

</div>

## Overview

* This page introduces the hardware parameters related to `LilyGo SIM7070G ESP32 Version`

### Product

| Product               | SOC            | Flash         | PSRAM         |
| --------------------- | -------------- | ------------- | ------------- |
| [T-SIM7070G ESP32][1] | ESP32-WROVER-E | 4MB(Quad-SPI) | 8MB(Quad-SPI) |

[1]: https://lilygo.cc/products/t-sim7000g

### Modem differences

| Model    | GPS | SMS | Phone Call | Frequency band(**Cat-M**)                                         | Frequency band(**Cat-NB**)                                    | Frequency band(**GSM**) |
| -------- | --- | --- | ---------- | ----------------------------------------------------------------- | ------------------------------------------------------------- | ----------------------- |
| SIM7070G | ✅   | ❌   | ❌          | B1/B2/B3/B4/B5/B8/B12/B13/B14/B18/B19/B20/B25/B26/B27/B28/B66/B85 | B1/B2/B3/B4/B5/B8/B12/B13/B18/B19/B20/B25/B26/B28/B66/B71/B85 | 850/900/1800/1900MHz    |

> \[!IMPORTANT]
> SIM7070G GPS and cellular functions cannot be enabled at the same time, otherwise GPS positioning cannot be performed. Cellular positioning must be disabled before positioning can be performed. The two are mutually exclusive.
>

### PlatformIO Quick Start

1. Install the **CH9102 USB bridge** driver for the first time.
   * [Windows](https://www.wch-ic.com/downloads/CH343SER_ZIP.html)
   * [Mac OS](https://www.wch-ic.com/downloads/CH34XSER_MAC_ZIP.html)
2. Install [Visual Studio Code](https://code.visualstudio.com/) and [Python](https://www.python.org/)
3. Search for the `PlatformIO` plugin in the `Visual Studio Code` extension and install it.
4. After the installation is complete, you need to restart `Visual Studio Code`
5. After restarting `Visual Studio Code`, select `File` in the upper left corner of `Visual Studio Code` -> `Open Folder` -> select the `LilyGo-Modem-Series` directory
6. Wait for the installation of third-party dependent libraries to complete
7. Click on the `platformio.ini` file, and in the `platformio` column
8. Cancel the `;` symbol in front of the line `default_envs = T-SIM7070G` and use `T-SIM7070G` as the default environment
9. Uncomment one of the lines `src_dir = xxxx` to ensure that only one line is valid. For example, to enable `src_dir = examples/ATdebug`, remove the leading `;` symbol and save the file. The ATDebug example will now be compiled.
10. Click the (✔) symbol in the lower left corner to compile
11. Connect the board to the computer USB-C
12. Click (→) to upload firmware
13. Click (plug symbol) to monitor serial output
14. If it cannot be written, or the USB device keeps flashing, please check the **FAQ** below

### Arduino IDE quick start

1. Install the **CH9102 USB bridge** driver for the first time.
   * [Windows](https://www.wch-ic.com/downloads/CH343SER_ZIP.html)
   * [Mac OS](https://www.wch-ic.com/downloads/CH34XSER_MAC_ZIP.html)
2. Install [Arduino IDE](https://www.arduino.cc/en/software)
3. Install [Arduino ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
4. Copy all folders in the `lib` directory to the `Sketchbook location` directory. How to find the location of your own libraries, [please see here](https://support.arduino.cc/hc/en-us/articles/4415103213714-Find-sketches-libraries-board-cores-and-other-files-on-your-computer)
    * Windows: `C:\Users\%USERNAME%\Documents\Arduino\libraries`
    * MacOS: `$HOME/Documents/Arduino/libraries`
    * Linux: `$HOME/Arduino/libraries`
5. Open the corresponding example
    * Open the downloaded `LilyGo-Modem-Series`
    * Open `examples`
    * Select the sample file and open the file ending with `ino`
6. In Arduino IDE, select the corresponding board in the tool project and click on the corresponding option in the list below to select

    | Name                                 | Value                                |
    | ------------------------------------ | ------------------------------------ |
    | Board                                | **ESP32 Dev Module**                 |
    | Port                                 | Your port                            |
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

     * `Partition Scheme` Please select according to the actual application. For example, select **Huge APP (3MB No OTA/1MB SPIFFS)** , For more partitioning schemes, please see [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/partition-tables.html)

7. In the open sketch, select the `utilities.h` file and uncomment the line `// #define LILYGO_T_SIM7070G`. Delete the `//` and save the file to use this board as the default configuration.

   ![board_select](../../../static/board_select.jpg)

8. Upload sketch

> \[!IMPORTANT]
>
> 1. Do not use USB-C to USB-C to power the motherboard. Please use USB-A to USB-C to power the motherboard. The USB-C port on the Apple computer cannot directly power the motherboard.
> 2. Unable to upload any code? Please see the FAQ below
> 3. When opening the Arduino IDE, you will be prompted that there are new libraries that can be updated. Please do not click update. There is no guarantee that it can be compiled, run, etc. after the update. Make sure that the board is running normally before deciding whether to update. You have to Know that problems may occur after updating due to library differences, or the default configuration (such as TinyGSM) will be overwritten.
> 4. If it runs abnormally after the update, please follow Article 4 of the Arduino Quick Start to delete the directory in libraries, and drag the folder in lib into the libraries directory again.

### 📍 Pins Map

| Name            | GPIO NUM                     | Free |
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
| Battery ADC Pin | 35                           | ❌    |
| Solar ADC Pin   | 36                           | ❌    |
| GPS Enabled     | Modem Physical pin number 48 | ❌    |
| Default SDA     | 21                           | ✅️    |
| Default SCL     | 22                           | ✅️    |

* Peripheral power control pin. When using SD or modem, this GPIO must be set to high level, otherwise these functions cannot be used.
* ESP32 models GPIO33 and above can only be set as input, not output

> \[!IMPORTANT]
> ESP32 version Since the SD card uses IO2 as CS, you cannot upload software in the Arduino IDE when you insert the SD card, so you must remove the SD card when uploading new code
>
> GPIO4(PWRKEY),GPIO26(TX),GPIO27(RX), is exposed on the header pins. Do not connect any wires to the GPIO4 position on the header pins; keep it unconnected.
>
> GPIO25 (Modem DTR) is exposed on the header. Do not connect any wires to the GPIO25 position on the header; keep it disconnected.
>

### Modem Pins

| Name                  | GPIO NUM | Enable level | AT Command          |
| --------------------- | -------- | ------------ | ------------------- |
| GPS Ant Power Enable  | 48       | High         | `AT+CGPIO=0,48,1,1` |
| GPS Ant Power Disable | 48       | Low          | `AT+CGPIO=0,48,1,0` |

> [!IMPORTANT]
> 🚨 **Before using GPS/GNSS, you must enable power to the active antenna by sending `AT+CGPIO=0,48,1,1`; otherwise, the modem cannot obtain a position fix. Disable the antenna power with `AT+CGPIO=0,48,1,0` when GPS/GNSS is not in use.**

### ⚡ Electrical parameters

| Features                        | Details |
| ------------------------------- | ------- |
| 🔗USB-C Input Voltage            | 5V      |
| ⚡Solar Input Voltage            | 5~6V    |
| ⚡USB-C/Solar Charge Max Current | 500mA   |
| 🔋Battery Voltage                | 3.7V    |
| 📍**VBUS** ( Pin header)         | 5V      |
| 📍**VBAT** ( Pin header)         | 4.2V    |

> \[!TIP]
>
> 1. The onboard JST2.0 interface is only used to connect the solar panel to charge the battery, and cannot provide power to the board from this interface
> 2. It is recommended to use a solar panel with an output voltage of 6V or 5V and a power of about 5-10W. Solar energy can only charge the battery. Without the battery, the panel cannot supply power.
> Please note that this is only a suggestion. It is not necessary to use a 5-10W solar panel. 1W is also acceptable.
> The size of the solar panel determines the current and speed of solar charging. Please note that depending on the environment,
> the sunshine time may not exceed one hour per day. At this time, if the solar panel is too small and the light is not sufficient, it cannot be charged.
> 3. Connect the VBUS pin to the USB-C power supply. If USB-C is present, the VBUS voltage is equal to the USB-C voltage. If USB-C is not present, there is no voltage on VBUS.
> 4. Connect the VBAT pin to the positive terminal of the battery. This pin can be used to connect an external battery directly to the VBAT pin. When using an external battery, it is best not to connect the battery to the development board's 18650 battery holder unless the battery's parameters are similar to the external battery. Batteries connected to the VBAT pin can be charged using the onboard charge management.
> 5. The VBUS pin is the only interface besides the battery that supplies power to the board; there is no other way.
> 6. The USB/VBUS pin input must be capable of providing a peak current of at least 2A, and the voltage must not drop below 5V, otherwise it will trigger a low-voltage automatic shutdown.

### ⚡Battery Protector Description

| Features                | Details    |
| ----------------------- | ---------- |
| Over-Voltage Threshold  | 4.30V      |
| Under-Voltage Threshold | 2.5V       |
| Over-Discharge Current  | 3A         |
| ChipName                | [DW01V][2] |

> \[!IMPORTANT]
>
> The board may reset and restart the device when switching between USB and battery. This is normal, as the board does not have a seamless power switching solution.
>
> This behavior cannot be affected by software settings.
>

### Button Description

| Button              | Function                                                                             |
| ------------------- | ------------------------------------------------------------------------------------ |
| RST(Close to modem) | Reset devices button                                                                 |
| PWR(Close to modem) | When the battery is first connected, press PWR to activate the battery power supply. |

* The above naming method is subject to the board silk screen printing

### Antenna Description

|     | Function                     |
| --- | ---------------------------- |
| SIM | LTE Main antenna interface   |
| GPS | GPS active antenna interface |

* The above naming method is subject to the board silk screen printing

### LED Description

| FUNCTION            | COLOR                            |
| ------------------- | -------------------------------- |
| MODEM STATUS        | RED   (Near the modem)           |
| MODEM NETWORK STATE | RED   (Near the modem)           |
| CHARGE LED          | RED  (Near the battery switch)   |
| CHARGE DONE LED     | Green  (Near the battery switch) |
| ON BOARD LED        | BLUE  (Near the esp module)      |

* Modem Status light and network status led cannot be turned off

### Resource

* [GPS Antenna](../../../../datasheet/GPS%20Antenna%20Specifications.pdf)
* [LTE Antenna](../../../../datasheet/LTE%20Antenna%20Specifications.pdf)
* [T-SIM7070G Schematic](../../../../schematic/esp32/T-SIM7000G-200415.pdf)
* [SIMCOM official SIM7070G All Datasheet](https://www.simcom.com/product/SIM7070G.html)
* [For SIM7000 series documentation, please visit the datasheet directory.](../../../../datasheet/SIM7080/)
* [Board dimensions](../../../../dimensions/esp32/T-SIM7000-ESP32.dxf)
* [Case](../../../../dimensions/esp32/T-SIM7000-ESP32-Case.zip)

### FAQ

* **If the above method still fails to upload the sketch, please follow the method below to test whether the USB2TTL communication is normal.**
  1. Connect USB-C to PC
  2. Open the serial monitor and adjust the baud rate to 115200
  3. Press the RST button on the board to restart
  4. If you can see the startup information, it means that the USB2TTL communication is normal. If nothing is displayed in the serial monitor, it may be that the USB2TTL bridge is damaged

* **Upgrade modem firmware**
  1. [T-SIM7070G Upgrade docs](../../upgrade/sim7070g/sim7070g_upgrade.md)

* **Unable to detect SIMCard?**
   1. Need to insert the SIMCard into the board first and then power on to detect the SIM card. If the order is reversed, it will report that the SIMCard cannot be detected.

* **Can't upload any sketch，Please enter the upload mode manually.**
   1. Connect the board via the USB cable
   2. Use wires to connect GND and IO0 together
   3. Press RST button
   4. Release the RST button
   5. Disconnect IO0 from GND
   6. Upload sketch

* **What the onboard switch does**
  1. When using the internal battery pack, the switch will work normally to power/power down the board. However, if an external battery pack is used and connected to the VBAT pin, the switch will be bypassed, meaning the only way to shut down is to disconnect the battery.
  2. The switch is only for battery power and has no effect when plugged into USB

* **About VBUS Pin**
  1. VBUS Pin and USB-C are on the same line. Only when USB-C is connected, VBUS has voltage
  2. When only the battery is connected, VBUS has no voltage output
  3. If you want to connect an external power supply without connecting USB-C, VBUS Pin is the only voltage input pin. Please note that the maximum input of VBUS Pin is 5V, do not exceed 5V

* Can other GPS antennas be used?
  1. The external GPS antenna must be an active GPS antenna with a 3.3V power supply. For example, the [MK-76](https://www.rfmw.com/datasheets/sanav/mk-76.pdf) supports 2.5-5.5V and is compatible. Most active GPS antennas support 2.5-5.5V power. Please refer to the GPS antenna datasheet for details.

[2]: https://item.szlcsc.com/datasheet/DW01V/140050.html?spm=sc.it.pdf.fd&lcsc_vid=QgRWVldWE1dZAwECQFUMVgYHFFRdXlxWRlELVFQFTgMxVlNTT1hdUldfQ1JeXjsOAxUeFF5JWBYZEEoEHg8JSQcJGk4%3D

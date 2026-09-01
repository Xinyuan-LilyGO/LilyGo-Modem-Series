<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo SIM7670G ESP32S3 Version🌟</h1>

<div align="center">

[English](./README.MD) | [中文](../../../cn/esp32s3/sim7670g-s3/README.MD)

</div>

## Overview

* This page introduces the hardware parameters related to `LilyGo SIM7670G ESP32S3 Version`

### Product

| Product                 | SOC              | Flash          | PSRAM    |
| ----------------------- | ---------------- | -------------- | -------- |
| [T-SIM7670G ESP32S3][1] | ESP32-S3-WROOM-1 | 16MB(Quad-SPI) | 8MB(OPI) |

[1]: https://www.lilygo.cc/products/t-sim-7670g-s3

### Modem differences

| Model    | GPS | Phone Call | SMS | Frequency band                                                                                         |
| -------- | --- | ---------- | --- | ------------------------------------------------------------------------------------------------------ |
| SIM7670G | ✅   | ❌          | ✅   | LTE-FDD:B1/B2/B3/B4/B5/B7/B8/B12/B13/B18/B19/B20/B25/B26/B28/B66/B71 LTE-TDD:B34/B38/B39/B40/B41 GSM:❌ |

* SMS: `SIM7670G-MNGV 2374B04` version supports SMS function,but it requires the operator base station to support SMS Over SGS service to send, otherwise it will be invalid

### PlatformIO Quick Start

1. Install [Visual Studio Code](https://code.visualstudio.com/) and [Python](https://www.python.org/)
2. Search for the `PlatformIO` plugin in the `Visual Studio Code` extension and install it.
3. After the installation is complete, you need to restart `Visual Studio Code`
4. After restarting `Visual Studio Code`, select `File` in the upper left corner of `Visual Studio Code` -> `Open Folder` -> select the `LilyGo-Modem-Series` directory
5. Wait for the installation of third-party dependent libraries to complete
6. Click on the `platformio.ini` file, and in the `platformio` column
7. Cancel the `;` symbol in front of the line `default_envs = T-SIM7670G` and use `T-SIM7670G` as the default environment
8. Uncomment one of the lines `src_dir = xxxx` to ensure that only one line is valid. For example, to enable `src_dir = examples/ATdebug`, remove the leading `;` symbol and save the file. The ATDebug example will now be compiled.
9. Click the (✔) symbol in the lower left corner to compile
10. Connect the board to the computer USB-C , Micro-USB is used for module firmware upgrade
11. Click (→) to upload firmware
12. Click (plug symbol) to monitor serial output
13. If it cannot be written, or the USB device keeps flashing, please check the **FAQ** below

### Arduino IDE quick start

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install [Arduino ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
3. Copy all folders in the `lib` directory to the `Sketchbook location` directory. How to find the location of your own libraries, [please see here](https://support.arduino.cc/hc/en-us/articles/4415103213714-Find-sketches-libraries-board-cores-and-other-files-on-your-computer)
    * Windows: `C:\Users\%USERNAME%\Documents\Arduino\libraries`
    * MacOS: `$HOME/Documents/Arduino/libraries`
    * Linux: `$HOME/Arduino/libraries`
4. Open the corresponding example
    * Open the downloaded `LilyGo-Modem-Series`
    * Open `examples`
    * Select the sample file and open the file ending with `ino`
5. In Arduino IDE, select the corresponding board in the tool project and click on the corresponding option in the list below to select

    | Name                                 | Value                               |
    | ------------------------------------ | ----------------------------------- |
    | Board                                | **ESP32S3 Dev Module**              |
    | Port                                 | Your port                           |
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
    | PSRAM                                | **OPI PSRAM**                       |
    | Upload Speed                         | 921600                              |
    | Programmer                           | **Esptool**                         |

     * `Partition Scheme` Please select according to the actual application. For example, select **16M Flash (3MB APP/9.9MB FATFS)** , For more partitioning schemes, please see [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/partition-tables.html)

6. In the open sketch, select the `utilities.h` file and uncomment the line `// #define LILYGO_T_SIM7670G_S3`. Delete the `//` and save the file to use this board as the default configuration.

   ![board_select](../../../static/board_select.jpg)

7. Upload sketch

> \[!IMPORTANT]
>
> 1. Unable to upload any code? Please see the FAQ below
> 2. When opening the Arduino IDE, you will be prompted that there are new libraries that can be updated. Please do not click update. There is no guarantee that it can be compiled, run, etc. after the update. Make sure that the board is running normally before deciding whether to update. You have to Know that problems may occur after updating due to library differences, or the default configuration (such as TinyGSM) will be overwritten.
> 3. If it runs abnormally after the update, please follow Article 4 of the Arduino Quick Start to delete the directory in libraries, and drag the folder in lib into the libraries directory again.

### 📍 Pins Map

| Name            | GPIO NUM     | Free |
| --------------- | ------------ | ---- |
| Modem TX        | 11           | ❌    |
| Modem RX        | 10           | ❌    |
| Modem PWRKEY    | 18           | ❌    |
| Modem RESET     | 17           | ❌    |
| Modem RING      | 3            | ❌    |
| Modem DTR       | 9            | ❌    |
| Board LED       | 12           | ❌    |
| Battery ADC Pin | 4 (See Tips) | ❌    |
| Solar ADC Pin   | 5            | ❌    |
| SD SCK          | 21           | ❌    |
| SD MISO         | 47           | ❌    |
| SD MOSI         | 14           | ❌    |
| SD CS           | 13           | ❌    |

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
> ⚠ When USB-C is connected, the GPIO4 ADC circuit is disconnected, so the measured voltage is 0. The voltage divider circuit will only be connected again after USB-C is disconnected.
>

### Modem Pins

| Name                 | GPIO NUM | Enable level | AT Command                     |
| -------------------- | -------- | ------------ | ------------------------------ |
| GPS Ant Power Enable | 4        | High         | `AT+CGDRT=4,1 ; AT+CGSETV=4,1` |

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

| Button                   | Function                                                                             |
| ------------------------ | ------------------------------------------------------------------------------------ |
| BOOT(Close to esp)       | Customizable function/Download mode                                                  |
| RST                      | Reset devices button                                                                 |
| SIM-BOOT(Close to modem) | Modem Upgrade mode                                                                   |
| PWR(Close to modem)      | When the battery is first connected, press PWR to activate the battery power supply. |

* Press and hold the `BOOT` button before powering on. The board is now in waiting mode for downloading.
* Before powering on, keep the `SIM-BOOT` button pressed to put the modem into firmware update mode.
* The above naming method is subject to the board silk screen printing

### Antenna Description

|      | Function                     |
| ---- | ---------------------------- |
| SIM  | LTE Main antenna interface   |
| GNSS | GPS active antenna interface |

* When using, you only need to connect the LTE antenna you wear to the SIM IPEX first generation interface. The AUX antenna does not need to be connected.
* The above naming method is subject to the board silk screen printing

### LED Description

| FUNCTION            | COLOR                            |
| ------------------- | -------------------------------- |
| MODEM STATUS        | RED   (Near the modem)           |
| MODEM NETWORK STATE | RED   (Near the modem)           |
| CHARGE LED          | RED   (Near the battery switch)  |
| CHARGE DONE LED     | GREEN  (Near the battery switch) |
| ON BOARD LED        | BLUE  (Near the RST button)      |

* Modem Status light and network status led cannot be turned off

### Resource

* [GPS Antenna](../../../../datasheet/GPS%20Antenna%20Specifications.pdf)
* [LTE Antenna](../../../../datasheet/LTE%20Antenna%20Specifications.pdf)
* [T-SIM7670G Schematic](../../../../schematic/esp32s3/T-SIM7670G-S3-V1.1.pdf)
* [SIMCOM official SIM7670G All Datasheet](https://cn.simcom.com/product/SIM7670X.html)
* [For SIM7670G series documentation, please visit the datasheet directory.](../../../../datasheet/SIM767X/)
* [Board dimensions](../../../../dimensions/esp32s3/T-SIM7670G-S3.dxf)

### FAQ

* **Upgrade modem firmware**
  1. [T-A76XX Upgrade docs](../../../../docs/update_fw.md) / [Video](https://www.youtube.com/watch?v=fAtrz_4DfVs)

* **Unable to detect SIMCard?**
   1. Need to insert the SIMCard into the board first and then power on to detect the SIM card. If the order is reversed, it will report that the SIMCard cannot be detected.

* **Can't upload any sketch，Please enter the upload mode manually.**
   1. Connect the board via the USB cable
   2. Press and hold the **BOOT** button , While still pressing the **BOOT** button
   3. Press **RST** button
   4. Release the **RST** button
   5. Release the **BOOT** button
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

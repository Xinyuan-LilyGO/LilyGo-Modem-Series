<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo A7608X ESP32 Version🌟</h1>

<div align="center">

[English](./README.MD) | [中文](../../../cn/esp32/a7608-esp32/README.MD)

</div>

## Overview

* This page introduces the hardware parameters related to `LilyGo A7608X ESP32 Version`

### Product

| Product                | SOC            | Flash         | PSRAM         |
| ---------------------- | -------------- | ------------- | ------------- |
| [T-A7608E/SA ESP32][1] | ESP32-WROVER-E | 4MB(Quad-SPI) | 8MB(Quad-SPI) |

[1]: https://lilygo.cc/products/t-a7608e-h?variant=42860532433077

### Modem differences

| Model     | GPS | Phone Call | SMS | Frequency band                                                                                                         |
| --------- | --- | ---------- | --- | ---------------------------------------------------------------------------------------------------------------------- |
| A7608E-H  | ✅   | ✅          | ✅   | LTE-TDD B38/B40/B41 LTE-FDD B1/B3/B5/B7/B8/B20 UMTS/HSPA+ B1/B8  GSM/GPRS/EDGE 900/1800 MHz                            |
| A7608SA-H | ✅   | ✅          | ✅   | LTE-TDD B38/B40/B41 LTE-FDD B1/B2/B3/B4/B5/B7/B8/B20/B28/B66 UMTS/HSPA+ B1/B2/B5/B8 GSM/GPRS/EDGE850/900/1800/1900 MHz |

* A7608 also has a version without positioning. Whether it has positioning function cannot be obtained from AT commands. It can only be distinguished by the PN number of the modem. Please check whether the purchase order includes GPS function.

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
8. Cancel the `;` symbol in front of the line `default_envs = T-A7608X` and use `T-A7608X` as the default environment
9. Uncomment one of the lines `src_dir = xxxx` to ensure that only one line is valid. For example, to enable `src_dir = examples/ATdebug`, remove the leading `;` symbol and save the file. The ATDebug example will now be compiled.
10. Click the (✔) symbol in the lower left corner to compile
11. Connect the board to the computer USB-C , Micro-USB is used for module firmware upgrade
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

7. In the open sketch, select the `utilities.h` file and uncomment the line `// #define LILYGO_T_A7608X`. Delete the `//` and save the file to use this board as the default configuration.

   ![board_select](../../../static/board_select.jpg)

8. Upload sketch

> \[!IMPORTANT]
>
> 1. Do not use USB-C to USB-C to power the motherboard. Please use USB-A to USB-C to power the motherboard. The USB-C port on the Apple computer cannot directly power the motherboard.
> 2. Unable to upload any code? Please see the FAQ below
> 3. When opening the Arduino IDE, you will be prompted that there are new libraries that can be updated. Please do not click update. There is no guarantee that it can be compiled, run, etc. after the update. Make sure that the board is running normally before deciding whether to update. You have to Know that problems may occur after updating due to library differences, or the default configuration (such as TinyGSM) will be overwritten.
> 4. If it runs abnormally after the update, please follow Article 4 of the Arduino Quick Start to delete the directory in libraries, and drag the folder in lib into the libraries directory again.

### 📍 Pins Map

| Name                     | GPIO NUM     | Free |
| ------------------------ | ------------ | ---- |
| Peripheral power control | 12           | ❌    |
| Modem TX                 | 26           | ❌    |
| Modem RX                 | 27           | ❌    |
| Modem PWR                | 4            | ❌    |
| Modem RESET              | 5            | ❌    |
| Modem RING               | 33           | ❌    |
| Modem DTR                | 25           | ❌    |
| SD SCK                   | 14           | ❌    |
| SD MISO                  | 2            | ❌    |
| SD MOSI                  | 15           | ❌    |
| SD CS                    | 13           | ❌    |
| Battery ADC Pin          | 35           | ❌    |
| GPS Enabled              | Modem AUXVDD | ❌    |
| Default SDA              | 21           | ✅️    |
| Default SCL              | 22           | ✅️    |

* Peripheral power control pin. When using SD or modem, this GPIO must be set to high level, otherwise these functions cannot be used.
* ESP32 models GPIO33 and above can only be set as input, not output

> \[!IMPORTANT]
> ESP32 version Since the SD card uses IO2 as CS, you cannot upload software in the Arduino IDE when you insert the SD card, so you must remove the SD card when uploading new code
>
> GPIO4(PWRKEY),GPIO26(TX),GPIO27(RX), is exposed on the header pins. Do not connect any wires to the GPIO4 position on the header pins; keep it unconnected.
>
> GPIO5 (Modem RST) is exposed on the header. Do not connect any wires to the GPIO5 position on the header; keep it disconnected.
>

### ⚡ Electrical parameters

| Features                        | Details |
| ------------------------------- | ------- |
| 🔗USB-C Input Voltage            | 5V      |
| ⚡Solar Input Voltage            | 5~6V    |
| ⚡USB-C/Solar Charge Max Current | 500mA   |
| 🔋Battery Voltage                | 3.7V    |
| 🔋Battery Type                   | Single-cell rechargeable Li-ion/LiPo (4.2 V full-charge) |
| 📍**VBUS** ( Pin header)         | 5V      |
| 📍**VBAT** ( Pin header)         | 4.2V    |

> \[!IMPORTANT]
>
> Do not use or charge LiFePO4 batteries, or any battery with a full-charge voltage other than 4.2 V, in this device. This device supports only single-cell rechargeable Li-ion/LiPo batteries with a 4.2 V full-charge voltage.
>

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
| Under-Voltage Threshold | 2.4V       |
| Over-Discharge Current  | 3A         |
| ChipName                | [DW06D][2] |

> \[!IMPORTANT]
>
> The board may reset and restart the device when switching between USB and battery. This is normal, as the board does not have a seamless power switching solution.
>
> This behavior cannot be affected by software settings.
>

### Button Description

| Button              | Function                            |
| ------------------- | ----------------------------------- |
| IO0(Close to esp)   | Customizable function/Download mode |
| RST                 | Reset devices button                |
| BOT(Close to modem) | Modem Upgrade mode                  |

* Press and hold the IO0 button before powering on. The board is now in waiting mode for downloading.
* Before powering on, keep the BOT button pressed to put the modem into firmware update mode.
* The above naming method is subject to the board silk screen printing

### Antenna Description

|      | Function                     |
| ---- | ---------------------------- |
| SIM  | LTE Main antenna interface   |
| AUX  | LTE Diversity antenna interface |
| GNSS | GPS active antenna interface |

* When using, you only need to connect the LTE antenna you wear to the SIM IPEX first generation interface. The AUX antenna does not need to be connected.
* The above naming method is subject to the board silk screen printing

### LED Description

| FUNCTION            | COLOR                           |
| ------------------- | ------------------------------- |
| MODEM STATUS        | RED   (Near the modem)          |
| MODEM NETWORK STATE | RED   (Near the modem)          |
| CHARGE LED          | BLUE  (Near the battery switch) |
| CHARGE DONE LED     | BLUE  (Near the battery switch) |

* Modem Status light and network status led cannot be turned off

### Audio interface

* The audio interfaces are now highlighted in the image below; the speaker jack is on the left, and the microphone jack is on the right.

  <img src="../../../../images/product/png/A7608X-SPEK.png" alt="microphone" width="480" style="border: 0;"/>

* Compatible with condenser microphones and speakers, but not with digital microphones; only compatible with condenser microphones.

  <img src="../../../../docs/static/microphone.png" alt="microphone" width="240" style="border: 0;"/>
  <img src="../../../../docs/static/speaker.png" alt="speaker" width="240" style="border: 0;"/>

### Resource

* [GPS Antenna](../../../../datasheet/GPS%20Antenna%20Specifications.pdf)
* [LTE Antenna](../../../../datasheet/LTE%20Antenna%20Specifications.pdf)
* [T-A7608X Schematic](../../../../schematic/esp32/T-A7608X-V1.0.pdf)
* [SIMCOM official A7608X All Datasheet](https://cn.simcom.com/product/A7608X-H-E_SA.html)
* [For A7608 series documentation, please visit the datasheet directory.](../../../../datasheet/A76XX/)
* [Board dimensions](../../../../dimensions/esp32/T-A7608X-ESP32.dxf)

### FAQ

* **ESP32 (V1.x) version T-A7608  known issue**
  1. When using battery power mode, BOARD_POWERON_PIN (IO12) must be set to a high level after ESP32 starts, otherwise a reset will occur.
  2. Modem cannot be put into sleep mode when powered by USB-C. For a solution, see [here](https://github.com/Xinyuan-LilyGO/LilyGO-T-A76XX/blob/main/examples/ModemSleep/README.MD)

* **If the above method still fails to upload the sketch, please follow the method below to test whether the USB2TTL communication is normal.**
  1. Connect USB-C to PC
  2. Open the serial monitor and adjust the baud rate to 115200
  3. Press the RST button on the board to restart
  4. If you can see the startup information, it means that the USB2TTL communication is normal. If nothing is displayed in the serial monitor, it may be that the USB2TTL bridge is damaged

* **Upgrade modem firmware**
  1. [T-A76XX Upgrade docs](../../../../docs/update_fw.md) / [Video](https://youtu.be/AZkm-Z7mKn8)

* **Unable to detect SIMCard?**
   1. Need to insert the SIMCard into the board first and then power on to detect the SIM card. If the order is reversed, it will report that the SIMCard cannot be detected.

* **Can't upload any sketch，Please enter the upload mode manually.**
   1. Connect the board via the USB cable
   2. Press and hold the **IO0** button , While still pressing the **IO0** button
   3. Press **RST** button
   4. Release the **RST** button
   5. Release the **IO0** button
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

[2]: https://item.szlcsc.com/datasheet/DW06D%252FJ/83278.html?spm=sc.it.pdf.fd___sc.gbn.xh1.zy.n&lcsc_vid=QgRWVldWE1dZAwECQFUMVgYHFFRdXlxWRlELVFQFTgMxVlNTT1hdUldfQ1JeXjsOAxUeFF5JWBYZEEoEHg8JSQcJGk4%3D

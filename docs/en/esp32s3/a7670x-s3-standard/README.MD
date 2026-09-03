<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo T-A7670X-S3-Standard🌟</h1>

<div align="center">

[English](./README.MD) | [中文](../../../cn/esp32s3/a7670x-s3-standard/README.MD)

</div>

## Overview

* This page introduces the hardware parameters related to `LilyGo T-A7670X-S3-Standard`

### Product

| Product                   | SOC              | Flash          | PSRAM         |
| ------------------------- | ---------------- | -------------- | ------------- |
| [T-A7670X-S3-Standard][1] | ESP32-S3-WROOM-1 | 16MB(Quad-SPI) | 2MB(Quad-SPI) |

[1]: https://lilygo.cc/products/t-sim-t-a-series-standard-edition?variant=52513685471413


### Modem differences

| Model           | GPS | Phone Call | SMS | Frequency band                                                                                                     |
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
> How to check the specific model version of the modem? Sending AT+SIMCOMATI can return the firmware version and hardware version used.
>
> Please note that whether the GNSS IPEX antenna connector is on the PCB or not depends on the actual modem version. The A7670G modem does not have internal GPS functionality, regardless of whether GPS is included in your order. If you purchased the A7670G with GPS, you will need to use an external GPS module.
> A7670G+GPS orders use an external GPS module and can only use [S3_StandardSeries_External_GPS_Shield Example](../../../../examples/S3_StandardSeries_External_GPS_Shield/S3_StandardSeries_External_GPS_Shield.ino). Other GPS examples cannot be used.
> 
> The image below clearly shows that if a GPS module is included on the side, then it's a version with an external GPS module.

<img src="../../../../images/product/png/H799-01-T-A7670X-S3-Standard-GPS.png" alt="T-A7670X-S3-Standard-GPS" width="320" style="border: 0;"/>


### PlatformIO Quick Start

1. Install [Visual Studio Code](https://code.visualstudio.com/) and [Python](https://www.python.org/)
2. Search for the `PlatformIO` plugin in the `Visual Studio Code` extension and install it.
3. After the installation is complete, you need to restart `Visual Studio Code`
4. After restarting `Visual Studio Code`, select `File` in the upper left corner of `Visual Studio Code` -> `Open Folder` -> select the `LilyGo-Modem-Series` directory
5. Wait for the installation of third-party dependent libraries to complete
6. Click on the `platformio.ini` file, and in the `platformio` column
7. Cancel the `;` symbol in front of the line `default_envs = T-A7670X-S3-Standard` and use `T-A7670X-S3-Standard` as the default environment
8. Uncomment one of the lines `src_dir = xxxx` to ensure that only one line is valid. For example, to enable `src_dir = examples/ATdebug`, remove the leading `;` symbol and save the file. The ATDebug example will now be compiled.
9. Click the (✔) symbol in the lower left corner to compile
10. Connect the board to the computer `ESP-USB` , `Modem-USB` is used for module firmware upgrade
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
    | PSRAM                                | **QSPI PSRAM**                      |
    | Upload Speed                         | 921600                              |
    | Programmer                           | **Esptool**                         |

     * `Partition Scheme` Please select according to the actual application. For example, select **16M Flash (3MB APP/9.9MB FATFS)** , For more partitioning schemes, please see [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/partition-tables.html)

6. In the open sketch, select the `utilities.h` file and uncomment the line `// #define LILYGO_A7670X_S3_STAN`. Delete the `//` and save the file to use this board as the default configuration.

   ![board_select](../../../static/board_select.jpg)

7. Upload sketch

> \[!IMPORTANT]
>
> 1. Unable to upload any code? Please see the FAQ below
> 2. When opening the Arduino IDE, you will be prompted that there are new libraries that can be updated. Please do not click update. There is no guarantee that it can be compiled, run, etc. after the update. Make sure that the board is running normally before deciding whether to update. You have to Know that problems may occur after updating due to library differences, or the default configuration (such as TinyGSM) will be overwritten.
> 3. If it runs abnormally after the update, please follow Article 3 of the Arduino Quick Start to delete the directory in libraries, and drag the folder in lib into the libraries directory again.

### 📍 Pins Map

| Name              | GPIO NUM             | Free |
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
| Battery ADC Pin   | 8                    | ❌    |
| Solar ADC Pin     | 18                   | ❌    |
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

### Modem Pins

| Name                         | GPIO NUM | Enable level | AT Command                     |
| ---------------------------- | -------- | ------------ | ------------------------------ |
| GPS Ant Power Enable         | 1        | High         | `AT+CGDRT=1,1 ; AT+CGSETV=1,1` |
| Audio power amplifier Enable | 3        | High         | `AT+CGDRT=3,1 ; AT+CGSETV=3,1` |

> [!IMPORTANT]
> 🚨 **Before using GPS/GNSS, you must configure modem GPIO1 as an output and drive it HIGH by sending `AT+CGDRT=1,1; AT+CGSETV=1,1`; otherwise, the modem cannot obtain a position fix. Disable the antenna power with `AT+CGDRT=1,1; AT+CGSETV=1,0` when GPS/GNSS is not in use.**

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

| Features                        | Details   |
| ------------------------------- | --------- |
| 🔗USB-C input voltage range      | 4.5V~5.5V |
| 🔗VBUS Pin input voltage range   | 4.5V~5.5V |
| ⚡Solar Input Voltage            | 5 ~ 6V    |
| ⚡USB-C/Solar Charge Max Current | 500mA     |
| 🔋Battery Voltage                | 3.7V      |
| 🔋Battery socket voltage range   | 3.4~4.3V  |
| 📍**VBUS** ( Pin header)         | 5V        |
| 📍**VBAT** ( Pin header)         | 4.2V      |

* The minimum voltage of battery power supply depends on the discharge capacity of the battery. The minimum power supply voltage test using a voltage regulator can be as low as 2.7V (due to the low voltage stability of the voltage regulator)
* The VBUS pin is on the same line as the USB-C port. When connected to USB-C, the VBUS pin will also have voltage. The VBUS pin can only be used for external power input and will not provide power to the outside.

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

| Features                | Details  |
| ----------------------- | -------- |
| Over-Voltage Threshold  | 4.30V    |
| Under-Voltage Threshold | 2.4V     |
| Over-Charge Current     | 3.6A     |
| Over-Discharge Current  | 4.6A     |
| Short-Circuit Current   | 2 × 4.6A |

> \[!IMPORTANT]
> Please note that the development board will not power on when connected to an 18650 battery. To activate battery power, you can use the following method to activate the BMS.
>
> Method: Plug into the USB-C port labeled ESP-USB. Please note that the Modem-USB port will not power or charge the development board.
>
> Please note that even if the power switch is off, you still need to activate the BMS as described above to power the development board.
> If you briefly turn the power switch off, turning it back on will also reconnect the battery power, eliminating the need to reconnect the USB port to activate the BMS.

### Connector Description

| Button                     | Function                      | Location   |
| -------------------------- | ----------------------------- | ---------- |
| JST 1.0mm `SPEK`           | Connect speakers              | PCB Bottom |
| JST 1.0mm `MIC`            | Connect condenser microphone  | PCB Bottom |
| JST 1.0mm `RTC`            | Connect 3~3.3V button battery | PCB Bottom |
| JST 2.0mm `Solar`          | Connect to a 5~6V solar panel | PCB Top    |
| 24 Pin 0.5mm FPC Connector | Connect OV2640/OV5640 camera  | PCB Top    |
| QWIIC                      | I2C Interface                 | PCB Bottom |
| QWUART or QWIIC            | UART or I2C Interface         | PCB Bottom |

* Camera models support cameras supported by esp32 platform
* `QWIIC I2C` : Fixed to I2C interface, cannot be changed to other functions , Examples see [QWIIC_I2C_Scan.ino](../../../../examples/QWIIC_I2C_Scan/QWIIC_I2C_Scan.ino)
* `QWIIC UART` : The default is ESP serial output, which can also be changed to the second I2C interface, I2C Example see [QWIIC_I2C_Scan.ino](../../../../examples/QWIIC_I2C_Scan/QWIIC_I2C_Scan.ino) / , Uart example see [QWIIC_UART_loopback.ino](../../../../examples/QWIIC_UART_loopback/QWIIC_UART_loopback.ino)
* `JST 2.0mm Solar` : This is the solar panel voltage input interface. This interface is only used as a solar or external power charging interface. It cannot be used to provide power to the motherboard after removing the battery.
* `JST 1.0mm SPEK`: This is the external speaker interface, the maximum output power of this interface is 8 ohms 1W
* `JST 1.0mm MIC`: This is an external condenser microphone interface for calls. The condenser microphone is directly connected to the modem. Only condenser microphones can be used, not digital microphones.
* `JST 1.0mm RTC`: This is the GPS backup power battery interface. If you do not connect this battery, the GPS will not have the hot start function. Connecting a battery to this interface will enable the GPS hot start function.

#### Bottom JST Connecter

![H799-01-T-A7670X-S3-Standard-bottom](../../../../images/product/png/H799-01-T-A7670X-S3-Standard-bottom.png)

### Button Description

| Button               | Function                            | Location   |
| -------------------- | ----------------------------------- | ---------- |
| BOOT  (ESP32S3 back) | Customizable function/Download mode | PCB Bottom |
| RST   (ESP32S3 back) | Reset devices button                | PCB Bottom |
| SBOOT(Near to modem) | Modem Upgrade mode                  | PCB Bottom |

* **RST** and **BOOT** Located on the bottom of the ESP32 module
* **SBOOT** is located on the back near the modem module
* Press and hold the `BOOT` button before powering on. The board is now in waiting mode for downloading.
* Before powering on, keep the `SBOOT` button pressed to put the modem into firmware update mode.
* The above naming method is subject to the board silk screen printing

### Antenna Description

| NAME | Function                     |
| ---- | ---------------------------- |
| LTE  | LTE Main antenna interface   |
| GNSS | GPS active antenna interface |

* When using, you only need to connect the LTE antenna you wear to the LTE IPEX first generation interface. The AUX antenna does not need to be connected.
* The above naming method is subject to the board silk screen printing

### LED Description

| FUNCTION        | COLOR                            | STATE                                                                  |
| --------------- | -------------------------------- | ---------------------------------------------------------------------- |
| MODEM STATE     | RED   (Near the modem)           | Startup:ON                                                             |
| MODEM NET       | RED   (Near the modem)           | Network status indicator                                               |
| GPS PPS LED     | RED  (Near the modem)            | Starting:ON,Startup completed:OFF,Position fix:Flashes once per second |
| CHARGE LED      | RED  (Near the battery switch)   | Charging:ON  Charging complete:OFF                                     |
| CHARGE DONE LED | GREEN  (Near the battery switch) | Charging:OFF  Charging complete:ON                                     |

* `CHARGE DONE LED` remains on if no battery is connected
* Modem Status light and network status led cannot be turned off

### eSIM

<img src="../../../../images/product/png/eSIM-Chip.png" alt="eSIM" width="480" style="border: 0;"/>

<img src="../../../../images/product/png/eSIM.png" alt="eSIM" width="480" style="border: 0;"/>

* The eSIM uses a QFN5*6-8 package and supports 1.8V/3.3V. It's not installed by default and requires soldering.

### Resource

* [GPS Antenna](../../../../datasheet/GPS%20Antenna%20Specifications.pdf)
* [LTE Antenna](../../../../datasheet/LTE%20Antenna%20Specifications.pdf)
* [T-A7670X-S3-Standard Schematic](../../../../schematic/standard/T-A7670X-S3-Standard_Rev1.0.pdf)
* [SIMCOM official A7670X All Datasheet](https://cn.simcom.com/product/A7670X.html)
* [For A7670X series documentation, please visit the datasheet directory.](../../../../datasheet/A7670X/)
* [L76K GPS Module datasheet](../../../../datasheet/GPS/)
* [3D](../../../../dimensions/Standard/T-A7670X-S3-Standard.7z)
* [Dimensions svg](../../../../dimensions/Standard/T-SIM7060G%20and%20A7670-S3-Standard.svg)

### FAQ

* **Upgrade modem firmware**
  1. [T-A76XX Upgrade docs](../../../../docs/update_fw.md) / [Video](https://youtu.be/AZkm-Z7mKn8)

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
  3. To activate battery power, please see the `Battery Protector Description` above.

* **About VBUS Pin**
  1. VBUS Pin and USB-C are on the same line. Only when USB-C is connected, VBUS has voltage
  2. When only the battery is connected, VBUS has no voltage output
  3. If you want to connect an external power supply without connecting USB-C, VBUS Pin is the only voltage input pin. Please note that the maximum input of VBUS Pin is 5V, do not exceed 5V

* Can other GPS antennas be used?
  1. The external GPS antenna must be an active GPS antenna with a 3.3V power supply. For example, the [MK-76](https://www.rfmw.com/datasheets/sanav/mk-76.pdf) supports 2.5-5.5V and is compatible. Most active GPS antennas support 2.5-5.5V power. Please refer to the GPS antenna datasheet for details.

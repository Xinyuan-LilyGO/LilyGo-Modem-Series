
<div align="center" markdown="1">
  <img src="../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo A7670/A7608 Upgrade Guide🌟</h1>

<div align="center">

[English](./update_fw.md) | [中文](./cn/update_fw.md)

</div>

# Prerequisites

## Driver

* [Windows USB Drivers](https://drive.google.com/drive/folders/1-7x2z00a5VO7GZS96C6mDupNTBXIh--H?usp=sharing)

## FlashTools

> \[!IMPORTANT]
> [A76XX_A79XX_MADL V1.13 Only for Update] HAS BUG DON'T USE THIS TOOL ,PLEASE USE V1.32 VERSION UPDATE TOOLS
>
> Before upgrading, please send "AT+SIMCOMATI" to check the hardware version. If the wrong version of firmware is written, the modem may be damaged.

* [A7670X//A7608X Flash Tools](https://drive.google.com/file/d/12nt5-wcsUT6bRaEhfOMBSq0EhOl8R2by/view?usp=sharing)
* [SIM7670G Flash Tools](https://drive.google.com/file/d/1-CHQOXQhCJRr1S8rP_AGHVWGqE823wem/view?usp=sharing)

## Firmware

### A7670E-LNMV No GPS,No Voice,No SMS

* [🆕 A7670E-LNMV 23156B02A7670M5A_A7670E-LNMV_V101240423](https://drive.google.com/file/d/1nDTdMgSrb2Ku2NUtOZaKzZO6MYJnj4l-/view?usp=sharing)

### A7670E-LNXY-UBL No GPS,No Voice,No SMS

* [A7670E-LNXY-UBL 23124B03](https://drive.google.com/file/d/12i1YNPVsygzwKhNnboiGVRn_nG6QulQA/view?usp=sharing)

### A7670G-LLSE No GPS

<!-- * [A7670G B18](https://drive.google.com/file/d/10BxF-O2aPQ9vB5N97VT3bxPguURNoMvF/view?usp=sharing) Known HTTP 715 Errors Don't use this version- -->
* [A7670G-LLSE A124B01](https://drive.google.com/file/d/1-UOq_7TxU8aNAY4KKuXtnoRt0UZwipSQ/view?usp=sharing)

<!-- (LTE-FDD B1/B2/B3/B4/B5/B7/B8/B12*/B13*LB18*/B19*/B20/B25*/B26*/B28/B66/ LTE-TDD B34/B38/B39/B40/B41 GSM/GPRS/EDGE 850/900/1800/1900 MHz) -->

### A7670G-LABE No GPS

* [A7670G-LABE A069B01](https://drive.google.com/file/d/10oSTTqhw7ZiiZ_LiqAb3WYV3LXwbpKtV/view?usp=sharing)
* 🆕[A7670G-LABE A110B06](https://drive.google.com/file/d/10fsorFI8SuTlcffufgphpYbt2JjUpqtg/view?usp=sharing)

<!-- (LTE-FDD B1/B2/B3/B4/B5/B7/B8/B20B28/B66/ LTE-TDD B34/B38/B39/B40/B41 GSM/GPRS/EDGE 850/900/1800/1900 MHz) -->

------------------------

### A7670E-LASE No GPS

<!-- * [A7670E-LASE B14](https://drive.google.com/file/d/1ERblToPH4FoAo2dVYn3B--u_FzhIzeMQ/view?usp=sharing) Known HTTP 715 Errors Don't use this version-->
* [A7670E-LASE A124B01](https://drive.google.com/file/d/1-14KABQxVgjcJjJVuofp1BkZd0VYZVWA/view?usp=sharing)<!-- 20241008 Update Fixed  HTTP 715 error-->
* 🆕[A7670E-LASE A124B02](https://drive.google.com/file/d/1PJ6xogfZqH1fFin-V_Mio9rExiVIL-lz/view?usp=sharing)

------------------------

### A7670E-FASE GPS

<!-- A011B07V01A7670M7_F_A7670E-FASE_CD_V101230711 -->
* [A7670E-FASE A011B07V01A7670M7](https://drive.google.com/file/d/1-5A9w4MCXNz6F5ODhynne0rC9IUOeOdH/view?usp=sharing)<!-- 20241008 Update Fixed  HTTP 715 error-->
* 🆕[A7670E-FASE A011B09A7670M7](https://drive.google.com/file/d/1xLY0xmofZpixy3Rd_NGj4DkoVnh_U3tP/view?usp=sharing)<!-- Fix MQTTS TLS : https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/issues/515-->

------------------------

### A7670SA-FASE GPS

<!-- A011B07V01A7670M7_F_A7670SA-FASE_CD_V101230712 -->
* [A7670SA-FASE-A011B07V01A7670M7](https://drive.google.com/file/d/1-CcYlyPOYpIpcmSDjnfIXDE-GuazzLjO/view?usp=sharing) <!-- 20241009 Update Fixed  HTTP 715 error-->
<!-- A011B09A7670M7_F_A7670SA-FASE_CD_V101230712.rar -->
* 🆕[A7670SA-FASE-A011B09A7670M7](https://drive.google.com/file/d/1nyIHD29vpMsm7do0SJIF8WNhXoop1K2V/view?usp=sharing)

------------------------

### A7670SA-LASE No GPS

* [A7670SA-LASE B19](https://drive.google.com/file/d/1-evoE-qTLzQEG3OrGdrq9SVuDxEVGHeQ/view?usp=sharing)

### A7670SA-LASC No GPS

* [A7670SA-LASC B01](https://drive.google.com/file/d/127FpmjV9TNFJcNEUK03X03sGpGGqFc-u/view?usp=sharing)

------------------------

### SIM7670G-MNGV

See [LilyGo SIM7670G Upgrade Guide](./en/upgrade/sim7670g/sim7670g_upgrade.md)

------------------------

### A7608E-H

<!-- * [A7608E-H B11](https://drive.google.com/file/d/1IfNkPfQmfG3oqbXEZl0YD_9qgLsN4e_D/view?usp=sharing) -->
* [A7608E-H B14](https://drive.google.com/file/d/1NNixH5VYale9fS1JkHSBdoM-KiiMboWY/view?usp=sharing)

------------------------

### A7608SA-H

* [🆕A7608SA-H A81C4B02A7600M7_T_A7608SA-H_V102250213](https://drive.google.com/file/d/1eIXt-tPJz9cF25YVeCH47hbQj1X1p2GS/view?usp=sharing)
* [A7608SA-H A81C4B01A7600M7_T_A7608SA-H_V102250213](https://drive.google.com/file/d/1lf7EFa7uaI9fyr25b4Ik2SW36P-22rWG/view?usp=sharing)
* [A7608SA-H A50C4B11V01A7600M7_A7608SA-H_V102220719](https://drive.google.com/file/d/1ktLzCjnd0TXzbiythU1EaWVkAokXzkf9/view?usp=sharing)
* [A7608SA-H A50C4B13A7600M7_A7608SA-H_V102240329](https://drive.google.com/file/d/1-LsgDug-Zz_0kU96HlCGtfks3ruvjcQb/view?usp=sharing)

> \[!IMPORTANT]
>
> The A7608 series requires a dedicated driver to be installed in boot mode; please see [here](https://github.com/Xinyuan-LilyGO/LilyGo-Modem-Series/issues/405#issuecomment-3575374939)
>
> Driver Directory: `A76XX_A79XX_MADL V1.32 Only for Update` -> `A1802&1803&1826Driver`

------------------------

**Please provide the information in the QR code on the modem to LilyGo to confirm the firmware version.**

> \[!IMPORTANT]
> Steps to enter upgrade mode
>
> 1. Press and hold the SBOOT button close to the modem and do not release it.
> 2. Plug in MICRO-USB
> 3. Plug in USB-C
> 4. Check the device manager and wait for the computer port to be generated
> 5. Release the SBOOT button after the port is identified

### Record Video

* [SIM7670G Upgrade Record](https://youtu.be/wTcMp0K8fXY)
* [A7670XX Upgrade Record](https://youtu.be/AZkm-Z7mKn8)


### Log capture

* [SIM7670G Capture Log Record](https://youtu.be/4vvNANhz86A)
* [A7670XX Capture Log Record](https://youtu.be/31MUyhX5UHs)



### Firmware Update Procedure

1. Upload [ATDebug_sketch](../examples/ATdebug/ATdebug.ino)
2. Press and hold the button next to the modem, then plug in the MicroUSB port
   ![](../images/upgrade/boot_pin.jpg)
   
3. Open the device manager of the computer, and then follow the instructions below to install all unknown drivers

   ![](../images/upgrade/step2.jpg)
   ![](../images/upgrade/step3.jpg)
   ![](../images/upgrade/step4.jpg)
   ![](../images/upgrade/step5.jpg)

    Repeat the above operations to complete the installation of all other device drivers

4. Open `A76XX_A79XX_MADL V1.13 Only for Update.exe`
5. Choose to upgrade the firmware according to the steps in the figure below
   ![](../images/upgrade/step1.jpg)
6. Click GO Button , Wait for the progress bar to complete.
   ![](../images/upgrade/step6.jpg)

7. After the firmware is updated, you can send `AT+SIMCOMATI` to check the version

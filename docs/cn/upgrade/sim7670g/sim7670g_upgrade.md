
<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo SIM7670G 升级指南🌟</h1>

<div align="center">

[English](../../../en/upgrade/sim7670g/sim7670g_upgrade.md) | [中文](./sim7670g_upgrade.md)

</div>

---

## 资源

### `0` SIM7670G 固件更新指南视频

- [💠SIM7670G 固件更新指南视频](https://youtu.be/wTcMp0K8fXY)

### `1`刷机工具

- [SIM7670G UpgradeTools](https://drive.google.com/file/d/19M-_COv_gkZ9KBwzqfWTWWJSYUEjOK8-/view?usp=sharing)

> \[!IMPORTANT]
> 请不要使用旧版本的刷机工具，因为它们在某些电脑上无法选择端口。
>
> 如果使用旧版本FlashTools，千万不要勾选EraseAll,否则会造成射频丢失导致modem无法工作,LilyGo 不推荐使用旧版FlashTools


### `2`驱动

- [SIM7670G 驱动](https://drive.google.com/file/d/1-SlbQ9FUZzov96Xc74SJ375U9v1JVjma/view?usp=sharing)

### `3`固件（兼容 LilyGo SIM7670G 和所有不同 PN 编号的调制解调器）

<!-- * ~~[SIM7670G B02](https://drive.google.com/file/d/1-63xiw4TbGwHi3rQDzJpPKwp2SDNPXC1/view?usp=sharing) Known HTTP 715 Errors Don't use this version~~  -->
- [🟡2374B03SIM767XM5A](https://drive.google.com/file/d/1bBrze2eDtrjEuJ_2yiufSo87eIk_mYkE/view?usp=sharing) <!-- 20241008 Update Fixed  HTTP 715 error-->
- [🟡2374B04SIM767XM5A](https://drive.google.com/file/d/1-akwKQJttLbtLD48ApagusfBvS9ixZ4F/view?usp=sharing)
- [🟢稳定版:2374B05V01SIM767XM5A](https://drive.google.com/file/d/10VvMNzgKhAX25lHSIGHnD3ip7kWjFl0g/view?usp=sharing) <!-- 20241206 Fixed MQTTS error https://github.com/Xinyuan-LilyGO/LilyGO-T-A76XX/issues/183 , HTTPS MQTTS FIXED -->
- [🔴2388B03SIM767XM5A 不推荐使用；存在很多问题。](https://drive.google.com/file/d/1_Gwj3v_6NCtC-6xQ8dGSrjayTFRJyVgu/view?usp=sharing)
- [🟡:2388B04SIM767XM5A_M_SIM7670G-MNGV_V202250121](https://drive.google.com/file/d/1VCdWaWFyk2PfM0WGyceXML_7lgFYbyWe/view?usp=sharing)
- [🟣最新:2397B01SIM767XM5A_M_SIM7670G-MNGV_V202260204](https://drive.google.com/file/d/149J1sh5L-iGmuGjyTjAG6a75QdGARiro/view?usp=sharing)

> \[!IMPORTANT]
>
> 注意：如果软件更新未在指定时间内进行，调制解调器将自动退出更新模式。此时，您需要按住调制解调器的 BOOT 按钮重新进入下载模式。
>

# 更新步骤

1. 确定 ESP32 的 USB 端口号。在设备管理器中查看。仅连接 ESP32 的 Type-C 端口并记下端口号。

2. 烧写 [ATDebug](../../../../../examples/ATdebug/ATdebug.ino) 并发送 `AT+SIMCOMATI` 检查当前固件版本。

3. 断开 ESP32 的 USB 端口与电脑的连接。

4. 连接 MicroUSB 端口（SIM7670G-S3 系列使用 MicroUSB；SIM7670G-S3-Standard 系列使用 Modem-USB）。

5. 按住调制解调器的 BOOT 按钮（SIM7670G-S3 系列的 BOOT 按钮在 MicroUSB 端口附近；SIM7670G-S3-Standard 系列的 BOOT 按钮在调制解调器背面）。

6. 连接 ESP32 Type-C 端口。

7. 在设备管理器中检查调制解调器的端口号；它将与 ESP32 的端口号不同。

8. 在软件中选择要升级的固件文件。

![upgrade1](../../../en/upgrade/sim7670g/images/upgrade-1.png)

![upgrade2](../../../en/upgrade/sim7670g/images/upgrade-2.png)

9. 打开升级工具并选择调制解调器的端口号。

10. 拔掉 ESP32 的 Type-C 数据线，然后重新连接。升级将自动开始。

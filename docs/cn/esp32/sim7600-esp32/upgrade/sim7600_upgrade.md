
<h1 align = "center">🌟SIM7600 调制解调器固件更新指南🌟</h1>

<div align="center">

[English](../../../../en/esp32/sim7600-esp32/upgrade/sim7600_upgrade.md) | [中文](./sim7600_upgrade.md)

</div>

---

### 录制视频

* [SIM7600G 升级录制](https://www.youtube.com/watch?v=7cJzjfcrFWY&t=10s)

#### 1. 下载驱动和工具

* [Windows USB 驱动](https://drive.google.com/file/d/1WhHny4E-43DxUfifMkrX752oFBx7O70D/view?usp=sharing)
* [升级固件工具](https://drive.google.com/file/d/1f02TTNoyirFPGWbob1khy9dnoBonoVe7/view?usp=sharing)
* [升级录制视频](https://youtu.be/7cJzjfcrFWY)

**刷写的固件版本必须与调制解调器的 PN 编号一致，否则将变砖。**

##### SIM7600G-H

* [LE20B04SIM7600G22](https://drive.google.com/file/d/11_gPJxy2CcXCrJPNfeUXDacKbT5_-F_F/view?usp=sharing)
* [LE20B05SIM7600G22](https://drive.google.com/file/d/12BMSSGPISMhFEDvG7C9s34YvWg5PDNNb/view?usp=sharing)
* 🆕[LE20B06SIM7600G22](https://drive.google.com/file/d/1MLpxBzHmjrrZPA_1t-G_S4TTTWm4NLD-/view?usp=sharing)

###### SIM7600E-H

* **Suitable for modems with the prefix PN: S2-107EQ-XXXXX**

* 🆕[LE11B14SIM7600M22](https://drive.google.com/file/d/1kHsw8LXSm2FYmcSWsaYiS7G8vvF9q2No/view?usp=sharing)

###### SIM7600E-L1C

* **Suitable for modems with the prefix PN: S2-10A9C-XXXXX**

* 🆕[LE20CB03SIM7600M11](https://drive.google.com/file/d/1huASLR3t2F_hZx7m92I-onnwKCmGh8fU/view?usp=sharing)

#### 2. 将 USB 输入切换到调制解调器

1. 将 USB 背面的 DIP 开关拨到下图所示位置

   <img  height="320" width="240" src=../images/USB.png>

2. 将 Type-C 连接到调制解调器接口，即下图中的 `USB interface`

   <img  height="290" width="640" src=../images/step9.png>

### 3. 安装驱动

1. 打开电脑设备管理器，当前升级仅支持 Windows

   <img  height="500" width="650" src=../images/update_simxxxx_3.png>
   <img  height="500" width="650" src=../images/update_simxxxx_4.png>
   <img  height="500" width="650" src=../images/update_simxxxx_6.png>

2. 重复上述过程完成其他设备列表中所有驱动的安装。此时不要关闭设备管理器。在更新过程中出现未知设备时，继续按照上述方法更新驱动

### 4. 获取当前固件版本

1. 上传 [ATDebug Sketch](../../../../../examples/ATdebug/ATdebug.ino)，此步骤是为了确保调制解调器正常启动

2. 在升级之前，请发送 `AT+SIMCOMATI` 检查硬件版本，写入错误版本的固件将导致调制解调器变砖

   <img  height="400" width="700" src=../images/version.png>

3. 请提供调制解调器上二维码中的信息给 LilyGo 以确认固件版本，或在 issue 中提交

### 5. 升级固件步骤

1. 打开 `sim7080_sim7500_sim7600_sim7900_sim8200 qdl v1.67 only for update.exe`
2. 按照以下说明更新固件

   <img  height="400" width="800" src=../images/step1.png>

   <img  height="400" width="800" src=../images/step2.png>

   <img  height="500" width="800" src=../images/step3.png>

   <img  height="400" width="800" src=../images/step4.png>

   <img  height="1000" width="800" src=../images/step5.png>

   <img  height="800" width="800" src=../images/step6.png>

   <img  height="400" width="800" src=../images/step7.png>

### 6. 固件更新完成后，您可以发送 `AT+SIMCOMATI` 检查版本

   <img  height="1000" width="800" src=../images/step8.png>

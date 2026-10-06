<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo T-BAT 使用指南🌟</h1>

<div align="center">

[English](../../../en/shield/t-bat/README.MD) | [中文](./README.MD)

</div>

---

<div align="center" markdown="1">
  <img src="../../../../images/product/png/T-BAT.png" alt="t-bat" width="480"/>
</div>

### ⚡ 电气参数

| 特性                           | 详情     |
| ------------------------------ | -------- |
| USB 输入电压                   | 4.5~5.5V |
| 太阳能输入电压                 | 4.5 ~ 6V |
| 电池接口允许输入电压           | 4.2V     |
| 电池类型                       | 仅限单节可充电锂离子/锂聚合物（Li-ion/LiPo）电池（充满电压 4.2 V） |
| MicroUSB/太阳能充电最大电流    | 500mA    |
| USB OUT                        | 1A       |

> \[!IMPORTANT]
>
> 请勿在本设备中使用或充电磷酸铁锂（LiFePO4）电池，或任何充满电压不是 4.2 V 的电池；本设备仅支持充满电压为 4.2 V 的单节可充电锂离子/锂聚合物电池。

### ⚡ 电池保护器说明

| 特性               | 详情       |
| ------------------ | ---------- |
| 过压阈值           | 4.30V      |
| 欠压阈值           | 2.4V       |
| 过放电电流         | 3A         |
| 芯片名称           | [DW06D][2] |

### 按钮说明

* 首次上电或电池保护触发时，按下按钮将恢复电池输出功能。

### LED 说明

| 功能             | 颜色 | 状态                                                     |
| ---------------- | ---- | -------------------------------------------------------- |
| 太阳能指示灯     | 黄色 | 输入反接时灯常亮，输入正常连接时熄灭。                   |
| 电池指示灯       | 黄色 | 输入反接时灯常亮，输入正常连接时熄灭。                   |
| 5V 输出指示灯    | 绿色 | 5V 输出灯常亮，关闭时熄灭。                              |
| 充电指示灯       | 绿色 | 充满时灯常亮，充电时熄灭                                 |
| 充电指示灯       | 红色 | 充电时灯亮，充满时熄灭。                                 |

## 原理图

[T-BAT-Rev1.0 原理图](../../../../schematic/shield/T-BAT-Rev1.0.pdf)


[2]: https://item.szlcsc.com/datasheet/DW06D%252FJ/83278.html?spm=sc.it.pdf.fd___sc.gbn.xh1.zy.n&lcsc_vid=QgRWVldWE1dZAwECQFUMVgYHFFRdXlxWRlELVFQFTgMxVlNTT1hdUldfQ1JeXjsOAxUeFF5JWBYZEEoEHg8JSQcJGk4%3D

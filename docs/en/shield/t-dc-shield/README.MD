<div align="center" markdown="1">
  <img src="../../../../.github/LilyGo_logo.png" alt="LilyGo logo" width="100"/>
</div>

<h1 align = "center">🌟LilyGo T-SimDcShield Usage Guide🌟</h1>

<div align="center">

<!-- [English](./README.MD) | [中文](../../../cn/shield/t-bat/README.MD) -->

</div>


<div align="center" markdown="1">
  <img src="../../../../images/product/png/H812-DC-Shield.png" alt="t-bat" width="480"/>
</div>

> \[!IMPORTANT]
> The T-SimDcShield was designed for multi-SIM motherboard compatibility. Currently, the version sold only supports direct use with Standard-Series motherboards and does not differentiate between Motherdem models. For other motherboards, the rear resistors must be modified for compatibility.

### I2C

| PCB Label | Standard-Series GPIO |
| --------- | -------------------- |
| SDA       | 3                    |
| SCL       | 2                    |

### Grove: Analog Input

| PCB Label | Standard-Series GPIO |
| --------- | -------------------- |
| A0        | 14                   |
| G0        | GND                  |
| A1        | 9                    |
| G1        | GND                  |

* The analog input can be changed to high-side or low-side by cutting the pads. By default, G0 and G1 are connected to GND, and the adjustable resistor is 3V3.

### Grove: Digital Input/Output

| PCB Label | Standard-Series GPIO |
| --------- | -------------------- |
| D0        | 16                   |
| G1        | GND                  |
| D1        | 15                   |
| G1        | GND                  |

### Grove interface model?

Connector interface type: HY2.0-4P

![HY2.0-4P](./images/HY2.0-4P.png)

### Battery input and 5V voltage output interface

Connector interface type: XH 2.54-4P

<div align="left" markdown="1">
  <img src="./images/interface.png" alt="t-bat" width="480"/>
</div>


### ⚡ Electrical parameters

| Features                               | Details                      |
| -------------------------------------- | ---------------------------- |
| DC input voltage                       | 7~36V / 3A                   |
| Battery interface allows input voltage | 4.2V                         |
| Battery Type                           | Single-cell rechargeable Li-ion/LiPo (4.2 V full-charge) |
| MicroUSB/Solar Charge Max Current      | Determined by the base plate |
| Battery Protector                      | Determined by the base plate |

> \[!IMPORTANT]
>
> Do not use or charge LiFePO4 batteries, or any battery with a full-charge voltage other than 4.2 V, in this device. This device supports only single-cell rechargeable Li-ion/LiPo batteries with a 4.2 V full-charge voltage.

### LED Description

| FUNCTION      | COLOR | STATE                                             |
| ------------- | ----- | ------------------------------------------------- |
| 5V  indicator | RED   | On: Normal; Off: No power supply, uncontrollable. |
| 3V3 indicator | RED   | On: Normal; Off: No power supply, uncontrollable. |

### Analog Input

The analog input can be changed to high-side or low-side by cutting the pads. By default, G0 and G1 are connected to GND, and the adjustable resistor is 3V3.

<div align="left" markdown="1">
  <img src="./images/solder-pads.png" alt="t-bat" width="480"/>
</div>


## Schematic

[T-SimDcShield-Rev1.0 schematic](../../../../schematic/shield/T-Sim-DC-Shield-Rev1.0.pdf)

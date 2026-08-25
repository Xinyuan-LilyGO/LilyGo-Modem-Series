<div align="center">

[English](./model_comparison.md) | [中文](./cn/model_comparison.md)

</div>

## Model Comparison

| Product                        | Module                   | QWIIC | Seamless <br> power <br> switching | GNSS<br> routing<br> to SOC | GNSS<br>PPS | eSIM<br>Pad | BMS | Camera<br>Interface | DeepSleep<br> Current | Pin<br>compatible |
| ------------------------------ | ------------------------ | ----- | ---------------------------------- | --------------------------- | ----------- | ----------- | --- | ------------------- | --------------------- | ----------------- |
| T-A7670X                       | ESP32-WROVER-B(N4R8)     | ❌     | ❌                                  | ❌                           | ❌           | ❌           | ✅   | ❌                   | N.A                   | ❌                 |
| T-A7608X                       | ESP32-WROVER-B(N4R8)     | ❌     | ❌                                  | ❌                           | ❌           | ❌           | ✅   | ❌                   | N.A                   | ❌                 |
| T-SIM7000G                     | ESP32-WROVER-B(N4R8)     | ❌     | ❌                                  | ❌                           | ❌           | ❌           | ✅   | ❌                   | N.A                   | ❌                 |
| T-SIM7600G                     | ESP32-WROVER-B(N4R8)     | ❌     | ❌                                  | ❌                           | ❌           | ❌           | ✅   | ❌                   | N.A                   | ❌                 |
| T-SIM7080G-S3                  | ESP32-S3-WROOM-1(N16R8)  | ❌     | ❌                                  | ❌                           | ❌           | ❌           | ❌   | ✅                   | N.A                   | ❌                 |
| T-SIM7670G-S3                  | ESP32-S3-WROOM-1(N16R8)  | ❌     | ❌                                  | ❌                           | ❌           | ❌           | ✅   | ❌                   | N.A                   | ❌                 |
| T-A7608X-S3                    | ESP32-S3-WROOM-1(N16R8)  | ❌     | ❌                                  | ❌                           | ❌           | ❌           | ✅   | ❌                   | N.A                   | ❌                 |
| T-A7670X-S3<br>-**Standard**   | ESP32-S3-WROOM-1(NR16R2) | ✅     | ✅                                  | ✅                           | ✅           | ✅           | ✅   | ✅                   | N.A                   | ✅                 |
| T-SIM7670G-S3<br>-**Standard** | ESP32-S3-WROOM-1(NR16R2) | ✅     | ✅                                  | ✅                           | ✅           | ✅           | ✅   | ✅                   | N.A                   | ✅                 |
| T-SIM7000G-S3<br>-**Standard** | ESP32-S3-WROOM-1(NR16R2) | ✅     | ✅                                  | ✅                           | ❌           | ✅           | ✅   | ✅                   | N.A                   | ✅                 |
| T-SIM7080G-S3<br>-**Standard** | ESP32-S3-WROOM-1(NR16R2) | ✅     | ✅                                  | ✅                           | ❌           | ✅           | ✅   | ✅                   | N.A                   | ✅                 |
| T-SIM7600G-S3<br>-**Standard** | ESP32-S3-WROOM-1(NR16R2) | ✅     | ✅                                  | ❌                           | ❌           | ✅           | ✅   | ✅                   | N.A                   | ✅                 |

- ESP32-WROVER-B(N4R8): 4MB Flash , 8MB PSRAM
- ESP32-S3-WROOM-1(N16R8): 16MB Flash , 8MB PSRAM(Octal SPI)
- ESP32-S3-WROOM-1(N16R2): 16MB Flash , 2MB PSRAM(Quad SPI)
- The deep sleep current test record can be found in [DeepSleep.ino](../examples/DeepSleep/DeepSleep.ino)
- SIM7000G/SIM7080G/SIM7600G do not have PPS function, so this function is not available.

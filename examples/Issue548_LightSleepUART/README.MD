# Issue 548: T-SIM7600X UART Light-Sleep Test

This example verifies large `AT+CFTRANTX` responses on the `T-SIM7600X` using the standard SIMCom UART sleep/wake sequence. It is intentionally a reproducible test case, not an OTA application. The primary question is whether the SIM7600 transmits the response bytes; the ESP32-side counters are supporting observations only.

## Board and pins

Select `T-SIM7600X` in `platformio.ini`. The T-SIM7600X pins are defined directly in `Issue548_LightSleepUART.ino`:

| Signal | ESP32 GPIO |
| --- | ---: |
| Modem RX (ESP32 receives TXD) | 26 |
| Modem TX (ESP32 sends RXD) | 27 |
| DTR | 32 |
| RI | 33 |

The CH9102 console is the ESP32 control port. A SIM7600 USB AT port such as `COM190` is a separate USB interface and is not the GPIO26/27 UART tested here. `COM190` can be used to collect `AT+SIMCOMATI`/`AT+CGMR` or as a software comparison, but it cannot replace a capture of the modem TXD waveform on GPIO26.

## Build and upload

Temporarily select this example in the repository `platformio.ini`:

```ini
default_envs = T-SIM7600X
src_dir = examples/Issue548_LightSleepUART
```

Then build/upload in the normal way. The `.ino` file is standalone and can be opened directly in Arduino IDE with the ESP32 board package; it does not include `examples/ATdebug/utilities.h` or any repository example header.

## Test commands

Open the ESP32 console at 115200 baud:

- `r`: create `E:/issue548.bin`, a deterministic 4096-byte file;
- `b`: baseline, with DTR low and `AT+CSCLK=0`;
- `l`: standard light-sleep test.

The `l` sequence is:

1. send `AT+CSCLK=1` and pull DTR high;
2. wait 25 seconds for the modem sleep condition;
3. enter ESP32 light sleep;
4. after wake, rebuild `Serial1`, pull DTR low, and wait;
5. require `AT` -> `OK`, set `AT+CATR=1`, then send `AT+CSCLK=0`;
6. read eight 512-byte windows with `AT+CFTRANTX` and verify every byte. Build with `-DISSUE548_WINDOW_SIZE=1024` to reproduce the earlier 1024-byte-window test.

If DTR is not pulled low, or the application starts the large transfer before a clean `AT`/`OK` wake confirmation, it has not followed the SIMCom wake procedure and the result must be treated as an application-flow error.

At startup the example first sends `AT`. If there is no response, it performs the board-standard `BOARD_PWRKEY_PIN` pulse and waits for the SIM7600 startup interval before retrying. A run with `MODEM_READY=0`, no `AT` response, and no SIM7600 USB AT port enumeration is a modem power/connection precondition failure, not a long-response or FIFO-loss result.

For automatic logging from the repository root:

```powershell
python examples/Issue548_LightSleepUART/issue548_serial_runner.py --port COM227 --cycles 1
```

The runner toggles the CH9102 control-line RTS only to reset the ESP32, then sends `r`, `b`, and `l`, and stores a timestamped log next to the runner. This is unrelated to modem UART RTS/CTS flow control, which is not supported on this device.

## Diagnostic output

After every test window the example prints a line such as:

```text
DIAG window=0 rx=... first_us=... max_gap_us=... fifo_ovf=... buffer_full=... frame=... parity=...
```

`first_us` is the delay from the first byte observed after the transfer command. `max_gap_us` is the largest gap between bytes observed by the Arduino task. The error fields are deltas for that window, collected with `HardwareSerial::onReceiveError()`. `HardwareSerial` normally uses the Arduino-ESP32 interrupt-backed receive path; this is the default implementation, not a conclusion that the modem is innocent.

Interpretation:

- `DIAG` is an observation at the ESP32 application boundary. It cannot by itself identify a SIM7600 fault;
- to test the modem, connect a logic analyzer or independent USB-UART receiver to the SIM7600 TXD line (the board signal routed to GPIO26) and capture the command echo, the approximately 55 ms interval, and the first `+CFTRANTX` bytes;
- if the independent capture contains the missing header/data during the interval but the ESP32 log does not, the loss is in the ESP32 receive path;
- if the independent capture also starts in the middle of the response, the SIM7600 is the suspect and the capture should be sent to SIMCom with `AT+SIMCOMATI`/`AT+CGMR` output.

The startup line also prints the configured baud rate, RX buffer, RX FIFO threshold, and the compile-time `CONFIG_UART_ISR_IN_IRAM` visibility. The latter is host-side diagnostic information only and is not a modem test; changing a precompiled Arduino/ESP-IDF UART component requires a matching framework build.

The T-SIM7600 device used for this test does not support hardware flow control. Do not enable `setHwFlowCtrlMode()` or treat RTS/CTS as a valid workaround on this board. A lower baud-rate comparison is valid only when both the modem and ESP32 UART are changed to the same rate; changing only `HardwareSerial` does not test a lower modem baud rate. The compile-time FIFO comparison can be selected with `-DISSUE548_RX_FIFO_THRESHOLD=24`, but it does not increase the ESP32's 128-byte hardware FIFO.

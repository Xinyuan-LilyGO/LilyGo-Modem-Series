# SIM7600G SD card recorder and player

This example only supports `T-SIM7600X-S3-Standard`. It records audio through
the SIM7600G and stores it as `D:/rec.wav` on the modem SD card.

Open the serial monitor at 115200 baud and send a command followed by Enter:

| Command | Short command | Action |
| --- | --- | --- |
| `record` | `r` | Check the SD card, then start recording |
| `stop` | `s` | Stop recording |
| `play` | `p` | Play `D:/rec.wav` |
| `help` | `h` | Show the command list |

Before `AT+CREC=1,"D:/rec.wav"` is sent, the example requires both
`AT+FSCD=D:/` and `AT+FSMEM` to succeed. The `FSMEM` response must identify the
`D:` drive. If any check fails, an error is printed and recording does not
start.

Playback uses the onboard audio power amplifier controlled by modem GPIO 77.

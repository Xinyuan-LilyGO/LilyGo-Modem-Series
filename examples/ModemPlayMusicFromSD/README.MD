# SIM7600 modem SD card MP3 player

This example is only for `T-SIM7600X-S3-Standard`. It scans the SD card
connected to the SIM7600G modem, finds MP3 files, and plays them through the
modem audio output. It scans `D:/` and its subdirectories, then loops through
the resulting playlist.

The SIM7600 firmware must include audio decoding support. Connect a speaker to
the board audio output before running the example.

The main AT command sequence is:

```text
AT+FSCD=D:/
AT+FSMEM
AT+FSLS
AT+CCMXPLAY="D:/music.mp3",0,0
```

For `T-SIM7600X-S3-Standard`, the example also enables the onboard audio power
amplifier through modem GPIO 77.

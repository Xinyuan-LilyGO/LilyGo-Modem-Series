# T-SIM7600X-S3-Standard SD audio and voice call example

This example combines single-file modem SD audio playback and WAV recording with voice-call
control and the SIM7600 `AT+CPTONE` tone command. It is intended for
`T-SIM7600X-S3-Standard` with audio decoding firmware, a modem SD card, and a
speaker/microphone connected to the board audio interface.

Commands are entered in the serial monitor at 115200 baud:

```text
call <number>                 Place a call, for example: call +8613812345678
answer                        Answer an incoming call
hangup                        Hang up a call
voice-channel <0|1|3>         Switch voice channel (0=off, 1=handset, 3=speaker phone)
volume <0-5>                  Set loudspeaker volume (default 4)
mic-gain <0-8>                Set microphone gain (default 7)
tone <tone> <ms> [gain]       Play CPTONE (default gain 4000)
record                        Record to D:/rec_<timestamp>.wav
record-stop                   Stop recording
play <path/file>              Play one audio file, for example play D:/music/test.mp3
play-stop                     Stop audio playback
list-files                    List recorded and other audio files on modem SD
at-debug                      Enter AT command passthrough mode
help                          Show the command list
```

In ATDebug mode, enter AT commands directly, for example `AT+CSQ`. Enter
`exit` on a separate line to return to the normal command mode. Audio playback
is never started automatically; use `play <path/file>` to play one file.

After boot, the example only initializes the modem and prints the help menu.
Use `list-files` to scan the modem SD card and list recorded/audio files.
Playback is stopped when an incoming call is detected; type `answer` or
`hangup` to handle the call. Recording and playback commands are rejected
while a call or another audio operation is active.

During initialization the example sends `AT+CODECCTL=1` to enable host control
of the external NAU8810 codec, then opens the speaker-phone path with
`AT+CSDVC=3`. Use `voice-channel 1` for the handset path or `voice-channel 0` to close the
voice channel.

`RING`/`+CRING` is a call notification, not a guaranteed local ringtone. When
one is received, this example plays `AT+CPTONE=1,500,4000` through the
configured audio path. The modem's repeated `RING` notifications repeat the
tone.

The tone implementation follows the data sheet limits:

```text
AT+CPTONE=<tone>,<time>,<gain>
```

Some firmware versions reject the two-parameter form, so the example always
sends the gain parameter. When omitted from the `tone` command, gain `4000` is
used.

The audio controls map to the SIM7600 voice commands:

```text
volume <0-5>                  -> AT+CLVL=<level>
mic-gain <0-8>                -> AT+CMICGAIN=<value>
```

`AT+CLVL` is nonvolatile and uses level 4 as the factory default. This example
sets `AT+CMICGAIN=7` during startup because `AT+CMICGAIN` returns to its modem
default after a reset. The setting takes effect immediately during an active
call, or on the next call when changed while idle.

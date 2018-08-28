# samd21-synth-utils

## Description

This repo contains utilities for developing synthesizer control firmware on the
Microchip SAM21G18AU ARM Cortex-M0+ MCU using the GNU ARM Embedded Toolchain.

## Dependencies

```
sudo apt-get install gcc-arm-none-eabi gdb-arm-none-eabi libnewlib-arm-none-eabi
libstdc++-arm-none-eabi-newlib openocd
```

Note that OpenOCD version >= 0.10.0 is required. Depending on your software
repositories, you may need to compile the latest version from source.

Finally, you'll need to download Microchip's ASF library v3.42, which should be
available here:

http://www.microchip.com/mplab/avr-support/advanced-software-framework

Extract the library locally on your system, and point the "ASF" macro in
Makefile to its location.

## Build Instructions

Connect at Atmel-ICE debugger to the SWD interface on the board, then:

```
make
make flash
```

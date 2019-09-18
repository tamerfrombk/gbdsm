# gbdsm

A minimal GameBoy ROM disassembler.

## Features
* Only depends on `libstdc++`
* Allows range disassembly by specifying start and end addresses for disassembly.

## Usage
```
gbdsm '/path/to/rom.gb' [-h] [-b address] [-e address]

Optional arguments:
-h            show this help message and exit.
-b address    set the starting address for the disassembler. Defaults to 0x0.
-e address    set the end address for the disassembler. Defaults to the end of ROM.
```

## Building

`gbdsm` uses a standard `Makefile` for building and installing. A version of `g++` supporting C++14 is required.

Navigate to the directory where you downloaded the sources and run `make`. This will build the executable named `gbdsm` into that directory. By default, a release version will be built. To build a debug version, use the `make debug` command.

To remove artifacts, use the `make clean` command.


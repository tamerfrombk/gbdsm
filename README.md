# gbdsm

A minimal GameBoy ROM disassembler.

## Features
* Only depends on `libstdc++`
* Allows range disassembly by specifying start and end addresses for disassembly.
* Allows for disassembly using either linear sweep or recursive search algorithms.

## Usage
```
gbdsm '/path/to/rom.gb' [-h] [-b address] [-e address] [--linear | --recursive]

Optional arguments:
-h            show this help message and exit.
-b address    set the starting address for the disassembler in decimal. Defaults to 0x0.
-e address    set the end address for the disassembler in decimal. Defaults to the end of ROM.
--linear      use the linear sweep algorithm for disassembly. This algorithm is the default.
--recursive   use the recursive search algorithm for disassembly.
```

For more information about the different algorithms, consult the `man` page.

## Building

`gbdsm` uses a standard `Makefile` for building and installing. A version of `g++` supporting C++14 is required.

Navigate to the directory where you downloaded the sources and run `make`. This will build the executable named `gbdsm` into that directory. By default, a release version will be built. To build a debug version, use the `make debug` command.

To remove artifacts, use the `make clean` command.

## Installing

To install the executable on your system, type `sudo make install`. This will place the `gbdsm` executable in your `/opt/bin` directory by default and install the `man` page. To customize the installation directory, set the `INSTALL_DIR` variable when running `make`: `sudo make install INSTALL_DIR=/path/to/install`

**NOTE**: In order to access `gbdsm` without using the full path `/opt/bin/gbdsm`, you may need to add `/opt/bin` to your `PATH`.

## Uninstalling

To uninstall, simply run `sudo make uninstall`. This will remove the `gbdsm` executable from `/opt/bin` by default and uninstall the `man` page. If you opted to install the program elsewhere, you will need to supply the installation directory when running `make`: `sudo make uninstall INSTALL_DIR=/path/to/install`

## Examples

Here is an example showing the disassembly for the address range [0, 20) for the GameBoy boot ROM:

```
> ./gbdsm boot.gb -b 0 -e 20

LD SP,$FFFE    $0000
XOR A          $0003
LD HL,$9FFF    $0004
LD (HL-),A     $0007
BIT 7,H        $0008
JR NZ,$0007    $000A
LD HL,$FF26    $000C
LD C,$0011     $000F
LD A,$0080     $0011
LD (HL-),A     $0013
```

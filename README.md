# Summoner

## What is this...

Summon demons and DATE them!!! (kiss, hold hand... wow...) But maybe they'll kill you!?

## Releases

TODO! :3 (sowwy)

## Build Instructions

*These instructions might not be 100%, please contact the authors for help or with any issues you may encounter.*

### Clone


```shell
:: Clone the github repository.
git clone --recursive https://github.com/Ceriole/Summoner-GBC.git
:: Enter the cloned repository
cd Summoner-GBC
```

### Configure

Create the `cfg.mk` file in your favorite text/code editor. Make sure it's in the base repository directory!

Set `*_HOME` variables to tool paths in the [configuration make file](cfg.mk) with a text editor (See [Setting CFG File](#setting-cfg-file)). See [Dependencies](#dependencies) for links to tools and dependencies.

### Build

```shell
:: Remove built files (Optional)
make clean

:: Build rom file.
make all

:: OR ::

:: Clean & build in one command.
make clean all
```

After praying to the Gods and performing multiple blood sacrifies, A file called `SUMMONER.gbc` should now exist in the base directory. Run it in an emulator like [**Emulicious**](https://emulicious.net/) (check out its [**VSCode debugger**](https://marketplace.visualstudio.com/items?itemName=emulicious.emulicious-debugger)), or upload to a flash cartrige and play on real hardware! (wow!!!)

## Dependencies

- [**GBDK-2020 4.1.1**](https://github.com/gbdk-2020/gbdk-2020/releases/tag/4.1.1)
    - Includes modified [**SDCC**](https://sdcc.sourceforge.net/) compiler, and other tools to create Gameboy (Color) ROMs using C and ASM.
    - **SDCC** uses the [**SDAS**]() compiler, which is based upon [**ASXXXX**](https://web.mit.edu/~6.121j/arch/i386_rhel4/versions/sdcc/2.5.0/share/sdcc/doc/aslink/asxhtm.html).
- [**RGBDS 5.1.0**](https://github.com/gbdev/rgbds/releases/v0.5.1)
    - For `rgbasm` to compile [libraies](lib).
- [**Python 3.X**](https://www.python.org/) to run python scripts.
- ***All of your sanity***

## Helpful Links

- [**GBDK-2020 Documentation**](https://gbdk-2020.github.io/gbdk-2020/docs/api/)
- [**Pan Docs**](https://gbdev.io/pandocs/)

## Tools
These are required to compile and edit this repository.
- [**MinGW**](https://sourceforge.net/projects/mingw/) or [**MSYS2**](https://www.msys2.org/) ***(Required)***
    - GNU tools like `cat`, `make`, etc...
- [**VSCode**](https://code.visualstudio.com/) or other text editor. ***(Optional?)***
- [**Aseprite**](https://www.aseprite.org/)
    - To edit and convert `.ase` files into `.png`s and export animation data to `.json`. ***(Optional)***
- An [**Emulator**](https://emulicious.net/) or **Gameboy (Color) Flash Cartrige**
    - *Optional, but then you can't run the built `.gb` or `.gbc` files...?*

## Included Libraries

- [**hUGEDriver**](https://github.com/SuperDisk/hUGEDriver) 
    - Music engine for gameboy (color).
- [**gb-vwf**](https://github.com/ISSOtm/gb-vwf)
    - Variable-width font rendering engine for gameboy (color).

## Setting CFG File

An example `cfg.mk`:

```make
# System and User specific config file
# Set the variables below to the correct paths for make to use.

# GBDK root directory (contains 'bin/lcc.exe' etc...)
GBDK_HOME			:= D:/gbdk
# Aseprite installation directory
ASEPRITE_HOME		:= D:/SteamLibrary/steamapps/common/Aseprite
# RGBDS root directory (contains 'rgbasm.exe' etc...)
RGBDS_HOME			:= D:/RGBDS/5.1
# Python command/executeable path for running scripts ('py', 'python' or 'python3')
PY					:= py

# Uncomment below to echo the generated console commands and debug info.
# Q :=
```
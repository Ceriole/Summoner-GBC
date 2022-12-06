# Summoner

## What is this...

Summon demons and DATE them!!! (kiss, hold hand... wow...)

## Build Instructions

*These instructions might not be 100%, please contact me for help or with any issues you may encounter.*

### Clone
Download the repository by running the command:
```bat
git clone --recursive https://github.com/Ceriole/Summoner-GBC.git
```

Set `*_HOME` variables to tool paths in the [`Makefile`](Makefile) with a text editor. See [below](#requirements) for links to tools and dependencies.

### Build
In the base directory run the commands:

```bat
:: Remove built files (Optional)
make clean

:: Build rom file.
make all
```

After praying to the Gods and performing multiple blood sacrifies, A file called `SUMMONER.gbc` should now exist in the base directory. Run it in an emulator like [Emulicious](https://emulicious.net/) (check out its [VSCode debugger](https://marketplace.visualstudio.com/items?itemName=emulicious.emulicious-debugger)), or upload to a flash cartrige and play on real hardware! (wow!!!)

## Dependencies
- **GBDK-2020 4.1.1 -** https://github.com/gbdk-2020/gbdk-2020/releases/tag/4.1.1
    - Includes modified `SDCC` compiler, and other tools to create Gameboy (Color) ROMs in C.
- **RGBDS 5.1.0 -** https://github.com/gbdev/rgbds/releases/v0.5.1
    - For `rgbasm` to compile [libraies](lib).
    - For `rgbgfx` to generate graphics binary data.
- ***All of your sanity***
## Tools
- [MinGW](https://sourceforge.net/projects/mingw/) or [MSYS2](https://www.msys2.org/) for tools like `make`, `cat`, etc. ***(required)***
- [VSCode](https://code.visualstudio.com/) or some form of code editor.
- [Aseprite](https://www.aseprite.org/) to convert `.ase` files into `.png`s and export animation data.
- An **Emulator** or **Gameboy (Color) Flash Cartrige**! ***(not required, but then you can't run the built .gb or .gbc files...?)***
## Included Libraries
- **hUGEDriver/hUGETracker -** https://github.com/SuperDisk/hUGEDriver
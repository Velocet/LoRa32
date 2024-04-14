# LoRa32

In the wake of more and more people using LoRa the lack of a reliable source for PIN mappings became obvious.
A lot of projects need to maintain their own set of configurations.

## Proposal

A config "database" for LoRa modules with a sane naming scheme so we can all benefit from it: [LoRa32](https://github.com/Velocet/LoRa32)

This incorporates ideas and configs from [RadioLib](https://github.com/jgromes/RadioLib/), @matthias-bs ([BresserWeatherSensorReceiver](https://github.com/matthias-bs/BresserWeatherSensorReceiver)) plus some vendor/architecture specific extensions.

The name stems from the fact that most modules are equipped with an ESP32.

- Naming Scheme for files
  - `LoRa32.h` - Main include file
  - Vendor/Architecture specifics should be kept in separate files like `LoRa32_HelTec.h` or `LoRa32_RP2040.h`
    - `vendor/LoRa32_*.h` - Vendor/Board specific files
    - `arch/Lora32_$Architecture.h` - Architechture specific files
    - `Lora32_$Library.h` - Library specific files that could by used by all (or most) implementations
- `LoRa32.h` should only contain the bare minimum == board configs
  - Needs to be usable without any vendor/architechture specific includes: Easier to include this file into other projects. Just copy&paste instead of loading a lib.
  - Because of this a version number needs to inside including the date
  - `#define`/`#if` guards are used to take care of the different boards, vendors, architechtures, etc.
- `LoRa32_*.h` files are optional but:
  - Included by default
  - Configurable in the main `LoRa32.h` file or from the project itself
    - Project settings always overwrite lib settings
    - `LoRa32.h` settings always overwrite `LoRa32_*.h` settings
- Main targets
  - Platform: ESP32
  - Framework: Arduino
  - Tool: VSCode
    - Arduino
    - PlatformIO

## Features

- TBD: Same & sane PIN naming for different boards across vendors and platforms
- RadioLib setups cause every board has a radio^^
- Workaround for Bugs (eg.: set pinMode to INPUT on GPI only pins used for interrupts)
- Deep Sleep Support
- Persistant Storage support
- Battery measurement
- Basic Display config (nothing i care about..)
- ???

Original Discussion: [PIN „Database“ @ RadioLib](https://github.com/jgromes/RadioLib/discussions/1065)

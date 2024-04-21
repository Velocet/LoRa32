# LoRa32

In the wake of more and more people using LoRa the lack of a reliable source for PIN mappings became obvious.
A lot of projects need to maintain their own set of configurations which leads to inconsistencies and the need to maintain this data.

## Proposal

A config "database" for radio modules with a sane naming scheme so we can all benefit from it: [LoRa32](https://github.com/Velocet/LoRa32)

This incorporates ideas and configs from [RadioLib](https://github.com/jgromes/RadioLib/), @matthias-bs ([BresserWeatherSensorReceiver](https://github.com/matthias-bs/BresserWeatherSensorReceiver)) plus some vendor/architecture specific extensions.

The name stems from the fact that most boards are based on an ESP32 with a LoRa capabale radio module.

- File Naming Scheme
  - `LoRa32.h` - Main include file
  - Vendor/Architecture specifics should be kept in separate files like `LoRa32_HelTec.h` or `LoRa32_RP2040.h`
    - `vendor/LoRa32_*.h` - Vendor/Board specific files
    - `arch/Lora32_$Architecture.h` - Architechture specific files
    - `Lora32_$Library.h` - Library specific files that could by used by all (or most) implementations
- `LoRa32.h` should only contain the bare minimum which are the board configs
  - Needs to be usable without any specific includes: Easier to include into other projects. Just copy&paste and adopt to your own needs instead of using a lib.
  - Because of this a version number (incl. date + git revision) needs to inside every file
  - `#define`/`#if` are used to take care of the flow
- `LoRa32_*.h` files are optional but:
  - Included by default
  - Configurable in the main `LoRa32.h` file or from the project itself
    - Project settings always overwrite lib settings
    - `LoRa32.h` settings always overwrite `LoRa32_*.h` settings
- PIN Naming Scheme (`$prefix_$group_$function`)
  - All uppercase to differentiate from other settings
  - `$prefix`
    - Standard is `LORA32_`
    - Compatability mode removes prefix
    - Can be changed if needed (eg. adopt to own project)
  - `$group`
    - Undefined if a function (`RADIO`, `I2C`, etc.) is not defined/used
    - Example: A board without a radio module has its `$prefix_RADIO` undefined
    - Can hold additional config data
      - Example: `LORA32_RADIO = SX1276` defines RadioLibs RADIO_TYPE (`LORA32_RADIO radio = new Module(...)`).
    - Predefined `$group`s
      - `PINS` (eg. `$prefix_PINS_SPI`): Defines a group of PINs for the same functionality (eg. SPI) with the PIN definitions as array data
      - `PIN` (eg. `$prefix_PIN_MOSI`): Compatability mode only: Additional definition of the PIN name
        - LORA32 definition: `LORA32_SPI_MOSI`
        - Compatability mode: `PIN_MOSI`
      - `SPI`: SPI name (HSPI/VSPI)
      - `DISPLAY`: Display geometry information
      - `RADIO`: RadioLib RADIO_TYPE
      - `TBD`: ... TBD ...
- Targets
  - Tool: VSCode with PlatformIO / Arduino
  - Framework: Arduino
  - Main Platform: ESP32(S2/S3)
    - Other: ESP8266, RPi, TBD

## Features

- Same & Sane PIN naming for boards from different vendors and platforms
- Workaround for Bugs (eg.: set input only PINs to input which could cause radio interrupt errors)
- Deep Sleep Support
- Persistant Storage support
- Battery measurement
- Basic Display config (nothing i care about..)
- Optional Automatic Lib Configs
  - RadioLib module configuration
  - Some standard display lib setups
- TBD

## Ideas / Notes / Status

- [tinyGS ConfigManager](https://github.com/G4lile0/tinyGS/blob/6f9bdcb60baefaf25f9de0d390843b064d1a314d/tinyGS/src/ConfigManager/ConfigManager.cpp#L50)
- Projects with a board pin configs
  - meshtastic
  - ExpressLRS
  - HomeSpan
  - tasmota
  - [BresserWeatherSensorReceiver](https://github.com/matthias-bs/BresserWeatherSensorReceiver)

Original Discussion: [PIN „Database“ @ RadioLib](https://github.com/jgromes/RadioLib/discussions/1065)

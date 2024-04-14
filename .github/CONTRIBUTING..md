# Structure of the `LoRa32` library:

```
|
|--examples  --> Arduino
|  |
|  |--SendLoRaNotNudes
|     | 
|     |- SendLoRaNotNudes.ino
|
|--src
|  |
|  |- LoRa32.h
|  |- LoRa32.cpp
|  |
|  |--arch
|  |  |
|  |  |- LoRa32_aESP32.cpp
|  |  |- LoRa32_aESP32.h
|  |  |
|  |--vendor
|  |  |
|  |  |- LoRa32_vHelTec.cpp
|  |  |- LoRa32_vHelTec.h
|
|- library.json  --> Custom build options, etc.: https://docs.platformio.org/page/librarymanager/config.html
|- platformio.ini
|
```

## Contents of `src/main.cpp`

```CPP
#include <Arduino.h>
#include <LoRa32.h>  // Include the LoRa32 header file

// This line will automatically configure a RadioLib module based on your board
LORA32_RADIO radio = new Module(LORA32_SPI_CS, LORA32_RADIO_IO0, LORA32_RADIO_RST, LORA32_RADIO_IO1);

// function declarations

void setup() {printf("setup");} // put your setup code here, to run once
void  loop() {printf("loop");}  // put your main code here, to run repeatedly

// function definitions
```

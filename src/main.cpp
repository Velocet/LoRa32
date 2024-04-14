/**
 * @file main.cpp "main.cpp"
 * @brief Automatic Board Configuration
 * @author Velocet
 *
 * Automatic board configuration for LoRa32 boards with RadioLib support.
 *
 * PlatformIO (main.cpp) example.
 *
 * MIT License
 * Copyright (c) Velocet
 */

#include <Arduino.h>
#include <SPI.h>
#include <LoRa32.h>

// Load RadioLib module
LORA32_RADIO radio = new Module(LORA32_SPI_CS, LORA32_RADIO_IO0, LORA32_RADIO_RST, LORA32_RADIO_IO1);

// function declarations
// ...

void setup() {printf("setup");} // setup code to run once
void loop()  {printf("loop");}  // main code to run repeatedly

// function definitions
// ...

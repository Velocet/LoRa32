/**
 * @file LoRa32_config.h "LoRa32_config.h"
 * @brief LoRa32 Custom Board Configuration
 * @author Velocet
 *
 * Custom board config for the LoRa32 lib.
 *
 * MIT License
 * Copyright (c) Velocet
 */

#ifndef LoRa32_config_h
#define LoRa32_config_h

#if LORA32_CUSTOM > 0
  #warning "[LORA32] Using Custom Board Config!"

  #if LORA32_RADIOLIB > 0
    #define LORA32_RADIO      RADIO_TYPE // RadioLib supported module type
  #endif

  #define LORA32_PINS_RADIO   PINS(RST, BUSY/IO0, IO1, IO2) // If no IO1/IO2: Use IO0 instead
  #define LORA32_PINS_SPI     PINS(SS, MOSI, MISO, SCK)     // Define SPI PINS if using non-Arduino SPI setup
  #define LORA32_PINS_DISPLAY PINS(RST, SCL, SDA)           // Define the Display and use like that:
  #define DISPLAY_GEOMETRY    "GEOMETRY_128_64"   // `SSD1306 display(0x3c, LORA32_DISPLAY_SDA, LORA32_DISPLAY_SCL, LORA32_DISPLAY_RST, DISPLAY_GEOMETRY);`
#endif

#endif // LoRa32_config_h
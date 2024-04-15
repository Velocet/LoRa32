/**
 * @file LoRa32.h "LoRa32.h"
 * @brief Automatic Board Configuration
 * @author Velocet
 *
 * Automatic board configuration for LoRa32 boards with RadioLib support.
 *
 * In PlatformIO (main.cpp) or Arduino Sketch `#include LoRa32.h` and load:
 * LORA32_RADIO radio = new Module(LORA32_SPI_CS, LORA32_RADIO_IO0, LORA32_RADIO_RST, LORA32_RADIO_IO1);
 *
 * See the README.md for more information and on how to add your own board configuration.
 *
 * TODO README.me ;)
 * TODO Add class to init own board config from Sketch
 * TODO Better exclusion of drivers when loading RadioLib
 *
 * MIT License
 * Copyright (c) Velocet
 */

#ifndef LoRa32_h
#define LoRa32_h

#include <Arduino.h>
#include <SPI.h>

#pragma region OPTIONS
#if !defined(LORA32_RADIOLIB)
  #define LORA32_RADIOLIB (1) // Use RadioLib?
#endif
#if !defined(LORA32_CUSTOM)
  #define LORA32_CUSTOM   (0) // Use custom config?
#endif
#pragma endregion OPTIONS

#define PINS(...) __VA_OPT__(__VA_ARGS__)

#if LORA32_CUSTOM > 0
  #include LoRa32_config.h
#endif

// TODO For SX127x/SX126x: Read SPI to get version: https://forum.lora-developers.semtech.com/t/sx126x-device-id/1508
// SX1261/SX1262 REG[0x0320-0x032F] `0000320 53 58 31 32 36 31 20 56 32 44 20 32 44 30 32 00 | SX1261 V2D 2D02.`
// OCP overcurrent protection register:
// - SX1261: 0x18
// - SX1262: 0x38
// SX1268        REG[0x0320-0x032F] `0000320 53 58 31 32 36 31 20 56 32 44 20 32 44 30 32 00 | SX1268 V2D 2D02.`

// TODO
// #define BUTTON    GPIO_NUM_0 // 'PRG' Button
// // LED pin & PWM parameters
// #define LED_PIN   GPIO_NUM_35
// #define LED_FREQ  5000
// #define LED_CHAN  0
// #define LED_RES   8
// // Battery voltage measurement
// #define VBAT_CTRL GPIO_NUM_37
// #define VBAT_ADC  GPIO_NUM_1
// #define VEXT      GPIO_NUM_36 // External power control

#pragma region RADIOLIB /* RadioLib Build Configuration Options. */
#if LORA32_RADIOLIB > 0
  #define RADIOLIB_DEBUG_BASIC      (0) // Basic Debugging (e.g. reporting GPIO timeouts or module not being found).
  #define RADIOLIB_DEBUG_PROTOCOL   (0) // Protocol Information (e.g. internal information).
  #define RADIOLIB_DEBUG_SPI        (0) // Verbose SPI Communication - produces large debug logs!

  #define RADIOLIB_GODMODE          (1) // Methods and member variables in all classes will be made public.
  #define RADIOLIB_LOW_LEVEL        (1) // Low-level Hardware Access enable.
  #define RADIOLIB_SPI_PARANOID     (0) // Verify SPI writes by a read to improve reliability. Slows down communication.
  #define RADIOLIB_CHECK_PARAMS     (1) // Parameter Range Checking.
  #define RADIOLIB_INTERRUPT_TIMING (0) // Interrupt-based timing: https://github.com/jgromes/RadioLib/wiki/Interrupt-Based-Timing

  // Exclude RadioLib drivers to speed up build process.
  #define RADIOLIB_EXCLUDE_CC1101   (1)
  #define RADIOLIB_EXCLUDE_NRF24    (1)
  #define RADIOLIB_EXCLUDE_RF69     (1)
  #define RADIOLIB_EXCLUDE_RFM2X    (1) // dependent on RADIOLIB_EXCLUDE_SI443X
  #define RADIOLIB_EXCLUDE_SI443X   (1)
  #define RADIOLIB_EXCLUDE_STM32WLX (1) // dependent on RADIOLIB_EXCLUDE_SX126X
  #define RADIOLIB_EXCLUDE_SX1231   (1) // dependent on RADIOLIB_EXCLUDE_RF69
  #define RADIOLIB_EXCLUDE_SX128X   (1) // 2.4Ghz only

  // Exclude RadioLib protocols to speed up build process.
  #define RADIOLIB_EXCLUDE_AFSK          (1)
  #define RADIOLIB_EXCLUDE_APRS          (1)
  #define RADIOLIB_EXCLUDE_AX25          (1)
  #define RADIOLIB_EXCLUDE_BELL          (1)
  #define RADIOLIB_EXCLUDE_FSK4          (1)
  #define RADIOLIB_EXCLUDE_HELLSCHREIBER (1)
  #define RADIOLIB_EXCLUDE_LORAWAN       (1)
  #define RADIOLIB_EXCLUDE_MORSE         (1)
  #define RADIOLIB_EXCLUDE_PAGER         (1)
  #define RADIOLIB_EXCLUDE_RTTY          (1)
  #define RADIOLIB_EXCLUDE_SSTV          (1)

  #include <RadioLib.h>
#endif
#pragma endregion RADIOLIB

#pragma region BOARDS
#if LORA32_CUSTOM == 0
#if defined(ARDUINO_TTGO_LORA32_V1)
  #define LORA32_RADIO          SX1276
  #define LORA32_PINS_SPI       PINS(18, 27, 19,  5) // SS, SI, SO, SC
  #define LORA32_PINS_RADIO     PINS(14, 26, 26, 26) // RESET, BUSY/IO0,...IOn
#elif defined(ARDUINO_TTGO_LORA32_V2)
  #define LORA32_RADIO          SX1276
  #define LORA32_PINS_SPI       PINS(18, 27, 19,  5) // SS, SI, SO, SC
  #define LORA32_PINS_RADIO     PINS(12, 26, 26, 26) // RESET, BUSY/IO0,...IOn
#elif defined(ARDUINO_TBEAM)
  #define LORA32_RADIO          SX1276
  #define LORA32_PINS_SPI       PINS(18, 27, 19,  5) // SS, SI, SO, SC
  #define LORA32_PINS_RADIO     PINS(23, 26, 33, 32) // RESET, BUSY/IO0,...IOn
#elif defined(ARDUINO_TTGO_LORA32_V21NEW)
  #define LORA32_RADIO          SX1276
  #define LORA32_PINS_SPI       PINS(18, 27, 19,  5) // SS, SI, SO, SC
  #define LORA32_PINS_RADIO     PINS(23, 26, 33, 32) // RESET, BUSY/IO0,...IOn
#elif defined(ARDUINO_HELTEC_WIRELESS_STICK)
  #define LORA32_RADIO          SX1276
  #define LORA32_PINS_RADIO     PINS(14, 26, 35, 34) // RESET, BUSY/IO0,...IOn
  #define LORA32_PINS_SPI       PINS(18, 27, 19,  5) // SS, SI, SO, SC
  #define LORA32_PINS_DISPLAY   PINS(16, 15, 4)      // RST, SCL, SDA
  #define LORA32_PINS_INPUT     PINS(34, 35)
  #define DISPLAY_GEOMETRY      "GEOMETRY_64_32"
#elif defined(ARDUINO_HELTEC_WIRELESS_STICK_V1)
  #define LORA32_RADIO          SX1276
  #define LORA32_PINS_RADIO     PINS(14, 26, 33, 32) // RESET, BUSY/IO0,...IOn
  #define LORA32_PINS_SPI       PINS(18, 27, 19,  5) // SS, SI, SO, SC
  #define LORA32_PINS_DISPLAY   PINS(16, 15, 4)      // RST, SCL, SDA
  #define LORA32_PINS_INPUT     PINS(33, 32)
  #define DISPLAY_GEOMETRY      "GEOMETRY_64_32"
#elif defined(ARDUINO_HELTEC_WIRELESS_STICK_V3)
  #define LORA32_RADIO          SX1262
  #define LORA32_PINS_RADIO     PINS(12, 13, 14, 14) // RESET, BUSY/IO0,...IOn
  #define LORA32_PINS_SPI       PINS( 8, 10, 11,  9) // SS, SI, SO, SC
  #define LORA32_PINS_DISPLAY   PINS(21, 18, 17)     // RST, SCL, SDA
  #define DISPLAY_GEOMETRY      "GEOMETRY_64_32"
#elif defined(ARDUINO_HELTEC_WIRELESS_STICK_LITE) || defined(ARDUINO_HELTEC_WIRELESS_BRIDGE)
  #define LORA32_RADIO          SX1276
  #define LORA32_PINS_RADIO     PINS(14, 26, 35, 34) // RESET, BUSY/IO0,...IOn
  #define LORA32_PINS_SPI       PINS(18, 27, 19,  5) // SS, SI, SO, SC
  #define LORA32_PINS_INPUT     PINS(35, 34)
#elif defined(ARDUINO_HELTEC_WIRELESS_STICK_LITE_V3)
  #define LORA32_RADIO          SX1262
  #define LORA32_PINS_RADIO     PINS(12, 13, 14, 14) // RESET, BUSY/IO0,...IOn
  #define LORA32_PINS_SPI       PINS(34, 35, 37, 36) // SS, SI, SO, SC
#elif defined(ARDUINO_HELTEC_WIFI_LORA_32)
  #define LORA32_RADIO          SX1276
  #define LORA32_PINS_RADIO     PINS(14, 26, 33, 32) // RESET, BUSY/IO0,...IOn
  #define LORA32_PINS_SPI       PINS(18, 27, 19,  5) // SS, SI, SO, SC
  #define LORA32_PINS_DISPLAY   PINS(16, 15, 4)      // RST, SCL, SDA
  #define LORA32_PINS_INPUT     PINS(33, 32)
  #define DISPLAY_GEOMETRY      "GEOMETRY_128_64"
#elif defined(ARDUINO_HELTEC_WIFI_LORA_32_V2)
  #define LORA32_RADIO          SX1276
  #define LORA32_PINS_RADIO     PINS(14, 26, 35, 34) // RESET, BUSY/IO0,...IOn
  #define LORA32_PINS_SPI       PINS(18, 27, 19,  5) // SS, SI, SO, SC
  #define LORA32_PINS_DISPLAY   PINS(16, 15, 4)      // RST, SCL, SDA
  #define LORA32_PINS_INPUT     PINS(35, 34)
  #define DISPLAY_GEOMETRY      "GEOMETRY_128_64"
#elif defined(ARDUINO_HELTEC_WIFI_LORA_32_V3)
  #define LORA32_RADIO          SX1262
  #define LORA32_PINS_RADIO     PINS(12, 13, 14, 14) // RESET, BUSY/IO0,...IOn
  #define LORA32_PINS_SPI       PINS( 8, 10, 11,  9) // SS, SI, SO, SC
  #define LORA32_PINS_DISPLAY   PINS(16, 15, 4)      // RST, SCL, SDA
  #define DISPLAY_GEOMETRY      "GEOMETRY_128_64"
#endif
#endif
#pragma endregion BOARDS

#pragma region PINS
#if defined(LORA32_PINS_SPI)
  const uint8_t LORA32_SPI_PINS[] = {LORA32_PINS_SPI};
  const uint8_t LORA32_SPI_CS     = LORA32_SPI_PINS[0];
  const uint8_t LORA32_SPI_MOSI   = LORA32_SPI_PINS[1];
  const uint8_t LORA32_SPI_MISO   = LORA32_SPI_PINS[2];
  const uint8_t LORA32_SPI_SCK    = LORA32_SPI_PINS[3];
#endif

#if defined(LORA32_PINS_RADIO)
  const uint8_t LORA32_RADIO_PINS[] = {LORA32_PINS_RADIO};
  const uint8_t LORA32_RADIO_RST    = LORA32_RADIO_PINS[0];
  const uint8_t LORA32_RADIO_IO0    = LORA32_RADIO_PINS[1];
  const uint8_t LORA32_RADIO_IO1    = LORA32_RADIO_PINS[2];
  const uint8_t LORA32_RADIO_IO2    = LORA32_RADIO_PINS[3];
#endif

#if defined(LORA32_PINS_DISPLAY)
  const uint8_t LORA32_DISPLAY_PINS[] = {LORA32_PINS_DISPLAY};
  const uint8_t LORA32_DISPLAY_RST    = LORA32_DISPLAY_PINS[0];
  const uint8_t LORA32_DISPLAY_SCL    = LORA32_DISPLAY_PINS[1];
  const uint8_t LORA32_DISPLAY_SDA    = LORA32_DISPLAY_PINS[2];
#endif
#pragma endregion PINS

// #pragma region INCLUDES
// #include "LoRa32_config.h"
// #include "LoRa32_display.h"
// #include "LoRa32_misc.h"
// #include "LoRa32_RadioLib.h"
// #include "arch/LoRa32_ESP32.h"
// #include "arch/LoRa32_RP2040.h"
// #include "arch/LoRa32_RP2040_Log.h"
// #include "vendor/LoRa32_HelTec.h"
// #pragma endregion INCLUDES


// TODO different output for different chips + more info on used settings
// #define STR_HELPER(x) #x
// #define STR(x) STR_HELPER(x)
// #pragma message(RECEIVER_CHIP "PINs: RST->" STR(LORA32_RADIO_RST) ", CS->" STR(LORA32_SPI_CS) ", IO0->" STR(LORA32_RADIO_IO0) ", IO1->" STR(LORA32_RADIO_IO1) )


#endif // LoRa32_h

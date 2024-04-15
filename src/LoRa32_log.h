/**
 * @file LoRa32_log.h "LoRa32_log.h"
 * @brief LoRa32 Log Functions
 * @author Matthias Prinke
 *
 * Replacement for https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-log.h
 * - RP2040: DEBUG_RP2040_PORT is set in Arduino IDE: Tools->Debug port: "<Disabled>|<Serial>|<Serial1>|<Serial2>"
 * - ESP8266: DEBUG_ESP_PORT is set in Arduino IDE: Tools->Debug port: "<None>|<Serial>|<Serial1>"
 * - ESP32: CORE_DEBUG_LEVEL is set in Adruino IDE: Tools->Core Debug Level: "<None>|<Error>|<Warning>|<Info>|<Debug>|<Verbose>"
 * - CORE_DEBUG_LEVEL has to be set manually below
 * - Arduino AVR:
 *
 * MIT License
 * Copyright (c) Matthias Prinke
 *
 */

#ifndef LoRa32_log.h
#define LoRa32_log.h

#if defined(ESP8266) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_AVR)
    #define ARDUHAL_LOG_LEVEL_NONE      0
    #define ARDUHAL_LOG_LEVEL_ERROR     1
    #define ARDUHAL_LOG_LEVEL_WARN      2
    #define ARDUHAL_LOG_LEVEL_INFO      3
    #define ARDUHAL_LOG_LEVEL_DEBUG     4
    #define ARDUHAL_LOG_LEVEL_VERBOSE   5

    #if defined(ARDUINO_ARCH_RP2040) && defined(DEBUG_RP2040_PORT)
        #define DEBUG_PORT DEBUG_RP2040_PORT
    #elif defined(DEBUG_ESP_PORT)
        #define DEBUG_PORT DEBUG_ESP_PORT
    #endif

    // Set desired level here!
    #undef CORE_DEBUG_LEVEL
    #define CORE_DEBUG_LEVEL ARDUHAL_LOG_LEVEL_INFO

    // '#undef' to change a previous definition
    #undef log_e
    #undef log_w
    #undef log_i
    #undef log_d
    #undef log_v

    #if defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_NONE
      #define log_e(...) { DEBUG_PORT.printf("%s(), l.%d: ",__func__, __LINE__); DEBUG_PORT.printf(__VA_ARGS__); DEBUG_PORT.println(); }
    #elif (defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_NONE) && defined(ARDUINO_ARCH_AVR)
      #define log_e(...) { printf(__VA_ARGS__); println(); }
    #else
      #define log_e(...) {}
    #endif
    #if defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_ERROR
      #define log_w(...) { DEBUG_PORT.printf("%s(), l.%d: ", __func__, __LINE__); DEBUG_PORT.printf(__VA_ARGS__); DEBUG_PORT.println(); }
    #elif (defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_ERROR) && defined(ARDUINO_ARCH_AVR)
      #define log_w(...) { printf(__VA_ARGS__); println(); }
    #else
      #define log_w(...) {}
    #endif
    #if defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_WARN
      #define log_i(...) { DEBUG_PORT.printf("%s(), l.%d: ", __func__, __LINE__); DEBUG_PORT.printf(__VA_ARGS__); DEBUG_PORT.println(); }
    #elif (defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_WARN) && defined(ARDUINO_ARCH_AVR)
      #define log_i(...) { printf(__VA_ARGS__); println(); }
    #else
        #define log_i(...) {}
    #endif
    #if defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_INFO
      #define log_d(...) { DEBUG_PORT.printf("%s(), l.%d: ", __func__, __LINE__); DEBUG_PORT.printf(__VA_ARGS__); DEBUG_PORT.println(); }
    #elif (defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_INFO) && defined(ARDUINO_ARCH_AVR)
      #define log_d(...) { printf(__VA_ARGS__); println(); }
    #else
      #define log_d(...) {}
    #endif
    #if defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_DEBUG
      #define log_v(...) { DEBUG_PORT.printf("%s(), l.%d: ", __func__, __LINE__); DEBUG_PORT.printf(__VA_ARGS__); DEBUG_PORT.println(); }
    #elif (defined(DEBUG_PORT) && CORE_DEBUG_LEVEL > ARDUHAL_LOG_LEVEL_DEBUG) && defined(ARDUINO_ARCH_AVR)
      #define log_v(...) { printf(__VA_ARGS__); println(); }
    #else
      #define log_v(...) {}
    #endif
#endif

#endif // LoRa32_log_h

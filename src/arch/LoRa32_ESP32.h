/**
 * @file LoRa32_ESP32.h "arch/LoRa32_ESP32.h"
 * @brief ESP32 configs
 * @author Velocet
 *
 * ESP32 specific configurations for the LoRa32 lib.
 *
 * MIT License
 * Copyright (c) Velocet
 */

#ifndef LoRa32_ESP32_h
#define LoRa32_ESP32_h

#pragma region DEEP_SLEEP
/**
 * @brief Puts the device into deep sleep mode.
 *
 * This function prepares the device for deep sleep mode by disconnecting from WiFi, turning off the display, disabling external power, and turning off the LED.
 * It can also be configured to wake up after a certain number of seconds using the optional parameter.
 *
 * @param seconds The number of seconds to sleep before waking up (default = 0).
 */
void lora32_esp32_deep_sleep(int seconds = 0) {
  #ifdef WiFi_h
    WiFi.disconnect(true);
  #endif
  #ifdef LORA32_PINS_DISPLAY
    display.displayOff();
  #endif
  #ifndef LORA32_RADIO
    // in case the radio is not interacted with at all before sleep, it will not respond to just .sleep() and then consumes 800 µA more than it should in deep sleep.
    radio.begin();
    // 'false' here is to not have a warm start, we re-init the after sleep.
    radio.sleep(false);
  #endif

  lora32_ve(false); // Turn off external power
  lora32_led(0); // Turn off LED

  // TODO Set all pins to input to save power
  pinMode(VBAT_CTRL, INPUT);
  pinMode(VBAT_ADC, INPUT);
  pinMode(DIO1, INPUT);
  pinMode(RST_LoRa, INPUT);
  pinMode(BUSY_LoRa, INPUT);
  pinMode(SS, INPUT);
  pinMode(MISO, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SDA_OLED, INPUT);
  pinMode(SCL_OLED, INPUT);
  pinMode(RST_OLED, INPUT);

  #ifdef LORA32_POWER_BUTTON // Set button wakeup if applicable
    esp_sleep_enable_ext0_wakeup(BUTTON, LOW);
    button.waitForRelease();
  #endif

  if (seconds > 0) {esp_sleep_enable_timer_wakeup(seconds * 1000000);} // Set timer wakeup if applicable
  esp_deep_sleep_start(); // and off to bed we go
}

/**
 * @brief Checks if the device woke up from deep sleep due to button press.
 *
 * @return True if the wake-up cause is a button press, false otherwise.
 */
bool lora32_esp32_wakeup_was_button() {return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0;}

/**
 * @brief Checks if the device woke up from deep sleep due to a timer.
 *
 * This function checks if the device woke up from deep sleep due to a timer.
 *
 * @return True if the wake-up cause is a timer interrupt, false otherwise.
 */
bool lora32_esp32_wakeup_was_timer() {return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER;}
#pragma endregion DEEP_SLEEP

/**
 * @brief Measures ESP32 Chip Temperature
 *
 * @return Float with temperature in degrees celsius.
*/
float lora32_esp32_temperature(){
  // #include "driver/temp_sensor.h"
  // We start with the coldest range, because those temps get spoiled the quickest by heat of processor waking up.
  temp_sensor_dac_offset_t offsets[5] = {
    TSENS_DAC_L4,   // (-40°C ~  20°C, err <3°C)
    TSENS_DAC_L3,   // (-30°C ~  50°C, err <2°C)
    TSENS_DAC_L2,   // (-10°C ~  80°C, err <1°C)
    TSENS_DAC_L1,   // ( 20°C ~ 100°C, err <2°C)
    TSENS_DAC_L0    // ( 50°C ~ 125°C, err <3°C)
  };

  int cutoffs[5] = { -30, -10, 80, 100, 2500 }; // If temp below value, use measurement.

  float result = 0;
  for (int n = 0; n < 5; n++) {
    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor.dac_offset = offsets[n];
    temp_sensor_set_config(temp_sensor);
    temp_sensor_start();
    temp_sensor_read_celsius(&result);
    temp_sensor_stop();
    // Serial.printf("L%d: %f°C\n", 4 - n, result);
    if (result < cutoffs[n]) break;
  }
  return result;
}

#endif // LoRa32_ESP32_h

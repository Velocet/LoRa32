/**
 * @file LoRa32_HelTec.h "vendor/LoRa32_HelTec.h"
 * @brief HelTec Board Configs
 * @author Velocet
 *
 * HelTec specific board configurations.
 *
 * See: https://github.com/ropg/heltec_esp32_lora_v3/
 *
 * MIT License
 * Copyright (c) Velocet
 */

#ifndef LoRa32_HelTec_h
#define LoRa32_HelTec_h

/**
 * @brief Controls the VEXT pin to enable or disable external power.
 *
 * Sets VEXT as output and its state based on the given parameter:
 * - True: VEXT is set to LOW to enable external power.
 * - False: VEXT is set to INPUT to disable external power.
 *
 * @param state VEXT pin state: True = Enable, False = Disable.
 */
void lora32_heltec_vext(bool state) {
  if (state) {pinMode(VEXT, OUTPUT);digitalWrite(VEXT, LOW);}
  else {pinMode(VEXT, INPUT);} /* pulled up, no need to drive it */
}

/**
 * @brief Initializes the Heltec library.
 *
 * Display connected to Vext ("external" power)
 */

lora32_heltec_vext(true);delay(5);

#endif // LoRa32_HelTec_h

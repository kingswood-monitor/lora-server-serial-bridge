#include <Arduino.h>
#include <RH_RF95.h>

bool init_radio();
uint8_t get_radio_packet(uint8_t *buffer, uint8_t len);
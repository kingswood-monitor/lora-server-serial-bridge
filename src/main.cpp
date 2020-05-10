/*
    Kingswood Monitoring System
    LoRa server / WiFi Bridge

    Hardware: TTGO ESP32 / SX1276 LoRa
    OS:       Arduino
*/

#include <Arduino.h>

#include "util.h"
#include "radio.h"
#include "socket.h"

void setup()
{
  if (!init_device())
    Serial.println("ERROR: Failed to start device");

  if (!init_radio())
    Serial.println("ERROR: Failed to start radio");

  if (!init_socket())
  {
    Serial.println("ERROR: Failed to connect socket. Freezing...");
    while (1)
      ;
  }
}

// Dont put this on the stack:
uint8_t buffer[RH_RF95_MAX_MESSAGE_LEN];

void loop()
{
  uint8_t bytes_received = get_radio_packet(buffer, sizeof(buffer));
  if (bytes_received > 0)
    transmit_measurement(buffer, bytes_received);
}
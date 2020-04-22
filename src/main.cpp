/*
    Kingswood Monitoring System
    LoRa server

    Hardware: Adafruit feather32u4 RFM95 / Airlift
    OS:       Arduino
*/

#include <stdio.h>
#include <string.h>

#include "util.h"

// **************************************

#include <RHReliableDatagram.h>
#include <RH_RF95.h>

#define SERVER_ADDRESS 0
#define CLIENT_ADDRESS 1

RH_RF95 driver(RFM95_CS, RFM95_INT);
RHReliableDatagram manager(driver, SERVER_ADDRESS);

// ******************************************

void setup()
{
  if (init_device())
    Serial.println("Device started [OK]");

  pinMode(RFM95_RST, OUTPUT);

  // initialise radio
  digitalWrite(RFM95_RST, HIGH);
  Serial.print("Radio...");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  manager.init();
  Serial.println("initialised");
}

uint8_t data[] = "OK";
// Dont put this on the stack:
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];

void loop()
{
  if (manager.available())
  {
    // Wait for a message addressed to us from the client
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, &from))
    {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print(F("[<-0x"));
      Serial.print(from, HEX);
      Serial.print(F("] "));
      Serial.print(len);
      Serial.print(F(" bytes "));

      // Send packet to co-processor
      {
        // \0\0\0\0${LEN}${PACKET}
        for (int i = 0; i < 4; i++)
          Serial1.write('\0');
        Serial1.write(len);
        Serial1.write(buf, len);

        digitalWrite(LED_BUILTIN, LOW);
      }

      // Send a reply back to the originator client
      if (!manager.sendtoWait(data, sizeof(data), from))
        Serial.println(F("sendtoWait failed"));
      else
        Serial.println(F("-> OK"));
    }
    else
    {
      {
        Serial.println("[FAIL]");
      }
    }
  }
}

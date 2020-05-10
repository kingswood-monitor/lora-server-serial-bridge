#include <RHReliableDatagram.h>
#include "radio.h"

#include "DigitalOut.h"

// Radio pins for TTGO ESP32
#define TTGO_CS 18
#define TTGO_IRQ 26

// Reliable Datagram Manager netowrk address
#define SERVER_ADDRESS 0

RH_RF95 driver(TTGO_CS, TTGO_IRQ);
RHReliableDatagram manager(driver, SERVER_ADDRESS);

using namespace Kingswood::Pin;
DigitalOut packet_led(LED_BUILTIN);

bool init_radio()
{
    packet_led.begin();
    packet_led.activeLow(); // signal is an "low" blink
    packet_led.turnOn();

    return manager.init();
}

uint8_t data[] = "OK";
uint8_t get_radio_packet(uint8_t *buf, uint8_t len)
{
    if (manager.available())
    {
        // Wait for a message addressed to us from the client
        uint8_t from;
        if (manager.recvfromAck(buf, &len, &from))
        {
            Serial.println("Packet received");
            // digitalWrite(LED_BUILTIN, HIGH);
            Serial.print(F("[<-0x"));
            Serial.print(from, HEX);
            Serial.print(F("] "));
            Serial.print(len);
            Serial.print(F(" bytes "));

            // digitalWrite(LED_BUILTIN, LOW);

            // Send a reply back to the originator client
            if (!manager.sendtoWait(data, sizeof(data), from))
                Serial.println(F("sendtoWait failed"));
            else
            {
                Serial.println(F("-> OK"));
                packet_led.blink();
            }

            return len;
        }
        else
        {
            {
                Serial.println("[FAIL]");
                return 0;
            }
        }
    }
    else
        return 0;
}
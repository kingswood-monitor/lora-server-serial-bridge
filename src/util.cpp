#include <Arduino.h>
#include "util.h"

// Singleton instance of the radio driver

bool init_device()
{
    Serial.begin(115200);
    Serial1.begin(9600);
    delay(5000);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println("** LoRa Server");
}

void init_radio()
{
    digitalWrite(RFM95_RST, HIGH);
    Serial.print("Radio...");

    // manual reset
    digitalWrite(RFM95_RST, LOW);
    delay(10);
    digitalWrite(RFM95_RST, HIGH);
    delay(10);
}

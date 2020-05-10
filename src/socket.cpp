#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

#include "DigitalOut.h"

#include "secrets.h"
#include "config.h"

// Sockets server host
#define SERVER_HOST "192.168.1.30"
#define SERVER_PORT 1880

using namespace Kingswood::Pin;
DigitalOut wifi_led(LED_BUILTIN);

using namespace websockets;
WebsocketsClient client;

void onMessageCallback(WebsocketsMessage message)
{
    Serial.print("Got Message: ");
    Serial.println(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data)
{
    if (event == WebsocketsEvent::ConnectionOpened)
    {
        Serial.println("");
        Serial.println("INFO: Connnection Opened");
    }

    else if (event == WebsocketsEvent::ConnectionClosed)
    {
        Serial.println("INFO: Connnection Closed");
        client.connect(SERVER_HOST, SERVER_PORT, "/");
    }

    else if (event == WebsocketsEvent::GotPing)
    {
        Serial.println("INFO: Got a Ping!");
    }

    else if (event == WebsocketsEvent::GotPong)
    {
        Serial.println("INFO: Got a Pong!");
    }
}

bool init_socket()
{
    wifi_led.begin();
    wifi_led.turnOff();

    // Connect to wifi or hang
    Serial.print("INFO: Connecting to WiFi");
    WiFi.begin(SSID_NAME, SSID_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        wifi_led.blink(10, 100); // blocks 10x100ms = 1 second
    }
    wifi_led.turnOn();
    Serial.print("Connected, IP: ");
    Serial.println(WiFi.localIP());

    // run callback when messages are received
    client.onMessage(onMessageCallback);

    // run callback when events are occuring
    client.onEvent(onEventsCallback);

    // Connect to server
    Serial.print("INFO: Connecting to websocket");
    while (!client.available())
    {
        client.connect(SERVER_HOST, SERVER_PORT, "/");
        Serial.print(".");
        delay(1000);
    }
    Serial.println();

    // Send a message
    client.send("Hello Server");

    // Send a ping
    client.ping();

    return client.available();
}

void transmit_measurement(const uint8_t *data, const size_t len)
{
    while (!client.available())
    {
        client.connect(SERVER_HOST, SERVER_PORT, "/");
        delay(1000);
    }
    client.sendBinary((char *)data, len);
}

void loop_socket()
{
    client.poll();
}
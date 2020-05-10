#include <Arduino.h>

#include "config.h"
#include "util.h"

void display_logo(const char *title, const char *version);

bool init_device()
{
    Serial.begin(115200);
    delay(5000);

    display_logo(FIRMWARE_NAME, FIRMWARE_VERSION);

    return true;
}

void display_logo(const char *title, const char *version)
{
    char strap_line[200];
    sprintf(strap_line, "                  |___/  %s v%s", title, version);

    Serial.println("  _  __ _                                                _ ");
    Serial.println(" | |/ /(_) _ __    __ _  ___ __      __ ___    ___    __| |");
    Serial.println(" | ' / | || '_ \\  / _` |/ __|\\ \\ /\\ / // _ \\  / _ \\  / _` |");
    Serial.println(" | . \\ | || | | || (_| |\\__ \\ \\ V  V /| (_) || (_) || (_| |");
    Serial.println(" |_|\\_\\|_||_| |_| \\__, ||___/  \\_/\\_/  \\___/  \\___/  \\__,_|");
    Serial.println(strap_line);
    Serial.println();
}
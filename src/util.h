#pragma once

#define NAME "LoRa server"
#define FIRMWARE "kwms_server_lora"
#define VERSION "0.2.0"
#define SERVER_ADDRESS 1
#define DEVICE_TYPE "lora_server"

// feather32u4 LoRa pin assignments
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

#define LED_RED 26

bool init_device();
void init_radio();
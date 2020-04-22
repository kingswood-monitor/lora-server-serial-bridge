# LoRa Server Serial Bridge

Takes LoRaWAN packets from multiple clients and bridges
them over serial.

### Packet Format

Any packets received over LoRaWAN are prefixed with a frame header
consisting of 4 null-bytes and a single byte for the length of the 
packet.

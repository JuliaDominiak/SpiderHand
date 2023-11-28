#include <WiFi.h>
#include <WiFiUdp.h>

#pragma once

class Conn
{
private:
    static WiFiUDP Client;
    static const char* host;
    static uint16_t port;
public:
    Conn(){};
    static void begin(const char* host, uint16_t port);
    static WiFiUDP getClient() { return Client; }
    static void beginPacket();
    static void write(const char* buff, size_t size);
    static void endPacket();
};


#include <WiFi.h>
#include "AsyncUDP.h"
#include "hand.h"

#pragma once

class Conn
{
private:
    static AsyncUDP udp;
    static const char* host;
    static uint16_t port;
    static Hand* hand; 
public:
    Conn(){};
    static void begin(const char* host, uint16_t port, Hand* hand);
    static AsyncUDP getServer() { return udp; }
    static void udpCallback(AsyncUDPPacket& packet);
};


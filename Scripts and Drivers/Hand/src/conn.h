#include <WiFi.h>
#include "AsyncUDP.h"
#include "hand.h"

#pragma once

class Conn
{
private:
    static AsyncUDP udp;
    static uint16_t port;
    static Hand* hand; 
public:
    Conn(){};
    static void begin(uint16_t port, Hand* hand);
    static void udpCallback(AsyncUDPPacket& packet);
};


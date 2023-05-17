#include "conn.h"


AsyncUDP Conn::udp;
uint16_t Conn::port;
Hand* Conn::hand;

void Conn::begin(uint16_t port, Hand* hand)
{
    Conn::hand = hand;
    Conn::port = port;
    WiFi.mode(WIFI_AP);
    WiFi.softAP("hand", "244466666");
    udp.listen(port);
    udp.onPacket(udpCallback);
}

void Conn::udpCallback(AsyncUDPPacket& packet){
    char* buf = (char*)packet.data();
    size_t size = packet.length();
    if (size != 17){
        Serial.printf("Malformed packet (wrong size: %d) (%s)", size, buf);
        return;
    }
    Serial.printf("Got packet %s\n", buf);
    hand->parseCommand(buf);
}
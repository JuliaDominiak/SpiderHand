#include "conn.h"


AsyncUDP Conn::udp;
uint16_t Conn::port;
Hand* Conn::hand;

void Conn::begin(uint16_t port, Hand* hand)
{
    Conn::hand = hand; 
    Conn::port = port;
    WiFi.mode(WIFI_AP); //we set WiFi mode to Access Point (AP)
    WiFi.softAP("hand", "244466666"); //we set network's name as "hand" and password as "244466666"
    udp.listen(port); //start listening on port 1420
    udp.onPacket(udpCallback); //when you get the packet, call the "udpCallback" function
}

void Conn::udpCallback(AsyncUDPPacket& packet){
    long begin = millis();
    char* buf = (char*)packet.data(); //get the packet's data
    size_t size = packet.length(); //get the packet's size
    if (size != 17){ //the packet consists of 17 chars as: (joint to move, value on x axis, value on y axis). each value has two decimal points an is left padded to 6 chars ex. (thu   9.00  12.00) 
        Serial.printf("Malformed packet (wrong size: %d) (%s)", size, buf);
        return;
    }
    Serial.printf("Got packet %s\n", buf);
    hand->parseCommand(buf); //pass the packet's data to the hand
    long end = millis();
    Serial.printf("Packet processing took %d ms\n", end - begin);
}
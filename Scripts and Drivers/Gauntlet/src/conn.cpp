#include "conn.h"

WiFiUDP Conn::Client;
const char* Conn::host;
uint16_t Conn::port;

void Conn::begin(const char* host, uint16_t port)
{
    Conn::host = host;
    Conn::port = port;
    WiFi.mode(WIFI_STA);
    WiFi.begin("hand", "244466666");
    //WiFi.softAP("gauntlet", "244466666");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(WiFi.status());
        delay(1000);
    }

    Serial.println("WiFi Connected");
    Client.begin(port);
}

void Conn::beginPacket(){
    Client.beginPacket(host, port);
}

void Conn::write(const char* buff, size_t size){
    Client.write((const uint8_t*)buff, size);
}

void Conn::endPacket(){
    Client.endPacket();
}
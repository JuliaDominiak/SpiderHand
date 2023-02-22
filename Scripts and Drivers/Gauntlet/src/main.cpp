#include <Arduino.h>
#include "gauntlet.h"
#include "conn.h"

Gauntlet gauntlet;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    gauntlet = Gauntlet(0x24, 0x19, 0xff, 0xff, 0xff, 0x2d);
    gauntlet.begin();
    Conn::begin("192.168.4.2", 80);
}

void loop()
{
    gauntlet.loop();
    yield();
}

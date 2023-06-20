#include <Arduino.h>
#include "gauntlet.h"
#include "conn.h"

Gauntlet gauntlet;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    gauntlet = Gauntlet(0x24, 0x19, 0x40, 0xff, 0xff, 0x2d, 0x33, 0xff);
    gauntlet.setCalibration(-175,-40,-170,-360, -100, -230, 0, 100, 0, 100, -32, 40, -66, 12);
    gauntlet.begin();
    Conn::begin("255.255.255.255", 1420); //port >1024?
}

void loop()
{
    gauntlet.loop();
    yield();
}

#include <Arduino.h>
#include "gauntlet.h"
#include "conn.h"

Gauntlet gauntlet;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    gauntlet = Gauntlet(0x24, 0x19, 0x40, 0xff, 0xff, 0x2d, 0xff);
    gauntlet.setCalibration(-60,-10,-60,-150, -20, -120, 0, 100, 0, 100, 0, 50, -15, 50);
    gauntlet.begin();
    Conn::begin("255.255.255.255", 1420); //port >1024?
}

void loop()
{
    gauntlet.loop();
    yield();
}

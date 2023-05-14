#include <Arduino.h>
#include "conn.h"
#include "hand.h"

Hand hand = Hand();

void setup() {
  Serial.begin(115200);
  Serial.println("setup begin");
  hand.addServo("ind", 0, 2);
  hand.addServo("ind", 1, 3);
  hand.addServo("mid", 0, 4);
  Conn::begin("192.168.4.2", 80, &hand);
}

void loop() {
}
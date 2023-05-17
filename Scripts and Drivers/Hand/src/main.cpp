#include <Arduino.h>
#include "conn.h"
#include "hand.h"

Hand *hand;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("setup begin");
  hand = new Hand();
  Serial.println("zyje");
  hand->addServo("thu", 0, 0, 397, 479);
  hand->addServo("ind", 0, 1, 384, 150);
  hand->addServo("mid", 0, 2, 150, 465);
  hand->addServo("wri", 0, 3, 150, 510);
  hand->addServo("wri", 1, 4, 307, 150);
  //hand->addServo("wri", 2, 5, 196, 540);
  hand->addServo("elb", 2, 6, 433, 150);
  Conn::begin("192.168.4.2", 80, hand);
}

void loop() {
}
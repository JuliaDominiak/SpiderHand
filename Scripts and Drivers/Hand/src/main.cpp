#include <Arduino.h>
#include "conn.h"
#include "hand.h"

Hand *hand;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("setup begin");
  hand = new Hand();
  hand->addServo("thu", 0, 0, 397, 479); //thumb, x axis, PCA port 0, min servo position, max servo position
  hand->addServo("ind", 0, 1, 384, 150);
  hand->addServo("mid", 0, 2, 150, 465);
  hand->addServo("wri", 0, 3, 300, 150); //wrist, x axis, PCA port 3, min servo position, max servo position
  hand->addServo("wri", 1, 4, 607, 300); //wrist, y axis, PCA port 4, min servo position, max servo position
  //hand->addServo("wri", 2, 5, 196, 540);
  //we cut through the VCC line of the PCA to provide two different voltages, 0-7 5V and 8-15 7.5V as the elbow needed higher voltage
  hand->addServo("elb", 0, 8, 433, 150);
  Conn::begin(1420, hand); // start the connection on port 1420
  Serial.println("setup done");
}

void loop() {
}
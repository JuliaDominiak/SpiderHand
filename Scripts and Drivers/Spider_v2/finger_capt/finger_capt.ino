#include <Wire.h>
#include "Adafruit_MPR121.h"

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int a=0;
int tresh[3]={300,300,300};

const char *ssid = "circuits4you";
const char *pass = "password"; 

unsigned int localPort = 2000; 

IPAddress ServerIP(192,168,4,1);
IPAddress ClientIP(192,168,4,2);

WiFiUDP udp;

char buffer;

void setup() {
  Serial.begin(9600);

WiFi.begin(ssid, pass);   //Connect to access point

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(WiFi.status());
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    
    //Start UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());

  while (!Serial) { 
    delay(10);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
}

void loop() {

  currtouched = cap.touched();
  uint8_t a = (cap.filteredData(0)<=tresh[0]) | ((cap.filteredData(1)<=tresh[1])<<1) | ((cap.filteredData(2)<=tresh[2])<<2);

  // if(cap.filteredData(0)>tresh[0] && cap.filteredData(1)>tresh[1] && cap.filteredData(2)>tresh[2]) {a=0;}//111
  // if(cap.filteredData(0)<tresh[0] && cap.filteredData(1)>tresh[1] && cap.filteredData(2)>tresh[2]) {a=1;}//110
  // if(cap.filteredData(0)>tresh[0] && cap.filteredData(1)<tresh[1] && cap.filteredData(2)>tresh[2]) {a=2;}//101
  // if(cap.filteredData(0)<tresh[0] && cap.filteredData(1)<tresh[1] && cap.filteredData(2)>tresh[2]) {a=3;}//100
  // if(cap.filteredData(0)>tresh[0] && cap.filteredData(1)>tresh[1] && cap.filteredData(2)<tresh[2]) {a=4;}//011
  // if(cap.filteredData(0)<tresh[0] && cap.filteredData(1)>tresh[1] && cap.filteredData(2)<tresh[2]) {a=5;}//010
  // if(cap.filteredData(0)>tresh[0] && cap.filteredData(1)<tresh[1] && cap.filteredData(2)<tresh[2]) {a=6;}//001
  // if(cap.filteredData(0)<tresh[0] && cap.filteredData(1)<tresh[1] && cap.filteredData(2)<tresh[2]) {a=7;}//000
  
Serial.println(cap.filteredData(0));
Serial.println(cap.filteredData(1));
Serial.println(cap.filteredData(2));
  Serial.println(a);

  // sprintf(buffer, "%d", a);
  buffer = a;

  int cb = udp.parsePacket();
    if (!cb) 
    {
      //If serial data is recived send it to UDP
      if(1>0)
        {
        udp.beginPacket(ServerIP, 2000);  //Send Data to Master unit
        udp.write(a);
        udp.endPacket();
        }
    }

  delay(10);
}

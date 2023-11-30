#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "circuits4you";
const char *pass = "password"; 

int pwm=150;

unsigned int localPort = 2000; // local port to listen for UDP packets

IPAddress ServerIP(192,168,4,1);
IPAddress ClientIP(192,168,4,2);

WiFiUDP udp;

char packetBuffer;

void setup()
{
    Serial.begin(9600);
    Serial.println();
    WiFi.softAP(ssid, pass);   

    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
}

void loop()
{
    int cb = udp.parsePacket();
    if (cb) 
    {
      udp.read(&packetBuffer, 1);
      Serial.printf("%d\n",packetBuffer);
      delay(20);
    }

    uint8_t bit0 = packetBuffer & 0b00000001;
    uint8_t bit1 = packetBuffer & 0b00000010;
    uint8_t bit2 = packetBuffer & 0b00000100;
    Serial.print(bit0);Serial.print(bit1);Serial.print(bit2);Serial.println("END");
    if(bit0==1) (analogWrite(14, pwm));
    if(bit0==0) (analogWrite(14, 0));
    if(bit1==2) (analogWrite(12, pwm));
    if(bit1==0) (analogWrite(12, 0));
    if(bit2==4) (analogWrite(13, pwm));
    if(bit2==0) (analogWrite(13, 0));


    // if(packetBuffer==0){digitalWrite(14,LOW); digitalWrite(12,LOW); digitalWrite(13,LOW);};
    // if(packetBuffer==1){digitalWrite(14,HIGH); digitalWrite(12,LOW); digitalWrite(13,LOW);};
    // if(packetBuffer==2){digitalWrite(14,LOW); digitalWrite(12,HIGH); digitalWrite(13,LOW);};
    // if(packetBuffer==3){digitalWrite(14,HIGH); digitalWrite(12,HIGH); digitalWrite(13,LOW);};
    // if(packetBuffer==4){digitalWrite(14,LOW); digitalWrite(12,LOW); digitalWrite(13,HIGH);};
    // if(packetBuffer==5){digitalWrite(14,LOW); digitalWrite(12,HIGH); digitalWrite(13,LOW);};
    // if(packetBuffer==6){digitalWrite(14,LOW); digitalWrite(12,HIGH); digitalWrite(13,HIGH);};
    // if(packetBuffer==7){digitalWrite(14,HIGH); digitalWrite(12,HIGH); digitalWrite(13,HIGH);};
}
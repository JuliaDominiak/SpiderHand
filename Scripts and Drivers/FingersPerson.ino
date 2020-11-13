#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

const char* ssid = "palce";
const char* pw = "22345678";
byte data[200] ={};
int packetsize = 0;
int arr[5];
String receiveddata="";
WiFiUDP Server;

void setup() {
pinMode(16, OUTPUT);
pinMode(15, OUTPUT);
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
pinMode(14, OUTPUT);

pwm.setup(16,1000,256)
pwm.setup(15,1000,256)
pwm.setup(13,1000,256)
pwm.setup(12,1000,256)
pwm.setup(14,1000,256)
  
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,pw,11);
  WiFi.begin();
  Server.begin(80);
  Serial.println("Server started...");
}

void loop() {
 
    char message = Server.parsePacket();
    packetsize = Server.available();
    if (message)
    {
     Server.read(data,packetsize);
     IPAddress remoteip=Server.remoteIP();
     //Server.write(data);
     Server.endPacket();
    }

    if(packetsize) {
      for (int i=0;packetsize > i ;i++)
      {
        //Serial.println(data[i]);
      }
    }

memcpy(arr, data, 20);
Serial.print(arr[0]);
Serial.print("\t"); 
Serial.print(arr[1]);
Serial.print("\t");
Serial.print(arr[2]);
Serial.print("\t");
Serial.print(arr[3]);
Serial.print("\t");
Serial.print(arr[4]);
Serial.println("");


if(arr[0]==2) {digitalWrite(14, HIGH); pwm.stop(14);}
if(arr[0]==1) {pwm.start(14);}
if(arr[0]==0) {digitalWrite(14, LOW); pwm.stop(14);}

if(arr[1]==2) {digitalWrite(12, HIGH);pwm.stop(12);}
if(arr[1]==1) {pwm.start(12);}
if(arr[1]==0) {digitalWrite(12, LOW);pwm.stop(12);}

if(arr[2]==2) {digitalWrite(13, HIGH);pwm.stop(13);}
if(arr[2]==1) {pwm.start(13);}
if(arr[2]==0) {digitalWrite(13, LOW);pwm.stop(13);}

if(arr[3]==2) {digitalWrite(15, HIGH);pwm.stop(15);}
if(arr[3]==1) {pwm.start(15);}
if(arr[3]==0) {digitalWrite(15, LOW);pwm.stop(15);}

if(arr[4]==2) {digitalWrite(16, HIGH);pwm.stop(16);}
if(arr[4]==1) {pwm.start(16);}
if(arr[4]==0) {digitalWrite(16, LOW);pwm.stop(16);}

}

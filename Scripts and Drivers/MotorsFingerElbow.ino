#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVO_FREQ 50
uint8_t serv_p1 = 0;
uint8_t serv_p2 = 1;
uint8_t serv_p3 = 2;
uint8_t serv_nad = 3;
uint8_t serv_lok = 4;

int sensor_p1=0;
int sensor_p2=0;
int sensor_p3=0;
int sensor_nad=0;
int sensor_lok=0;

int position_p1=0;
int position_p2=0;
int position_p3=0;
int position_nad=0;
int position_lok=0;

int i=0;
int j=0;

#define SERVOMIN  200 
#define SERVOMAX  300 

const char* ssid = "ramie";
const char* pw = "22345678";
byte data[200] ={};
int packetsize = 0;
int arr[5];
String receiveddata="";
WiFiUDP Server;

void setup() {
  Serial.begin(115200);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(100);
  
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


///////////////////////////////////////////////////////
//Finger 1 - thumb
sensor_p1=1003-1.30*arr[4];
if (sensor_p1>400) {sensor_p1=400;}
if (sensor_p1<100) {sensor_p1=100;}

if (sensor_p1 > position_p1) 
  { 
    position_p1 = position_p1 + 1;
    if (position_p1>400) {position_p1=400;}
    pwm.setPWM(serv_p1, 0, position_p1);
  }
  
  if (sensor_p1 < position_p1) 
  { 
    position_p1 = position_p1 - 1;
    if (position_p1<100) {position_p1=100;}
    pwm.setPWM(serv_p1, 0, position_p1);
  }
  
///////////////////////////////////////////////////////
//Finger 2 - index finger
sensor_p2=12*arr[1]-10580;
if (sensor_p2>400) {sensor_p2=400;}
if (sensor_p2<100) {sensor_p2=100;}

if (sensor_p2 > position_p2) 
  { 
    position_p2 = position_p2 + 1;
    if (position_p2>400) {position_p2=400;}
    pwm.setPWM(serv_p2, 0, position_p2);
  }
  
  if (sensor_p2 < position_p2) 
  { 
    position_p2 = position_p2 - 1;
    if (position_p2<100) {position_p2=100;}
    pwm.setPWM(serv_p2, 0, position_p2);
  }
  
///////////////////////////////////////////////////////  
//Finger 3 - middle finger
sensor_p3=6839-7.31*arr[0];
if (sensor_p3>400) {sensor_p3=400;}
if (sensor_p3<100) {sensor_p3=100;}

if (sensor_p3 > position_p3) 
  { 
    position_p3 = position_p3 + 1;
    if (position_p3>400) {position_p3=400;}
    pwm.setPWM(serv_p3, 0, position_p3);
  }
  
  if (sensor_p3 < position_p3) 
  { 
    position_p3 = position_p3 - 1;
    if (position_p3<100) {position_p3=100;}
    pwm.setPWM(serv_p3, 0, position_p3);
  }
  
/////////////////////////////////////////////////////// 
//Wrist
sensor_nad=500-2.22*arr[2];
if (sensor_nad>500) {sensor_nad=500;}
if (sensor_nad<100) {sensor_nad=100;}

if (sensor_nad > position_nad) 
  { 
    position_nad = position_nad + 1;
    if (position_nad>500) {position_nad=500;}
    pwm.setPWM(serv_nad, 0, position_nad);
  }
  
  if (sensor_nad < position_nad) 
  { 
    position_nad = position_nad - 1;
    if (position_nad<100) {position_nad=100;}
    pwm.setPWM(serv_nad, 0, position_nad);
  }

/////////////////////////////////////////////////////// 
//Elbow

sensor_lok=800-arr[3];
if (sensor_lok>409) {sensor_lok=409;}
if (sensor_lok<155) {sensor_lok=155;}

if (sensor_lok > position_lok) 
  { 
    position_lok = position_lok + 1;
    if (position_lok>409) {position_lok=409;}
    pwm.setPWM(serv_lok, 0, position_lok);
  }
  
  if (sensor_nad < position_nad) 
  { 
    position_lok = position_lok - 1;
    if (position_lok<155) {position_lok=155;}
    pwm.setPWM(serv_lok, 0, position_lok);
  }




Serial.print(arr[4]);
Serial.print("\t");
Serial.print(sensor_p1);
Serial.print("\t");
Serial.print("\t");
Serial.print(arr[1]);
Serial.print("\t");
Serial.print(sensor_p2);
Serial.print("\t");
Serial.print("\t");
Serial.print(arr[0]);
Serial.print("\t");
Serial.print(sensor_p3);
Serial.print("\t");
Serial.print("\t");
Serial.print(arr[2]);
Serial.print("\t");
Serial.print(sensor_nad);
Serial.print("\t");
Serial.print("\t");
Serial.print(arr[3]);
Serial.print("\t");
Serial.print(sensor_lok);
Serial.println("");




}

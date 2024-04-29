//Tiny GPS
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include "String.h"
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

SoftwareSerial serial_connection(3,1 ); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;

//

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6E8xXcYA6"
#define BLYNK_TEMPLATE_NAME "GUNGGING"
#define BLYNK_AUTH_TOKEN "u6cb3DMP0xfj2XYT4WtWXgPQEIHSURK1"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial



//NTPClient time

#include "time.h"
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 25200;
const int   daylightOffset_sec = 0;

        // Variables to save time
char timeHour[3];
char timeMinute[3];
char timeSecond[3];
  
//NTP



// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SAHOUSE2020  2G";
char pass[] = "11012709";
int hr;
int minx;
int sec;
String strTime="99:99:99";


  


  

//
void setup(){
 configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
 printLocalTime();

  pinMode(17,OUTPUT);
  digitalWrite(17,1);
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop(){

  strTime=String(atoi(timeHour))+":"+String(atoi(timeMinute))+":"+String(atoi(timeSecond));
  hr=atoi(timeHour);
  minx=atoi(timeMinute);

  Blynk.run();
  Blynk.virtualWrite(V1,strTime);
  if(digitalRead(17)==1){
    Blynk.virtualWrite(V3,"OFF");
  }
  if(digitalRead(17)==0){
    Blynk.virtualWrite(V3,"ON");
  }
  
  if((digitalRead(4)==1)||((hr>=9&&hr<=18)&&(minx>=5&&minx<=10))||((hr>=9&&hr<=18)&&(minx>=35&&minx<=40))){
    digitalWrite(17,0);
  }else digitalWrite(17,1);
  if(digitalRead(0)==1){
    digitalWrite(17,1);
  }
  printLocalTime();
  delay(200);
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  

  strftime(timeHour,3, "%H", &timeinfo);  //%H:%M:%S
  Serial.print(timeHour);
  Serial.print(":");

  
  strftime(timeMinute,3, "%M", &timeinfo);
  Serial.print(timeMinute);
  Serial.print(":");

  
  strftime(timeSecond,3, "%S", &timeinfo);
  Serial.println(timeSecond);
  
  
}



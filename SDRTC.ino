#include <SD.h>
#include <RTClib.h>
#include <Wire.h>



RTC_DS1307 rtc;
File imsfile;
const int cs=4;

void setup() {
 Serial.begin(9600);
 SD.begin();
 //puts sd card in workig mood
  rtc.begin();
  //starts rtc
  Wire.begin();
  // This line sets the RTC with an explicit date & time,

pinMode(cs, INPUT);

Serial.println("INITIALIZATION CHECK");
//To check if rtc and sd card installlization are done.
if(rtc.begin())
{
  Serial.println("RTC Initialized");
}
  else 
        {
          Serial.println("RTC failed");
        }

if(SD.begin())
{
  Serial.println("SD-Card initialized");
}
  else
        {
          Serial.println("SD-Card failed");
        }
Serial.println("PROGRAM STARTED");
delay(4000);
}

void loop() {
  Serial.println();
DateTime now =rtc.now();
Serial.println("```````````````````````````````````````");   
Serial.print(now.hour(),DEC);
Serial.print(" - ");
Serial.print(now.minute(),DEC);
Serial.print(" - ");
Serial.print(now.second(),DEC);
Serial.print("                 ");
Serial.print(now.day(),DEC);
Serial.print(" : ");
Serial.print(now.month(),DEC);
Serial.print(" : ");
Serial.print(now.year(),DEC);
Serial.println("Its Working");
Serial.println();

 imsfile = SD.open("sdcard.txt", FILE_WRITE); 
  if (imsfile) 
  {
    

imsfile.println("```````````````````````````````````````");   
imsfile.print(now.day(),DEC);
imsfile.print(" - ");
imsfile.print(now.month(),DEC);
imsfile.print(" - ");
imsfile.print(now.year(),DEC);
imsfile.print("                 ");
imsfile.print(now.hour(),DEC);
imsfile.print(" : ");
imsfile.print(now.minute(),DEC);
imsfile.print(" : ");
imsfile.print(now.second(),DEC);
imsfile.println("Its Working");
imsfile.println();
imsfile.close();
Serial.println("Data saved");
  }
  else 
  {
    Serial.println("error opening sdcard.txt");
  }
}

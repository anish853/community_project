#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include <SD.h>

//SD card and RTC related stuff
RTC_DS1307 rtc ;
File imsfile;
const int cs = 10;


//Ultrasonic Sensor related stuff
#define  Trig 3
#define  Echo 2
int distanceCm = 0; 
int duration = 0;



// voltage sensor related stuff
#define voltageSensor  A2  
float voltage ;
float value;
float maped;
float r2 = 30000.00 ;
float r1 = 10000.00 ;


//current sensor related stuff
#define currentSensor A1
float current = 0.00 ;
float offsetted_val ;
float converted_voltage = 0.00;


// current sensing filtering stuff
int smooth[10] ;
int total = 0 ;
int readingNo = 0 ;
float average = 0 ;






void setup() {

  Serial.begin(9600);

  SD.begin();
  rtc.begin();
  Wire.begin();

  pinMode(cs, OUTPUT);

  pinMode(Echo , INPUT);
  pinMode(Trig , OUTPUT);

Serial.println("INITIALIZATION");

if(rtc.begin())
{
  Serial.println("RTC Initialization Successfull");
}
  else 
        {
          Serial.println("RTC initialization Failed");
        }

if(SD.begin())
{
  Serial.println("SD Card initialization Successfull");
}
  else
        {
          Serial.println("SD Card initialization Failed");
        }


Serial.println(" PROGRAM STARTED");
 
 delay(5000);
  
}

void loop() {

UltraSonic_Sensor();

Serial.println();
DateTime now =rtc.now();  
Serial.print(now.year() , DEC);
Serial.print(" - ");
Serial.print(now.month() , DEC);
Serial.print(" - ");
Serial.print(now.day() , DEC);
Serial.print("                 ");
Serial.print(now.hour() , DEC);
Serial.print(" : ");
Serial.print(now.minute() , DEC);
Serial.print(" : ");
Serial.print(now.second() , DEC);
Serial.println();
Serial.print("Distance From Ultrasonic Sensor :  ");
Serial.println(UltraSonic_Sensor());
Serial.print("Current Value :  ");
Serial.println(currentSensing());
Serial.print("Voltage Value :  ");
Serial.println(voltageSensing());








   
  imsfile = SD.open("sdcard.txt", FILE_WRITE); 
  if (imsfile) 
  {
    

imsfile.println("_________________________________________________");   
imsfile.print(now.year() , DEC);
imsfile.print(" - ");
imsfile.print(now.month() , DEC);
imsfile.print(" - ");
imsfile.print(now.day() , DEC);
imsfile.print("                 ");
imsfile.print(now.hour() , DEC);
imsfile.print(" : ");
imsfile.print(now.minute() , DEC);
imsfile.print(" : ");
imsfile.print(now.second() , DEC);
imsfile.println();
imsfile.print("Distance From Ultrasonic Sensor :  ");
imsfile.println(UltraSonic_Sensor());
imsfile.print("Current Value :  ");
imsfile.println(currentSensing());
imsfile.print("Voltage Value :  ");
imsfile.println(voltageSensing());
imsfile.println("_________________________________________________"); 
    
imsfile.close();
Serial.println("-:Data saved:-");
  }
  else 
  {
    Serial.println("error opening sdcard.txt");
  }
  
}



float currentSensing()
{
  total = total - smooth[readingNo];
  smooth[readingNo] = analogRead(currentSensor);
  total =total + smooth[readingNo] ;
  readingNo++;
  if(readingNo >= 10)
  {readingNo = 0 ;}

 average = total / 10 ;
 converted_voltage = ((average * 5)/1024) ;
 converted_voltage = converted_voltage - 2.50 ;             // 2720 mV gives 1Amp of current
 current = converted_voltage/ 0.2720 ;
  return(current) ;
  
}


 float voltageSensing()
{
  value = analogRead(voltageSensor);
  voltage = (value*(5.0/682)*(r1 + r2))/r2 ;
  
  return (voltage);
}





int UltraSonic_Sensor()
{
 //makig a pulse for trigring Ultrasonic Sensor
digitalWrite(Trig, LOW);
delayMicroseconds(2);
digitalWrite(Trig, HIGH);
delayMicroseconds(10);
digitalWrite(Trig, LOW);
//Formulation
duration = pulseIn(Echo, HIGH);
distanceCm= duration*0.034/2;  
return(distanceCm);  
}
 
   

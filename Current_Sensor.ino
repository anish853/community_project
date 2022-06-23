float currentSensor= A1;
float current = 0.00 ;
float offsetted_val ;
float converted_voltage = 0.00;

// current sensing filtering stuff
int smooth[10] ;
int total = 0 ;
int readingNo = 0 ;
float average = 0 ;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(currentSensor, OUTPUT);

}

void loop() {
  total = total - smooth[readingNo];
  smooth[readingNo]= analogRead(currentSensor);
  total =total + smooth[readingNo] ;
  readingNo++;
  if(readingNo >= 10)
  {readingNo = 0 ;}

 average = total / 10 ;
 converted_voltage = ((average * 5)/1024) ;
 converted_voltage = converted_voltage - 2.50 ;             // 2720 mV gives 1Amp of current
 current = converted_voltage/ 0.2720 ;
 
Serial.print("Current Value :  ");
Serial.println(current);
}

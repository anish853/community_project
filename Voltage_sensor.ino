const float voltage_sensor= A2;  
float voltage ;
float value;
float r2 = 30000.00 ;
float r1 = 10000.00 ;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(voltage_sensor, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:

  value= analogRead(voltage_sensor);
  voltage= (value*(5.0/682)*(r1 + r2))/r2 ;
  Serial.print("Voltage Value :  ");
Serial.println(voltage);
}

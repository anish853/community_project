const float voltage_sensor= A1; 
float voltage;
float value;
int r1= 30000;
int r2= 7500;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(voltage_sensor, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:

  value= analogRead(voltage_sensor);
  voltage= ((value*5.0)/1024)*(r2/(r1 + r2)) ;

  Serial.println("Voltage Value : 10 v  ");

}


const int trig=3;
const int echo=2;
long duration , distance ;
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
Serial.begin(9600);

}

void loop() {
//first trig is low to make sure its in off condition

digitalWrite(trig, LOW); 
//Digital Write to declare the on/off state of the pin.
//Delay is add to make the pin off for specific time in which we want it off.
delayMicroseconds(2);


//Now setting trig high to set it in working state for a specific time.
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);

//pulseIn fumction helps us to measure time taken by the sound to recieve when emit through emitter towards object and then from object to reciever.
duration= pulseIn(echo, HIGH);

//distance = (time taken means duration)*(speed of sound)/2. we have didvide by 2 because the distance travel by sound wave is first from emitter to object then from object to reciever.
distance = duration*0.034/2;

Serial.print("Distance =");
Serial.print(distance);
Serial.print(" cm ");
//println prints the value in the next line
Serial.println();

delay(100);
}

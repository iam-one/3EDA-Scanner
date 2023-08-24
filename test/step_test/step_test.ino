const int dirPin = 2;
const int stepPin = 3;

void setup(){
  Serial.begin(9600);
  
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin,OUTPUT);
}

void loop(){
  /*
  stepMotor(HIGH);
  Serial.println("step high is done");
  delay(1000);

  stepMotor(LOW);
  Serial.println("step low is done");
  delay(1000);
  */
}

void stepMotor(int dir){
  digitalWrite(dirPin, dir);

  for (int step = 0; step < 200; step++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
}

const int DIRPIN = 2;
const int STEPPIN = 3;
const int STEP_TIME = 100;
const int MAX_STEP = 20;

void setup(){
    Serial.begin(9600);
}

void loop(){
    stepMotor(HIGH);
    delay(1000);
    Serial.println("Step HIGH is Done");

    stepMotor(LOW);
    delay(1000);
    Serial.println("Step LOW is Done");
}

void stepMotor(int dir)
{
  digitalWrite(DIRPIN, dir);
  for (int step = 1; step <= MAX_STEP; step++)
  {
    digitalWrite(STEPPIN, HIGH);
    delayMicroseconds(STEP_TIME / 2);
    digitalWrite(STEPPIN, LOW);
    delayMicroseconds(STEP_TIME / 2);

    Serial.println(step);
  }
}
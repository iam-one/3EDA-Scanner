#include <SharpIR.h> // Use SharpIR Library to get Distance

const int IR_PIN = 14; // IR SENSOR PIN = A0
const int S_STEPPIN = 2;
const int S_DIRPIN = 3;
const int P_STEPPIN = 4;
const int P_DIRPIN = 5;
const int TRIG_PIN = 6;
const int LIMIT_PIN = 7;

const float STEP_ANGLE = 1.8; // mm
const int MAX_STEP = 50; // mm
const int MAX_Z = 0; // mm
const int STEP_TIME = 200; // mm
const int PLATE_RADIUS = 750; // mm
const float MIN_DISTANCE = 52.5; // mm
const float ENTIRE_DISTANCE = PLATE_RADIUS + MIN_DISTANCE; // mm
const float LIMIT_DISTANCE = 2 * PLATE_RADIUS + MIN_DISTANCE; // mm
const int SENSOR_STEP = 1; // 2mm per 1 step
const int PLATE_STEP = 20;

boolean is_scan = false;

int irDistance = 0;
int objectDistance = 0;
int stepedZ = 0;

float pointX = 0;
float pointY = 0;
float pointZ = 0;

SharpIR ir(SharpIR::GP2Y0A41SK0F, IR_PIN);

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG_PIN, INPUT_PULLUP);
  pinMode(LIMIT_PIN, INPUT_PULLUP);
  pinMode(S_DIRPIN, OUTPUT);
  pinMode(S_STEPPIN, OUTPUT);
  pinMode(P_DIRPIN, OUTPUT);
  pinMode(P_STEPPIN, OUTPUT);
}

void loop()
{
  if (digitalRead(TRIG_PIN) == LOW)
  {
    for (int stepZ = 1; stepZ <= MAX_Z; stepZ++)
    {
      pointZ = 2 * stepZ;
      for (int stepV = 1; stepV <= MAX_STEP; stepV++)
      {
        if (digitalRead(LIMIT_PIN) == LOW){
          stepedZ = stepZ;
          break;
        }
        irDistance = 10 * ir.getDistance();
        if (irDistance > LIMIT_DISTANCE){
          stepedZ = stepZ;
          break;
        }
        scanPoint(stepV);
        stepPlate(HIGH);
      }
      stepSensor(HIGH);
    }
    sendPointcloud();

    // TODO: Get Init Step Location when it stopped manual
  }
  if (stepedZ != 0){
    stepSensor(LOW);
  }
}

void sendPointcloud()
{
  Serial.print(pointX);
  Serial.print(", ");
  Serial.print(pointY);
  Serial.print(", ");
  Serial.println(pointZ);
}

void scanPoint(int step)
{
  objectDistance = ENTIRE_DISTANCE - (irDistance * 10);

  pointX = -10 * objectDistance * sin(1.8 * step);
  pointY = -10 * objectDistance * cos(1.8 * step);
}

void stepSensor(int dir)
{
  if (dir == 1)
  digitalWrite(S_DIRPIN, dir);
  for (int step = 1; step <= (200 * SENSOR_STEP); step++)
  {
    digitalWrite(S_STEPPIN, HIGH);
    delayMicroseconds(STEP_TIME / 2);
    digitalWrite(S_STEPPIN, LOW);
    delayMicroseconds(STEP_TIME / 2);
  }
}

void stepPlate(int dir)
{
  digitalWrite(P_DIRPIN, dir);
  for (int step = 1; step <= (200 / PLATE_STEP); step++)
  {
    digitalWrite(P_STEPPIN, HIGH);
    delayMicroseconds(STEP_TIME / 2);
    digitalWrite(P_STEPPIN, LOW);
    delayMicroseconds(STEP_TIME / 2);
  }
}
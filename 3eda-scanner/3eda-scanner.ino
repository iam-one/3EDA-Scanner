#include <SharpIR.h> // Use SharpIR Library to get Distance

const int IR_PIN = 14; // IR SENSOR PIN = A0
const int S_STEPPIN = 2;
const int S_DIRPIN = 3;
const int P_STEPPIN = 4;
const int P_DIRPIN = 5;
const int TRIG_PIN = 6;
const int LIMIT_PIN = 7;

const int STEP_ANGLE = 1.8;
const int MAX_STEP = 50;
const int MAX_Z = 0;
const int STEP_TIME = 200;
const float ENTIRE_DISTANCE = 750 + 52.5;
const int SENSOR_STEP = 1; // 2mm per 1 step
const int PLATE_STEP = 20;

class PointCloud
{
public:
  float x, y, z;
};

boolean is_scan = false;

int objectDistance = 0;

SharpIR ir(SharpIR::GP2Y0A41SK0F, IR_PIN);
PointCloud point;

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
      for (int stepV = 1; stepV <= MAX_STEP; stepV++)
      {
        if (digitalRead(LIMIT_PIN) == LOW)
          is_scan = false;

        point.x, point.y, point.z = 0;
        scanPoint(stepV);
        stepPlate();
      }
      stepSensor();
    }
    sendPointcloud();
  }
}

void sendPointcloud()
{
  Serial.write(point.x);
  Serial.write(", ");
  Serial.write(point.y);
  Serial.write(", ");
  Serial.write(point.z);
  Serial.write("\n");
}

void scanPoint(int step)
{
  objectDistance = ENTIRE_DISTANCE - (ir.getDistance() * 10);

  point.x = -10 * objectDistance * sin(1.8 * step);
  point.y = -10 * objectDistance * cos(1.8 * step);
}

void stepSensor()
{
  digitalWrite(S_DIRPIN, HIGH);
  for (int step = 1; step <= (200 * SENSOR_STEP); step++)
  {
    digitalWrite(S_STEPPIN, HIGH);
    delayMicroseconds(STEP_TIME / 2);
    digitalWrite(S_STEPPIN, LOW);
    delayMicroseconds(STEP_TIME / 2);
  }
  digitalWrite(S_DIRPIN, LOW);
}

void stepPlate()
{
  digitalWrite(P_DIRPIN, HIGH);
  for (int step = 1; step <= (200 / PLATE_STEP); step++)
  {
    digitalWrite(P_STEPPIN, HIGH);
    delayMicroseconds(STEP_TIME / 2);
    digitalWrite(P_STEPPIN, LOW);
    delayMicroseconds(STEP_TIME / 2);
  }
  digitalWrite(P_DIRPIN, LOW);
}
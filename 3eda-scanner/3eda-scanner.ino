/*
3EDA-Scanner by one

exp_
This scanner works for scan the small object.
It gets distance from sensor to object, and calculate each point.
And it converts each point to point cloud, passes to raspberry pi.

*/

// Pin Declare
const int irPin = A0; // Sharp GP2Y0A41SK0F Model
const int sStepPin = 2; // sensor stepper pin
const int sDirPin = 3; // sensor stepper direction pin
const int pStepPin = 4; // plate stepper pin
const int pDirPin = 5; // plate stepper direction pin
const int trigPin = 6; // scan trigger pin
const int limitPin = 7; // scan emergency stop pin

// Constant Var Declare
const float STEP_ANGLE = 1.8; // degree(unit)
const float PLATE_RADIUS = 7.5; // cm(unit)
const float MIN_DISTANCE = 5.25; // cm(unit)
const float MAX_DISTANCE = PLATE_RADIUS + MIN_DISTANCE; // cm(unit)

const int STEP_HEIGHT = 10; // cm(unit), one z pointStep will be 0.5cm
const int STEP_PER_LAYER = 40; // loop(unit), it must be LCM of 200(pointStep), it can be affect to the precision of mesh.

const int STEP_LAYER = 2 * STEP_HEIGHT;
const int STEP_PER_POINT = 200 / STEP_PER_LAYER;

// Main Var Declare
float distance, objectDistance = 0.0;
float pointX, pointY, pointZ = 0.0;

boolean isWork = false;

void setup(){
  Serial.begin(9600);

  pinMode(irPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(limitPin, OUTPUT);

  pinMode(sStepPin, OUTPUT);
  pinMode(sDirPin, OUTPUT);
  pinMode(pStepPin, OUTPUT);
  pinMode(pDirPin, OUTPUT);
}

void loop(){
  if (digitalRead(trigPin) == LOW){
    isWork = true;
    // TODO: add limit feature when emergency

    for (int layerStep = 0; layerStep < STEP_LAYER; layerStep++){
      for (int pointStep = 0; pointStep < STEP_PER_LAYER; pointStep++){
        distance = 13 * pow(analogRead(irPin) * 0.0048828125, -1); // From GP2Y0A41SK0F Datasheet
        objectDistance = MAX_DISTANCE - distance; // calculate distance from sensor to scan object

        if (MIN_DISTANCE < distance < MAX_DISTANCE){ // if distance is valid
          // get point from distance
          pointX = -10 * objectDistance * sin(1.8 * STEP_PER_POINT * pointStep);
          pointY = -10 * objectDistance * cos(1.8 * STEP_PER_POINT * pointStep);
          pointZ = 0.5 * layerStep;

          Serial.print(pointX, 6);
          Serial.print(", ");
          Serial.print(pointY, 6);
          Serial.print(", ");
          Serial.println(pointZ, 6);
        }

        stepPlate(HIGH);
      }
      stepSensor(HIGH);
    }

    Serial.println("done");
  }
}

void stepSensor(int dir){
  digitalWrite(sDirPin, dir);
  for (int stepSensor = 0; stepSensor < 500; stepSensor++)
  {
    digitalWrite(sStepPin, HIGH);
    delayMicroseconds(50);
    digitalWrite(sStepPin, LOW);
    delayMicroseconds(50);
  }
}

void stepPlate(int dir){
  digitalWrite(pDirPin, dir);
  for (int stepPlate = 0; stepPlate < STEP_PER_POINT; stepPlate++)
  {
    digitalWrite(pStepPin, HIGH);
    delayMicroseconds(50);
    digitalWrite(pStepPin, LOW);
    delayMicroseconds(50);
  }
}
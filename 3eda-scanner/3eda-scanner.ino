/*
3EDA-Scanner by one

exp_
This scanner works for scan the small object.
It gets distance from sensor to object, and calculate each point.
And it converts each point to point cloud, passes to raspberry pi.

*/

// Pin Declare
const int irPin = A0; // Sharp GP2Y0A41SK0F Model
const int sDirPin = 2; // sensor stepper direction pin
const int sStepPin = 3; // sensor stepper pin
const int pDirPin = 4; // plate stepper direction pin
const int pStepPin = 5; // plate stepper pin
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

boolean isLimited = false;
int tmpLayerStep, tmpPointStep = 0;

// Work Block
void setup(){
  Serial.begin(9600);

  pinMode(irPin, INPUT);
  pinMode(trigPin,INPUT_PULLUP);
  pinMode(limitPin, INPUT_PULLUP);

  pinMode(sStepPin, OUTPUT);
  pinMode(sDirPin, OUTPUT);
  pinMode(pStepPin, OUTPUT);
  pinMode(pDirPin, OUTPUT);
}

void loop(){
  if (digitalRead(trigPin) == LOW){
    for (int layerStep = 0; layerStep < STEP_LAYER; layerStep++){
      for (int pointStep = 0; pointStep < STEP_PER_LAYER; pointStep++){
        if (digitalRead(limitPin) == LOW){
          // store step data to tmp var
          tmpLayerStep = layerStep;
          tmpPointStep = pointStep;

          isLimited = true;
          break;
        }

        distance = 13 * pow(analogRead(irPin) * 0.0048828125, -1); // From GP2Y0A41SK0F Datasheet
        objectDistance = MAX_DISTANCE - distance; // calculate distance from sensor to scan object

        if (MIN_DISTANCE < distance && distance < MAX_DISTANCE){ // if distance is valid
          // get point from distance
          pointX = -1 * objectDistance * sin(radians(1.8 * STEP_PER_POINT * (pointStep + 1)));
          pointY = -1 * objectDistance * cos(radians(1.8 * STEP_PER_POINT * (pointStep + 1)));
          pointZ = 0.5 * layerStep;

          // send point data to raspberry pi via serial
          Serial.print(pointX, 6);
          Serial.print(", ");
          Serial.print(pointY, 6);
          Serial.print(", ");
          Serial.println(pointZ, 6);
        }
        stepPlate(HIGH); // move plate to scan next point
      }
      if (isLimited == true) break;

      stepSensor(HIGH); // move sensor to scan next layer
    }

    Serial.println("ended"); // send end signal to raspberry pi via serial

    for (int layerStep = 0; layerStep < tmpLayerStep; layerStep++) stepSensor(LOW);
    for (int pointStep = 0; pointStep < tmpPointStep; pointStep++) stepPlate(LOW);

    isLimited = false;
  }
}

void stepSensor(int dir){
  digitalWrite(sDirPin, dir);
  for (int stepSensor = 0; stepSensor < 500; stepSensor++)
  {
    digitalWrite(sStepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(sStepPin, LOW);
    delayMicroseconds(2000);
  }
}

void stepPlate(int dir){
  digitalWrite(pDirPin, dir);
  for (int stepPlate = 0; stepPlate < STEP_PER_POINT; stepPlate++)
  {
    digitalWrite(pStepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(pStepPin, LOW);
    delayMicroseconds(2000);
  }
}

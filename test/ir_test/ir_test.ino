const int irPin = A0;

float distance = 0;

void setup(){
    Serial.begin(9600);
}

void loop(){
    distance = 13 * pow(analogRead(irPin) * 0.0048828125, -1); // From GP2Y0A41SK0F Datasheet
    Serial.print("IR DISTANCE: ");
    Serial.print(distance);
    Serial.println("cm");

    delay(200);
}

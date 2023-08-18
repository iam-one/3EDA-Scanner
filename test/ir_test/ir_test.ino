#include <SharpIR.h>

const int IR_PIN = 14;

int irDistance = 0;

SharpIR ir(SharpIR::GP2Y0A41SK0F, IR_PIN);

void setup(){
    Serial.begin(9600);
}

void loop(){
    irDistance = ir.getDistance();
    Serial.print("IR DISTANCE: ");
    Serial.print(irDistance);
    Serial.println("...");
}
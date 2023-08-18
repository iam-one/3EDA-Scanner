int pointX = 12;
int pointY = 19;
int pointZ = 38;

void setup(){
    Serial.begin(9600);

    sendPointcloud();
}

void loop(){
    if (Serial.available()){
        Serial.print("Received: ");
        Serial.println(Serial.read());
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
void setup(){
    Serial.begin(9600);
}

void loop(){
  Serial.print(0.000000);
  Serial.print(", ");
  Serial.print(0.000000);
  Serial.print(", ");
  Serial.println(0.000000);

  delay(500);
}

void setup()
{
  pinMode(14, INPUT);
  Serial.begin(115200);
}


void loop() 
{
  if (digitalRead(14) == HIGH)
  {
    Serial.println("HIGH");
  }
  else
  {
    Serial.println("LOW");
  }
  delay(100);
}

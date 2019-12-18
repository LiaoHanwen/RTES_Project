void setup()
{
  pinMode(16, INPUT);
  Serial.begin(115200);
}


void loop() 
{
  if (digitalRead(16) == HIGH)
  {
    Serial.println("HIGH");
  }
  else
  {
    Serial.println("LOW");
  }
  delay(100);
}

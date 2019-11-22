void setup() {
  Serial.begin(57600);
}

int i = 0;

void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("%d\n", i);
  analogWrite(14, i);
  i += 10;
  if (i > 1023)
    i = 0;
  delay(100);
}

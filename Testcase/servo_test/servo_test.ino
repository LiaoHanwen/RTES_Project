void setup() {
  Serial.begin(115200);
}

int i = 400;
int st = 10;

void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("%d\n", i);
  analogWrite(14, i);
  i += st;
  if (i >= 1000)
  {
    st = -10;
  }
  if (i <= 400)
  {
    st = 10;
  }
  delay(100);
}

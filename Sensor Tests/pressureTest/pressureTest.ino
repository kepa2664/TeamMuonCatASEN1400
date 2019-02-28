float pressure;

void setup() {
  pinMode(A3, INPUT);
  Serial.begin(9600);
}

void loop() {
  pressure = (analogRead(A3)/204.6-0.5)*15/4;
  pressure = constrain(pressure, 0, 15);
  Serial.println(pressure);
  delay(5);
}

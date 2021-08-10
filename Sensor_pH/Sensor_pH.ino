void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  Serial.println("Test pH:...");
}

void loop() {
  // put your main code here, to run repeatedly:
  float Value_sensor, sum = 0, _val;
  for(int i = 0; i < 10; i++)
  {
    Value_sensor = analogRead(A0);
    delay(10);
    sum += Value_sensor;
  }
  _val = sum/10;
  float Voltage = _val * (5.0 / 1024.0);
  float pH = 7 + ((2.5 - Voltage)/0.18);
  Serial.print("Vol: ");
  Serial.print(Voltage);
  Serial.print(", pH: ");
  Serial.println(pH);
  delay(3000);
}

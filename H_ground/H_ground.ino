#define H_Pin A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Check Humidity of ground...!");
}

void loop() {
  // put your main code here, to run repeatedly:
  int _Val_read = analogRead(H_Pin);
  int _H_data = map(_Val_read, 0, 1023, 0, 100);
  Serial.print("Soil Moisture: ");
  Serial.print(_H_data);
  Serial.println("%");
//  if (_Val_read >=900 && _Val_read <= 1023){
//    Serial.println("Ban chua cam cam bien vao dat");
//    delay(1000);
//    return;
//  }
//  if(_Val_read < 500){
//    Serial.print(_Val_read);
//    Serial.println(" - Dat qua uot");
//  } else if(_Val_read >= 500 && _Val_read < 750)
//  {
//    Serial.print(_Val_read);
//    Serial.println(" - Pham vi ly tuong");
//  } else {
//    Serial.print(_Val_read);
//    Serial.println(" - Do am thap can tuoi nuoc");
//  }

  delay(500);
}

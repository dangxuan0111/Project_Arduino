#include "stdlib.h"
#include "Wire.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float sensor_value = analogRead(A0);
  float voltage = sensor_value * (5.0 / 1024.0);
  float turbidity = -1120.4*voltage*voltage + 5742.3*voltage - 4352.9;

  if (turbidity <= 0){
    turbidity = 0;
    }
    
  Serial.print("Voltage: ");
  Serial.println(voltage);
  Serial.println("Turbidity");
  Serial.println(turbidity);
  delay(1000);
}

#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#define DHTPIN A0
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
//Khởi tạo với các chân
LiquidCrystal lcd(7, 6, 2, 3, 4, 5);
 
void setup() {
  lcd.begin(16, 2);
  dht.begin();
  lcd.print("Wellcome to HF");
  delay(2000);
  
}
 
void loop() {
  float h = dht.readHumidity();
  float  t = dht.readTemperature();
  lcd.clear();
  lcd.print("Checking...");
  if(isnan(t) || isnan(h)){
    lcd.clear();
    lcd.print("Fail read DHT...");
    delay(500);
    return;
  } else {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Temperature: ");
     lcd.setCursor(12, 0);
     lcd.print(t);
     lcd.setCursor(0, 1);
     lcd.print("Humidity: ");
     lcd.setCursor(10, 1);
     lcd.print(h);
     delay(1000);
  }
}

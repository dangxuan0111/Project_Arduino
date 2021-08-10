// Humidity - Temperature Library
#include <DHT.h>
#include <DHT_U.h>

// OLED LIBRARY 
#include <U8g2lib.h>
#include <U8x8lib.h>

// WIFI LIBRARY
//#include <WiFi.h>

// THE DHT USED
#define DHTTYPE DHT22
#define DHTPIN 34

DHT dht(DHTPIN, DHTTYPE);

// THE OLED USED
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock */ 15, /* data */ 4, /*reset */ 16);

void setup() {
  // put your setup code here, to run once:
  u8x8.begin();
  Serial.begin(9600);
  dht.begin();
  u8x8.setCursor(0, 0);
  u8x8.print("Checking Temperature and Humidity...");
  Serial.print("Checking Temperature and Humidity...");
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String Ha = (String)h;
  String Ta = (String)t;
  if (isnan(h) || isnan(t)){
    u8x8.drawString(2, 0, "Fail read from DHT22");
    return;
  } else{
    u8x8.drawString(2, 0, "Nhiet do: ");
    u8x8.drawString(2, 9, Ta.c_str());
    u8x8.drawString(3, 0, "Do am: ");
    u8x8.drawString(3, 8, Ha.c_str());
    Serial.print(h,t);
  }
  delay(1000);
  u8x8.clear();
}

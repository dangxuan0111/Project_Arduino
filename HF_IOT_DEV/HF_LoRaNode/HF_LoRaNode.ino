//#include <heltec.h>
//
//
//
//#define BAND    433E6 //you can set band here directly,e.g. 868E6,915E6


#include <DHT.h>
#include <DHT_U.h>


#include <SPI.h>              // include libraries
#include <LoRa.h>
//#define PIN_RES 36
const long frequency = 433175000;  // LoRa Frequency

const int csPin = 10;          // LoRa radio chip select
const int resetPin = 9;        // LoRa radio reset
const int irqPin = 2;          // change for your board; must be a hardware interrupt pin

const char HF_KEY[] = "sQmAeaDK2LSslQmibxiW~fAA20d26";
byte _isSending = 0;


#define DHTPIN A0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Gateway - Gửi tin nhắn với enableInvertIQ 
//         - Nhận tin nhắn với Dis
// Node    - Gửi tin nhắn với DisInvertIQ 
//         - Nhận tin nhắn với Ena

void LoRa_rxMode(){
  LoRa.enableInvertIQ();                // active invert I and Q signals
  LoRa.receive();                       // set receive mode
}

// set up gateway in idle and enable receive messenge
void LoRa_txMode(){
  LoRa.idle();                          // set standby mode
  LoRa.disableInvertIQ();               // normal mode
}

//send packet from node to gateway
void LoRa_sendMessage(String message) {
  if (_isSending) return;
  _isSending = 1;
  LoRa_txMode();                        // set tx mode
  LoRa.beginPacket();                   // start packet
  //LoRa.setTxPower(17,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print(message);                  // add payload
  LoRa.endPacket(true);                 // finish packet and send it
}

//callback data from gateway
void onReceive(int packetSize) {
  String message = "";

  while (LoRa.available()) {
    message += (char)LoRa.read();
  }
  //printf();
}

void onTxDone() {  
  LoRa_rxMode();
  _isSending = 0;
}

boolean runEvery(unsigned long interval, unsigned long &previousMillis)
{  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

String StringFormat(const char* fmt, ...){
  va_list vaArgs;
  va_start(vaArgs, fmt);
  va_list vaArgsCopy;
  va_copy(vaArgsCopy, vaArgs);
  const int iLen = vsnprintf(NULL, 0, fmt, vaArgsCopy);
  va_end(vaArgsCopy);
  int iSize = iLen + 1;
  char* buff = (char*)malloc(iSize);
  vsnprintf(buff, iSize, fmt, vaArgs);
  va_end(vaArgs);
  String s = buff;
  free(buff);
  return String(s);
}



void LoRa_sendPacket(char* msg, int len){
  if (_isSending) return;
  _isSending = 1;
  LoRa_txMode();                        // set tx mode
  LoRa.beginPacket();                   // start packet
  LoRa.write((const uint8_t *)msg,(size_t)len);                  // add payload
  LoRa.endPacket(true);                 // finish packet and send it
}
String dtoString(float value, int decimal) {
  char _val[64];
  dtostrf(value, decimal+2, decimal, _val);
  return _val;
}
void LoopSend(unsigned long interval){
  static unsigned long _count = 0;
  static unsigned long _tStart = 0;
  float n = dht.readTemperature();
  float h = dht.readHumidity();
  String Na = dtoString(n, 2);
  String Ha = dtoString(h, 2);
//    int _val = analogRead(PIN_RES);
//    String _Val = dtoString(_val, 0);
    if (!runEvery(interval,_tStart)) return;
    ++_count;
  
  unsigned long t = millis();
  
  String sensor = StringFormat("{\"t\":%s,\"name\":\"Võ Việt Dũng\",\"c\":%s}", Na.c_str() , Ha.c_str());
// String sensor = StringFormat("{\"t\":%s,\"name\":\"Võ Việt Dũng\",\"c\":%s}", t, _Val.c_str());
  String message = StringFormat("{\"k\":\"%s\",\"s\":%s}",HF_KEY,sensor.c_str());
  LoRa_sendMessage(message);
  Serial.println(message);
  if(isnan(n) || isnan(h)){
    Serial.println("Error - Faild read data from DHT!");
    return;
    }else{
    Serial.println(n);
    Serial.println(h);   
    }
  
 }

/////////////////////////////////////////////
void setup() {
 
  Serial.begin(9600);                   // initialize serial UNO GPS
  dht.begin();
  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) {
    while (true);                       // if failed, do nothing
  }

  LoRa.onReceive(onReceive);
  LoRa.onTxDone(onTxDone);
  LoRa_rxMode();
}

void loop() {
  LoopSend(3000);
  }

//#define res_pin 36
//int res_val = 0;
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  delay(200);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  res_val = analogRead(res_pin);
//  Serial.println(res_val);
//  delay(1000);
//}
int quangtro = 4; //Thiết đặt chân analog đọc quang trở
void setup() {
  // Khởi tạo cộng Serial 9600
  Serial.begin(9600);
}

void loop() {
  int giatriQuangtro = analogRead(quangtro);// đọc giá trị quang trở
  
  Serial.println(giatriQuangtro); // Xuất giá trị ra Serial Monitor
  delay(1000);
}

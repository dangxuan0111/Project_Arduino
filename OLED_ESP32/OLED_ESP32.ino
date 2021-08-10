#include <U8g2lib.h>
#include <U8x8lib.h>

// THE OLED USED
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock */ 15, /* data */ 4, /*reset */ 16);

void setup(){
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
}

void loop(){
 // u8x8.setCursor(2,2);
  u8x8.print("H-Factor");
  delay(500);
  
  for(int i = 10; i > 0; i--){
    u8x8.clear();
    u8x8.setCursor(3,3);
    u8x8.print(i);
    delay(1000);
  }
  u8x8.drawString(0,2, "Wellcome to");
  u8x8.draw2x2String(0,3, "H-Factor");
  delay(1000);
  u8x8.clear();
  
}

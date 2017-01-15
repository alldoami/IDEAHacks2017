#include <Wire.h>
#include <AM2321.h>
#include "U8glib.h"

void setup() {
    
  // flip screen, if required
  // u8g.setRot180();
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) 
    u8g.setColorIndex(255);     // white
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT )
    u8g.setColorIndex(3);         // max intensity
  else if ( u8g.getMode() == U8G_MODE_BW )
    u8g.setColorIndex(1);         // pixel on
  Serial.begin(9600);
}

void draw(int temperature, int humidity) {
  // graphic commands to redraw the complete screen should be placed here  
  //u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_fixed_v0r);
  u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 15, 70, temperature);
}

void loop() {
 // u8g.firstPage();  
 // do {
  //  draw();
 // } while( u8g.nextPage() );
  readByAM2321();
  delay(500);
}

void readByAM2321()
{
  AM2321 am2321;
  am2321.read();
  Serial.print("(");
  Serial.print(am2321.temperature/10.0);
  Serial.print(", ");
  Serial.print(am2321.humidity/10.0);
  draw(am2321.temperature/10.0, am2321.humidity/10.0);
  Serial.println(')');
}

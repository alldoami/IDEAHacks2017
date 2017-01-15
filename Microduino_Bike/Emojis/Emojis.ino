#include "U8glib.h"
const int proxSensor = 6;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  
int distance = 0;


void draw(void) {
  u8g.setFont(u8g_font_osb21);
  if(distance > 250){
    u8g.drawStr( 15, 70, ":-)");
    u8g.setRot90();
  }else if(distance < 250 && distance > 115){
    u8g.drawStr( 15, 70, ":-(");
    u8g.setRot90();
  }else if(distance < 115){
    u8g.drawStr( 15, 70, "X-(");
    u8g.setRot90();
  }
  
}
void Proximity() {
  long duration, cm;
  pinMode(proxSensor, OUTPUT);
  digitalWrite(proxSensor, LOW);
  delayMicroseconds(2);
  digitalWrite(proxSensor, HIGH);
  delayMicroseconds(5);
  digitalWrite(proxSensor, LOW);

  pinMode(proxSensor, INPUT);
  duration = pulseIn(proxSensor, HIGH);

  // convert the time into a distance
  //inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  //Serial.print(inches);
  //Serial.print("in, ");
  Serial.print(cm);
  distance = cm;
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void setup(void) {
  Serial.begin(9600);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) 
    u8g.setColorIndex(255);     // white
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT )
    u8g.setColorIndex(3);         // max intensity
  else if ( u8g.getMode() == U8G_MODE_BW )
    u8g.setColorIndex(1);         // pixel on
  
}

void loop(void) {
  Proximity();
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(5);
}

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 18

Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, PIN, NEO_GRB + NEO_KHZ800);

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<3; i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait*0.25);
  }
 }
  
void setup() {
  strip.begin();
  strip.setBrightness(25);
  strip.show();

  // put your setup code here, to run once:
}


void loop() {
  colorWipe(strip.Color(255, 0,255),25);
  delay(1000);
}

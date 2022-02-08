#include <TFT.h>
#include <SPI.h>
#define cs 10
#define dc 9
#define rst 8


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6


Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);



TFT TFTscreen = TFT(cs, dc, rst);
int width = TFTscreen.width();
int height = TFTscreen.height();
int padding_buttons = width*0.0125;
int button_width = width*0.475;
int textBox = height*0.15;
int button_height = height*0.4;

const int number_of_buttons = 4;

int colorCode[number_of_buttons][3] = {{255, 163, 0}, {25, 0, 225}, {0, 0, 255}, {0, 255, 253}};
int rectPosition[number_of_buttons][4] = {{0, 0, 0, 0}, {0, button_height + padding_buttons*2, 0, 0}, {button_width+padding_buttons*2, 0, 0, 0}, {button_width+padding_buttons*2, button_height + padding_buttons*2, 0, 0}};




void setup() {

  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(5,INPUT_PULLUP);
  pinMode(6,OUTPUT);
  
  Serial.begin(9600);
  
  TFTscreen.begin();
  TFTscreen.setRotation(225);
  start_page();
  colorWipe(strip.Color(255,255,255),50);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
 }

void start_page() {
  
  TFTscreen.background(255, 255, 255);
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.textSize(1); 
  TFTscreen.text("Tippen Sie auf das Produkt:", 1, 1);

  for (int i=0; i<number_of_buttons; i++) {
    TFTscreen.fill(colorCode[i][0], colorCode[i][1], colorCode[i][2]);
    TFTscreen.rect(padding_buttons+rectPosition[i][0], textBox+rectPosition[i][1], button_width+rectPosition[i][2], button_height+rectPosition[i][3]);
  }
 }


void end_page() {
  TFTscreen.background(64, 255, 0);
  TFTscreen.textSize(1); 
  TFTscreen.text("Vielen Dank!", width*0.27, height/2-height/2*0.2);
  TFTscreen.text("Auf Wiedersehen!", width*0.20, height/2-height/2*0.05);
}
  
void loop() {

 int input = 5;
  if (Serial.available() > 0) {
    input = Serial.read();
  }
// replace with touchscreen input function
  
  switch (input){
    
    case 49:
      end_page();
      colorWipe(strip.Color(0, 0, 255), 50); // Bounty
      delay(5000);
      start_page();
      colorWipe(strip.Color(255,255,255),50);
      break;
      
    case 50:
      end_page();
      colorWipe(strip.Color(255, 0, 0), 50); // KiKat
      delay(5000);
      start_page();
      colorWipe(strip.Color(255,255,255),50);
      break;
      
    case 51:
      end_page();
      colorWipe(strip.Color(255, 0, 255), 50); // Snickers
      delay(5000);
      start_page();
      colorWipe(strip.Color(255,255,255),50);
      break;
      
    case 52:
      end_page();
      colorWipe(strip.Color(255, 136, 0), 50); // Twix
      delay(5000);
      start_page();
      colorWipe(strip.Color(255,255,255),50);
      break;
    
    
    }  
  }

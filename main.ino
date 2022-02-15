#include <TFT.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>



#define cs 10
#define dc 9
#define rst 8
#define PIN 6


Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
TFT TFTscreen = TFT(cs, dc, rst);

int dimensions[2] = {TFTscreen.width(), TFTscreen.height()};
int padding_buttons = dimensions[0]*0.0125;
int button_width = dimensions[0]*0.475;
int textBox = dimensions[1]*0.15;
int button_height = dimensions[1]*0.4;

const int number_of_buttons = 4;

int colorCode[number_of_buttons][3] = {{255, 163, 0}, {25, 0, 225}, {0, 0, 255}, {0, 255, 253}};
int rectPosition[number_of_buttons][4] = {{0, 0, 0, 0}, {0, button_height + padding_buttons*2, 0, 0}, {button_width+padding_buttons*2, 0, 0, 0}, {button_width+padding_buttons*2, button_height + padding_buttons*2, 0, 0}};




void setup() {
  Serial.begin(9600);

  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(5,INPUT_PULLUP);
  pinMode(6,OUTPUT);
  
  
  TFTscreen.begin();
  TFTscreen.setRotation(225);
  start_page();
  colorWipe(strip.Color(255,255,255),50);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait*0.25);
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


void item_out_page(int b, int g, int r) {
  TFTscreen.background(b, g, r);
  TFTscreen.textSize(1); 
  TFTscreen.text("Bitte warten...", width*0.26, height/2-height/2*0.15);
}

void end_page() {
  TFTscreen.background(64, 255, 0);
  TFTscreen.textSize(1); 
  TFTscreen.text("Bitte entnehmen!", width*0.21, height/2-height/2*0.2);
  TFTscreen.text("Vielen Dank!", width*0.29, height/2-height/2*0.05);
}

void item_out(int b, int g, int r) {
  
  
  item_out_page(b, g, r);
  colorWipe(strip.Color(r, g, b), 50);
  delay(5000);  //motoren
  end_page();
  delay(5000);  // rausgenommen
  start_page();
  colorWipe(strip.Color(255,255,255),50);
}


void loop() {
 int input = 0;
  if (Serial.available() > 0) {
    input = Serial.read();

    switch (input){
    
    case '1':
      item_out(255, 0, 0);
      break;
      
    case '2':
      item_out(25, 0, 225);
      break;
      
    case '3':
      item_out(255, 0, 255);
      break;
      
    case '4':
      item_out(255, 136, 0);
      break;
    
    
    }  
    
  }
  // replace with touchscreen input function
  delay(10);
  
  }

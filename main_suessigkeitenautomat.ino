#include <TFT.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define cs 10
#define dc 9
#define rst 8
#define PIN 6


int motorPins[4][2];
int speed = 1023;

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



int colorCodes[4][3] = {{255, 0, 0}, {25, 0, 225}, {255, 0, 255}, {255, 136, 0}};



int input = 0;
int inputPins[5] = [1,2,3,4,5];

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

  


  for(int i = 0; i < 5 ; i++)
    {
      pinMode(inputPins[i], INPUT);
    }


  int pin = 40;

  for(int motor_index = 0; motor_index < 4; motor_index++)
  {
      for(int direction_index = 0; direction_index < 2; direction_index++)
      {
          pinMode(pin, OUTPUT);
          motorPins[motor_index][direction_index] = pin++;
      }
  }
  
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


void item_out_page(int color[]) {
  TFTscreen.background(color[2], color[1], color[0]);
  TFTscreen.textSize(1); 
  TFTscreen.text("Bitte warten...", width*0.26, height/2-height/2*0.15);
}

void end_page() {
  TFTscreen.background(64, 255, 0);
  colorWipe(strip.Color(0, 255, 64),50);
  TFTscreen.textSize(1); 
  TFTscreen.text("Bitte entnehmen!", width*0.21, height/2-height/2*0.2);
  TFTscreen.text("Vielen Dank!", width*0.29, height/2-height/2*0.05);
}

void item_out(int x) {

  int color[3] = {};
  for (int i = 0; i <=2; i++){
    color[i] = colorCodes[x-1][i];
    Serial.println(color[i]);
  }
  
  item_out_page(color);
  colorWipe(strip.Color(color[0], color[1], color[2]), 50);
  control_motor(motorPins[x-1][0]);
  end_page();


  if(digitalRead(x) == HIGHT)
  {
    start_page();
    colorWipe(strip.Color(255,255,255),50); //was auch immer ihr wollt
  }
  
  
}


void control_motor(int motor_pin)
{
  //while(!digitalRead(inputpin))
  for(int i = 0; i < 10; i++)
  {
    analogWrite(motor_pin, speed);
    //Serial.println(motor_pin);
    delay(500);
  }
  analogWrite(motor_pin, 0);
}


void loop() {
 int input = 0;
  if (Serial.available() > 0) {
    input = Serial.read();

    switch (input){
    
    case '1':
      item_out(1);
      break;
      
    case '2':
      item_out(2);
      break;
      
    case '3':
      item_out(3);
      break;
      
    case '4':
      item_out(4);
      break;
    
    
    }  
    
  }
  // replace with touchscreen input function
  delay(10);
  
  }

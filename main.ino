#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 44
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xFF00
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define SNICKERS  0x0AF0
#define KITKAT    0xF000
#define BOUNTY    0xE0F0
#define TWIX      0xFF00



#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

#define TS_MINX 130
#define TS_MAXX 905

#define TS_MINY 75
#define TS_MAXY 930

//#define 

#include <MCUFRIEND_kbv.h>
// Adafruit_TFTLCD tft;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
MCUFRIEND_kbv tft;
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
int motorPins[4][2];
int speed = 1023;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int width = 480;
int height = 320;
int padding_buttons = width*0.0125;
int button_width = width*0.475;
int textBox = height*0.125;
int button_height = height*0.4125;

const int number_of_buttons = 4;

int rectPosition[number_of_buttons][4] = {{0, 0, 0, 0}, {0, button_height + padding_buttons*2, 0, 0}, {button_width+padding_buttons*2, 0, 0, 0}, {button_width+padding_buttons*2, button_height + padding_buttons*2, 0, 0}};



int colorCode[number_of_buttons][3] = {{255, 0, 0}, {255, 0, 255}, {0, 0, 255}, {255, 136, 0}};
int colorCodes[4] = {KITKAT, BOUNTY, SNICKERS, TWIX};

void start_page() {
    tft.fillScreen(WHITE);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.setCursor(5, 5);
    tft.println("Tippen Sie auf ein Produkt");
    
    for(int i=0; i<=3; i++){
      if (i==0){
        tft.fillRect(padding_buttons+rectPosition[i][0], textBox+rectPosition[i][1], button_width+rectPosition[i][2], button_height+rectPosition[i][3], KITKAT);
        tft.setCursor(padding_buttons+rectPosition[i][0]+55, button_height+rectPosition[i][3] - textBox+rectPosition[i][1]);
        tft.println("KitKat");
      } else if (i==1){
        tft.fillRect(padding_buttons+rectPosition[i][0], textBox+rectPosition[i][1], button_width+rectPosition[i][2], button_height+rectPosition[i][3], BOUNTY);
        tft.setCursor(padding_buttons+rectPosition[i][0]+60, button_height+rectPosition[i][3] - textBox+rectPosition[i][1]);
        tft.println("Bounty"); 
      } else if (i==2){
        tft.fillRect(padding_buttons+rectPosition[i][0], textBox+rectPosition[i][1], button_width+rectPosition[i][2], button_height+rectPosition[i][3], SNICKERS);
        tft.setCursor(padding_buttons+rectPosition[i][0]+40, button_height+rectPosition[i][3] - textBox+rectPosition[i][1]);
        tft.println("Snickers");
      } else if (i==3){
        tft.fillRect(padding_buttons+rectPosition[i][0], textBox+rectPosition[i][1], button_width+rectPosition[i][2], button_height+rectPosition[i][3], TWIX);
        tft.setCursor(padding_buttons+rectPosition[i][0]+75, button_height+rectPosition[i][3] - textBox+rectPosition[i][1]);
        tft.println("Twix");
      }
      tft.drawRect(padding_buttons+rectPosition[i][0], textBox+rectPosition[i][1], button_width+rectPosition[i][2], button_height+rectPosition[i][3], BLACK);
      

    }
}

void setup(void) {
  Serial.begin(9600);
  Serial.println("Started");
  tft.reset();  
  tft.begin(0x9486);
  tft.setRotation(225);
  tft.setTextSize(3);
  delay(10000);
  start_page(); 

  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);

  strip.begin();
  strip.setBrightness(25);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(5,INPUT_PULLUP);
  pinMode(46,OUTPUT);
  
  colorWipe(strip.Color(255,255,255),25);




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
  for(uint16_t i=0; i<60; i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait*0.25);
  }
 }

void control_motor(int motor_pin)
{
  //while(!digitalRead(inputpin))
  for(int i = 0; i < 10; i++)
  {
    analogWrite(motor_pin, speed);
    Serial.println(motor_pin);
    delay(500);
  }
  analogWrite(motor_pin, 0);
}







void end_page() {
  tft.fillScreen(GREEN);
  colorWipe(strip.Color(7, 224, 0),25);
  tft.setTextSize(4); 
  tft.setCursor(60, 110);
  tft.println("Bitte entnehmen!");
  tft.setCursor(95, 145);
  tft.println("Vielen Dank!");
}

void select_item_amount(int color){
  tft.fillScreen(colorCodes[color]);
  tft.setRotation(225);
  tft.setCursor(50, 140);
  tft.println("Anzahl");

  tft.fillRect(160, 120, 60, 60, GREEN);

  tft.drawRect(160, 120, 60, 60, BLACK);
  
  delay(10000);
}

void item_out(int x) {
  tft.begin(0x9486);
  tft.setRotation(225);
  //select_item_amount(x-1);

  tft.fillScreen(colorCodes[x-1]);
  tft.setCursor(60, 140);
  tft.setTextSize(4);
  tft.println("Bitte warten...");
  colorWipe(strip.Color(colorCode[x-1][0], colorCode[x-1][1], colorCode[x-1][2]), 25);
  Serial.println(x);
  control_motor(motorPins[x-1][0]);
  
  end_page();
  delay(5000);
  delay(1000);  // rausgenommen
  start_page();
  colorWipe(strip.Color(255,255,255),25);
}

void loop() {

  TSPoint p = ts.getPoint();
      if (p.z > 200) {
        if (p.x<829 && p.x>524 && p.y<951 && p.y>574){   
          item_out(1);
          
        } else if (p.x<829 && p.x>524 && p.y<549 && p.y>199){
          item_out(3);
        } else if (p.x<499 && p.x>209 && p.y<951 && p.y>574){
          item_out(2);
        } else if (p.x<499 && p.x>209 && p.y<549 && p.y>199){
          item_out(4);
        }
      }


    
  
  
}

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>


#define PIN 6
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xFF0000
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

#define MINPRESSURE 10
#define MAXPRESSURE 1000
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



int colorCode[number_of_buttons][3] = {{0, 0, 255}, {255, 0, 0}, {255, 136, 0}, {255, 0, 255}};
int colorCodes[4] = {KITKAT, SNICKERS, BOUNTY, TWIX};

void start_page() {
  
  tft.fillScreen(WHITE);
  tft.setRotation(225);
  
  tft.setCursor(5, 5);
  tft.setTextSize(3); 
  tft.setTextColor(BLACK);
  tft.println("Tippen Sie auf ein Produkt");

  for (int i=0; i<number_of_buttons; i++) {
    tft.fillRect(padding_buttons+rectPosition[i][0], textBox+rectPosition[i][1], button_width+rectPosition[i][2], button_height+rectPosition[i][3], colorCodes[i]);
    tft.drawRect(padding_buttons+rectPosition[i][0], textBox+rectPosition[i][1], button_width+rectPosition[i][2], button_height+rectPosition[i][3], BLACK);
  }

}

void setup(void) {
  Serial.begin(9600);
  tft.reset();  
  tft.begin(0x9486);
  delay(10000);
  start_page(); 

  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);

  strip.begin();
  strip.setBrightness(25);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(5,INPUT_PULLUP);
  pinMode(6,OUTPUT);
  
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
  for(uint16_t i=0; i<strip.numPixels(); i++) {
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

/*void loop(void) {
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  if (p.z > 500){
    if (p.x < 501 && p.x > 209 && p.y < 551 && p.y > 199){
    item_out(1);
    }  
    else if (p.x < 501 && p.x > 209 && p.y < 950 && p.y > 569){
      item_out(2);
    }
  }
  item_out(1);
}
*/





void item_out_page() { //int color[]
  tft.fillScreen(GREEN); // color[2], color[1], color[0]
  tft.setTextSize(3); 
  tft.println("Bitte warten..."); // width*0.26, height/2-height/2*0.15
  }


void end_page() {
  tft.fillScreen(GREEN);
  colorWipe(strip.Color(0, 255, 64),25);
  tft.setTextSize(4); 
  tft.setCursor(60, 110);
  tft.println("Bitte entnehmen!"); // width*0.21, height/2-height/2*0.2
  tft.setCursor(95, 145);
  tft.println("Vielen Dank!"); // width*0.29, height/2-height/2*0.05
}


void item_out(int x) {

  
  tft.begin(0x9486);
  tft.fillScreen(colorCodes[x-1]);
  tft.setRotation(225);
  tft.setCursor(60, 140);
  tft.setTextSize(4);
  tft.println("Bitte warten...");
  delay(2000);
  colorWipe(strip.Color(colorCode[x][0], colorCode[x][1], colorCode[x][2]), 25);
  
  Serial.println(motorPins[x-1][0]);
  control_motor(motorPins[x-1][0]);
  
  end_page();
  delay(5000);
  delay(1000);  // rausgenommen
  start_page();
  colorWipe(strip.Color(255,255,255),25);
   
  
  
}

void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);

  TSPoint p = ts.getPoint();
  if (p.z > 200) {
    
    if (p.x<829 && p.x>524 && p.y<951 && p.y>574){   
      
      item_out(1);
      
    } else if (p.x<829 && p.x>524 && p.y<549 && p.y>199){
      item_out(2);
    } else if (p.x<499 && p.x>209 && p.y<951 && p.y>574){
      item_out(3);
    } else if (p.x<499 && p.x>209 && p.y<549 && p.y>199){
      item_out(4);
    }
  }
  
}

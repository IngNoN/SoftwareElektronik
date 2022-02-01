//Motor Pins
const int motorPin11 = 46;
const int motorPin12 = 47;
const int motorPin21 = 48;
const int motorPin22 = 49;
const int motorPin31 = 50;
const int motorPin32 = 51;
const int motorPin41 = 52;
const int motorPin42 = 53;

int inputPin1 = 22;
int inputPin2 = 23;
int inputPin3 = 24;
int inputPin4 = 25;

int speed = 1023;

void setup(){
//Set pins as outputs
pinMode(motorPin11, OUTPUT);
pinMode(motorPin12, OUTPUT);
pinMode(motorPin21, OUTPUT);
pinMode(motorPin22, OUTPUT);
pinMode(motorPin31, OUTPUT);
pinMode(motorPin32, OUTPUT);
pinMode(motorPin41, OUTPUT);
pinMode(motorPin42, OUTPUT);

pinMode(inputPin1, INPUT_PULLUP);
pinMode(inputPin2, INPUT_PULLUP);
pinMode(inputPin3, INPUT_PULLUP);
pinMode(inputPin4, INPUT_PULLUP);

Serial.begin(9600);

}
int motorNum = 0;

void loop()
{


  //Pullup Widerstand ist standardmäßig HIGH
  //Abfrage mit Verneinung
  if (!digitalRead(inputPin1))
  {
    motorNum = 1;  
  }
  else if(!digitalRead(inputPin2))
  {
    motorNum = 2;  
  }
  else if(!digitalRead(inputPin3))
  {
    motorNum = 3;  
  }
  else if(!digitalRead(inputPin4))
  {
    motorNum = 4;  
  }

  Serial.println(digitalRead(inputPin1));
  
  switch(motorNum)
  { 
    case 1:
      analogWrite(motorPin11, speed);
      delay(3000);
      motorNum = 0;
      break;
     case 2:
      analogWrite(motorPin21, speed);
      delay(3000);
      motorNum = 0;
      break;
     case 3:
      analogWrite(motorPin31, speed);
      delay(3000);
      motorNum = 0;
      break;
     case 4:
      analogWrite(motorPin41, speed);
      delay(3000);
      motorNum = 0;
      break;
  }

}

//Motor Pins
int motorPins[4][2];
int speed = 1023;

void control_motor(int motor_pin)
{
  int get_sweet = 1;
  switch(get_sweet)
  {
    case 1:
      analogWrite(motor_pin, speed);
      get_sweet = 2;
    case 2:
      //int sweets_ejected = digitalRead(inputpin);
      delay(3000);
      if (true)
      {
        get_sweet = 3;  
      }
      else
        {
          break;
        }
    case 3:
      analogWrite(motor_pin, 0);
  }
}

void setup(){

int pin = 46;

  for(int motor_index = 0; motor_index < 4; motor_index++)
  {
      for(int direction_index = 0; direction_index < 2; direction_index++)
      {
          pinMode(pin, OUTPUT);
          motorPins[motor_index][direction_index] = pin++;
          
      }
  }

Serial.begin(9600);
}

void loop()
{
  int input = 4;
  if (Serial.available() > 0) {
    input = Serial.read();
  }

   int motor_index = input - '1';
   control_motor(motorPins[motor_index][0]);
}

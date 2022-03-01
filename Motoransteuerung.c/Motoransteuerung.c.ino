//Motor Pins
int motorPins[4][2];
int speed = 1023;

inputPins[5] = [23,25,27,29,31];


void waitForSensor (int inputPin)
{
    while(true)
      {
        if(digitalRead(inputPin) == HIGH)
        {
            break;
        }
      }
        return;
}

void control_motor(int motor_pin)
{
  analogWrite(motor_pin, speed);
  waitForSensor(motor_pin);
  analogWrite(motor_pin, 0);
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
  int input = 0;
  if (Serial.available() > 0) {
    input = Serial.read();
  }
  int motor_index = input - '1';
  //Serial.println(motorPins[motor_index][0]);
  if (motor_index <= 3 && motor_index >= 0)
  {
    control_motor(motorPins[motor_index][0]);
  }
}

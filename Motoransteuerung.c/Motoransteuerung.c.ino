//Motor Pins
int motorPins[4][2];
int speed = 1023;

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

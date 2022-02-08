//Motor Pins
int motorPins[4][2];
int speed = 1023;

void control_motor(int motor_pin)
{
  analogWrite(motor_pin, speed);
  while (true)
  {
    if (true)//(inputpin) //sensor signal von Benedikt - true durch inputpin ersetzenbei implementierung der Sensoren
    {
      delay(4000); //zu entfernen bei implementierung der Sensoren
      analogWrite(motor_pin, 0);
      break;  
    }
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
  int input = 5;
  if (Serial.available() > 0) {
    input = Serial.read();
  }
  
  switch(input)
  { 
    case '1':
      control_motor(motorPins[0][0]);
      break;
     case '2':
      control_motor(motorPins[1][0]);
      break;
     case '3':
      control_motor(motorPins[2][0]);
      break;
     case '4':
      control_motor(motorPins[3][0]);
      break;
  }
}

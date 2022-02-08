//Motor Pins

int motorPins[4][2];

int pin = 46;



int speed = 1023;

void setup(){

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
      analogWrite(motorPins[0][0], speed);
      delay(3000);
      analogWrite(motorPins[0][0], 0);
      break;
     case '2':
      analogWrite(motorPins[1][0], speed);
      delay(3000);
      analogWrite(motorPins[1][0], 0);
      break;
     case '3':
      analogWrite(motorPins[2][0], speed);
      delay(3000);
      analogWrite(motorPins[2][0], 0);
      break;
     case '4':
      analogWrite(motorPins[3][0], speed);
      delay(3000);
      analogWrite(motorPins[3][0], 0);
      break;
  }
}

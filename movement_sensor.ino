inputPins[5] = [1,2,3,4,5];
int input = 0;
void setup() 
{
    Serial.begin(9600);
    for(int i = 0; i < 5 ; i++)
    {
      pinMode(inputPins[i], INPUT);
    }

}

void loop() 
{

  if(digitalRead(inputPIN) == HIGHT)
  {
    //was auch immer ihr wollt

  }


}
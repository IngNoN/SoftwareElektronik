
inputPins[5] = [23,25,27,29,31];

void setup8()
{
  for(int i = 0; i < 5 ; i++)
    {
      pinMode(inputPins[i], INPUT);
    }
}
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
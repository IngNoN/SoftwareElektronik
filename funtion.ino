void waitForSensor (int inputPin)
{
    while(true)
      {
        if(digitalRead(inputPin) == HIGHT)
        {
            break;
        }
      }
        return;


}
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
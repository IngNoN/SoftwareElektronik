const int inputPIN = 3;
const int ledpin = 4;
int input = 0;
volatile byte state = LOW;
void setup() 
{
    Serial.begin(9600);
    pinMode(ledpin, OUTPUT);
  pinMode(inputPIN, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(inputPIN), light, HIGH);
	//attachInterrupt(digitalPinToInterrupt(inputPIN), shadow, LOW);
}

void light()
{
  digitalWrite(ledpin, HIGH);
  delay(1000);
  digitalWrite(ledpin, LOW);
  Serial.println(5);
  //delay(1000);
  //state = !state; 
}

/*void shadow()
{
  digitalWrite(ledpin, LOW);
  delay(1000);
  //digitalWrite(ledpin, LOW);
  Serial.println(5);
  //delay(1000);
  //state = !state; 
}*/

void loop() 
{
  

delay(100);}
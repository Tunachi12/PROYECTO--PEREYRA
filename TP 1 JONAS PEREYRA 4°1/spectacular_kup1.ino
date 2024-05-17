void setup()
{
  pinMode(7, OUTPUT);
 
 
  pinMode(3, OUTPUT);

 
  pinMode(2, OUTPUT); 
  pinMode(4, OUTPUT);
 
 
  pinMode(9, OUTPUT);  
  pinMode(6, OUTPUT);
 
}

void loop()
{
  analogWrite(3, 255);
  delay(1000);
  analogWrite(3, 0);
  delay(1000);
  digitalWrite(7, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(7, LOW);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  delay(1000);
  digitalWrite(7, HIGH);
  analogWrite(9, 99);
  analogWrite(6, 99);
  delay(1000);
  digitalWrite(7, LOW);
  analogWrite(9, 0);
  analogWrite(6, 0);
  delay(1000);
 
}

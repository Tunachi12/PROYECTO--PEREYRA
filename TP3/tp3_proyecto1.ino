void setup() 
{
  pinMode(A3, INPUT_PULLUP);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(8, OUTPUT);  
  Serial.begin(9600); 
}

void loop()
{
  int Potenciomentro1 = analogRead(A1);
  int Potenciomentro2 = analogRead(A2);
  int Potenciomentro3 = analogRead(A3);
  int pot1 = map(Potenciomentro1, 0, 1023, 0, 255);
  int pot2 = map(Potenciomentro2, 0, 1023, 0, 255);
  int pot3 = map(Potenciomentro3, 0, 1023, 0, 255);

  if(analogRead(A0) == LOW)
  {
    Serial.println("Tiene 5 s para configurar el color del led....");
    analogWrite(10, 0);
    analogWrite(9, 0);
    analogWrite(8, 0);
    delay(5000);

    Potenciomentro1 = analogRead(A1);
    Potenciomentro2 = analogRead(A2);
    Potenciomentro3 = analogRead(A3);
    pot1 = map(Potenciomentro1, 0, 1023, 0, 255);
    pot2 = map(Potenciomentro2, 0, 1023, 0, 255);
    pot3 = map(Potenciomentro3, 0, 1023, 0, 255);

    Serial.print("El led esta usando esta configuración de colores RGB:(");
    Serial.print(pot1);
    Serial.print("; ");
    Serial.print(pot2);
    Serial.print("; ");
    Serial.print(pot3);
    Serial.println(")");

    analogWrite(10, pot3); 
    analogWrite(9, pot2); 
    analogWrite(8, pot1); 
    delay(5000);
    
  }else{
    analogWrite(10, 0);
    analogWrite(9, 0);
    analogWrite(8, 0);
  }
}
      
          
      
      
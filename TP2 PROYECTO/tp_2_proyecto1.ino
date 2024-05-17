// C++ code
//
void setup()
{
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(A1, INPUT);
 pinMode(2, INPUT_PULLUP);
}
void loop()
{
 if( digitalRead(2) == LOW )
 {
 digitalWrite(10, LOW);
 digitalWrite(11, LOW);
 digitalWrite(12, LOW);  
 }
 else{
   
 int fornite = analogRead(A1);
 
 int Maincraft = map( fornite , 0,1023,200,1500);
 
 digitalWrite(10, HIGH);
 digitalWrite(11, HIGH);
 digitalWrite(12, LOW);
 delay( Maincraft );
 digitalWrite(10, LOW);
 digitalWrite(11, HIGH);
 digitalWrite(12, HIGH);
 delay( Maincraft );
 digitalWrite(10, HIGH);
 digitalWrite(11, LOW);
 digitalWrite(12, LOW);
 delay( Maincraft );
 }
}

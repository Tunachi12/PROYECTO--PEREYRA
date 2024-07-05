// C++ code
//
#define POTENCIOMETRO A5
#define PIEZO 2
#define TRIG 4
#define ECO 5
#define  MSG(a,b) Serial.print(a); Serial.println(b);Serial.print(""); 
void setup()
{
  pinMode(POTENCIOMETRO, INPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECO, INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite( TRIG , LOW );
  delayMicroseconds(2);
  digitalWrite( TRIG , HIGH );
  delayMicroseconds(10);
  digitalWrite( TRIG , LOW );
 
  float tiempo = pulseIn( ECO , HIGH);
  float distancia = tiempo / 57.6 ;
  int x = analogRead(POTENCIOMETRO);

  int movil = map(distancia, 1, 330, 20, 330);
  int fijo = map(x, 0, 1023, 50, 200);

  int velocidad;
  if (movil > fijo){
     velocidad = movil - fijo;
  }else{
     velocidad = fijo - movil;
  }
 
  delay(velocidad);
  digitalWrite(PIEZO,HIGH);
  delay(velocidad);
  digitalWrite(PIEZO,LOW);
  MSG("fijo: ",fijo);
  MSG("movil: ",movil);
  MSG("velocidad: ",velocidad);
  
}
                
    
  
  

  
  
  
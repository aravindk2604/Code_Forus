#define t 2
byte sw;
void setup() {

  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(3, INPUT_PULLUP);
}

void loop() {

  sw = digitalRead(3);  
  
  if(!sw)
  {
    digitalWrite(7,HIGH);
  }
  else
  { 
    digitalWrite(7,LOW);
  }
  
  digitalWrite(8,HIGH);
  delay(t);
  digitalWrite(8,LOW);
  delay(t);
  
  /*  digitalWrite(8,HIGH);
   delay(t);
   digitalWrite(8,LOW);
   delay(t);
   //////////////////////////////////// 
   digitalWrite(7,LOW);
   
   digitalWrite(8,HIGH);
   delay(300);
   digitalWrite(8,LOW);
   delay(300);
   digitalWrite(8,HIGH);
   delay(300);
   digitalWrite(8,LOW);
   delay(300); */


}


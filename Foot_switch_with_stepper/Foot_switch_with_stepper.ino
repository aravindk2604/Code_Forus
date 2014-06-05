#define swI1 2
#define swI2 3
#define swF1 4
#define swF2 5
#define swT 6

#define t 1
#define M0 7 // smart mode pin 0
#define M1 8 // smart mode pin 1
#define STEP 9 // Steps pin for the motor
#define DIR 10 // Direction for the step
//#define SLEEP 11 //sleep mode enable and disable
#define ENABLE 12

//boolean prev_Iminus = true;
boolean Iminus = true;
//boolean prev_Iplus = true;
boolean Iplus = true;

boolean prev_Fminus = true;
boolean Fminus = true;
boolean prev_Fplus = true;
boolean Fplus = true;

boolean prev_Trigger = true;
boolean Trigger = true;

int count = 30; // previously 450
void setup() 
{
  pinMode(swI1,INPUT_PULLUP); // Illumination -
  pinMode(swI2,INPUT_PULLUP); // Illumination +
  pinMode(swF1,INPUT_PULLUP); // Focus+
  pinMode(swF2,INPUT_PULLUP); // Focus-
  pinMode(swT,INPUT_PULLUP); // Trigger

  pinMode(M0,OUTPUT); 
  pinMode(M1,OUTPUT); 
  pinMode(STEP,OUTPUT);
  pinMode(DIR,OUTPUT); 
//  pinMode(SLEEP,OUTPUT);
  pinMode(ENABLE,OUTPUT);

  pinMode(13, OUTPUT);

  /************************  Stepper Motor initial position setup *******************/
  digitalWrite(ENABLE,HIGH);

//  digitalWrite(SLEEP,HIGH); // wake up from sleep mode
//  digitalWrite(DIR, LOW);
//  for(int i=0; i<100; i++)
//  {
//    digitalWrite(STEP,HIGH);
//    delay(t);
//    digitalWrite(STEP,LOW);
//    delay(t);
//  }
 // digitalWrite(SLEEP,LOW); // go back to sleep mode

  digitalWrite(ENABLE,LOW);

  digitalWrite(M0,HIGH);
  digitalWrite(M1,HIGH);
}

void loop() 
{
  //  digitalWrite(SLEEP,HIGH); // wake up from sleep mode

  digitalWrite(STEP,LOW);
  digitalWrite(13, LOW);
  Iminus = digitalRead(swI1);
  Iplus = digitalRead(swI2);
  Fminus = digitalRead(swF2);
  Fplus = digitalRead(swF1);
  Trigger = digitalRead(swT);

  if(Iminus == false)// && prev_Iminus == true )
  {
    delay(50);
    //Serial.println("Illumination -");
    digitalWrite(13, HIGH);
    delay(100);
  }

  if(Iplus == false)// && prev_Iplus == true )
  {
    delay(50);
    //Serial.println("Illumination +");
    digitalWrite(13, HIGH);
    delay(100);
  }

  if(Fplus == false)// && prev_Fplus == true )
  {
//    if(prev_Fplus == true)
//        digitalWrite(SLEEP,HIGH); // wake up from sleep mode
    // delay(50);
    // Serial.println("Focus +");
    //delay(100);
    
      digitalWrite(ENABLE,LOW);

    
    digitalWrite(DIR, HIGH);
    if(count >= 30 && count < 800) // previously 450 and 665
    {
      //   for(int repeat=0; repeat<10; repeat++)
      //   {
      digitalWrite(STEP,HIGH);
      delay(t);
      digitalWrite(STEP,LOW);
      delay(t); 
      //   }

      if(count!= 800)
      {
        count++;
      }
    }
   //digitalWrite(SLEEP,LOW); // go back to sleep mode
//delay(100);

  digitalWrite(ENABLE,HIGH);

  }
//else
//    if(prev_Fplus == false); // wake up from sleep mode)
//        digitalWrite(SLEEP,LOW); // go back to sleep mode
  
  if(Fminus == false) //&& prev_Fminus == true )
  {
    // delay(50);
    // Serial.println("Focus -");
//    if(prev_Fminus == true)
//        digitalWrite(SLEEP,HIGH); // wake up from sleep mode
   // delay(100);
   
     digitalWrite(ENABLE,LOW);
   
    digitalWrite(DIR, LOW);
    if(count > 30 && count <= 800)
    {
      //  for(int repeat=0; repeat<10; repeat++)
      // {
      digitalWrite(STEP,HIGH);
      delay(t);
      digitalWrite(STEP,LOW);
      delay(t); 
      //}

      if(count!=30)
      {
        count--;
      }
    }

  digitalWrite(ENABLE,HIGH);
     
//delay(100);

  }
//  else
//      if(prev_Fminus == false)
//        digitalWrite(SLEEP,LOW); // go back to sleep mode

  if(Trigger == false && prev_Trigger == true )
  {
    delay(120);
    if(Trigger == false && prev_Trigger == true )
    {
      digitalWrite(13,HIGH);
      delay(100);
      // Serial.println("Trigggrrr");
    }
  }
  prev_Trigger = Trigger;
//    digitalWrite(SLEEP,LOW); // go back to sleep mode

//prev_Fplus = Fplus;
//prev_Fminus = Fminus; 
}






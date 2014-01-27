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

//boolean prev_Iminus = true;
boolean Iminus = true;
//boolean prev_Iplus = true;
boolean Iplus = true;

//boolean prev_Fminus = true;
boolean Fminus = true;
//boolean prev_Fplus = true;
boolean Fplus = true;

boolean prev_Trigger = true;
boolean Trigger = true;

int count = 450;
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

  pinMode(13, OUTPUT);

  /************************  Stepper Motor initial position setup *******************/
  digitalWrite(DIR, LOW);
  for(int i=0; i<100; i++)
  {
    digitalWrite(STEP,HIGH);
    delay(t);
    digitalWrite(STEP,LOW);
    delay(t);
  }

  digitalWrite(M0,HIGH);
  digitalWrite(M1,LOW);
}

void loop() 
{
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
   // delay(50);
    // Serial.println("Focus +");
    digitalWrite(DIR, HIGH);
    if(count >= 450 && count < 665)
    {
      for(int repeat=0; repeat<150; repeat++)
      {
        digitalWrite(STEP,HIGH);
        delay(t);
        digitalWrite(STEP,LOW);
        delay(t); 
      }

      if(count!=665)
      {
        count++;
      }
    }

  }

  if(Fminus == false) //&& prev_Fminus == true )
  {
   // delay(50);
    // Serial.println("Focus -");
    digitalWrite(DIR, LOW);
    if(count > 450 && count <= 665)
    {
      for(int repeat=0; repeat<150; repeat++)
      {
        digitalWrite(STEP,HIGH);
        delay(t);
        digitalWrite(STEP,LOW);
        delay(t); 
      }

      if(count!= 450)
      {
        count--;
      }
    }


  }

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
}




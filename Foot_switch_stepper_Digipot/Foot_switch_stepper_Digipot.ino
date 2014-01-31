#include <EEPROM.h>

#include <MCP4561.h>
#include <Wire.h>

/****************************** Defining Foot switch pins ***********************/
#define swI1 2
#define swI2 3
#define swF1 4
#define swF2 5
#define swT 6

/***************************** Defining Stepper Driver pins *********************/

#define t 1  // delay time between energising the stepper motor
#define M0 7 // smart mode pin 0
#define M1 8 // smart mode pin 1
#define STEP 9 // Steps pin for the motor
#define DIR 10 // Direction for the step
//#define SLEEP 11 //sleep mode enable and disable
#define ENABLE 12  //enable pin

/**************************** Foot switch variables ****************************/
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
int count = 450;

/************************************* Digipot class instance ************************/
MCP4561 digiPot(47); // object for MCP4661 digipot
int value = 0;
const int addr = 2;
void setup() 
{
  Wire.begin(); //join i2c bus as master

  pinMode(swI1,INPUT_PULLUP); // Illumination -
  pinMode(swI2,INPUT_PULLUP); // Illumination +
  pinMode(swF1,INPUT_PULLUP); // Focus+
  pinMode(swF2,INPUT_PULLUP); // Focus-
  pinMode(swT,INPUT_PULLUP); // Trigger

  /******************************** Stepper Driver pins ************************/
  pinMode(M0,OUTPUT); 
  pinMode(M1,OUTPUT); 
  pinMode(STEP,OUTPUT);
  pinMode(DIR,OUTPUT); 
  // pinMode(SLEEP,OUTPUT);
  pinMode(ENABLE,OUTPUT);

  pinMode(13, OUTPUT); // LED

  /**************************** Pullup pins for MCP4661 ****************************/
  pinMode(18,INPUT_PULLUP);          //A1 pulled up to higher potential
  pinMode(19,INPUT_PULLUP);          //A2 pulled up to higher potential (slave address purpose)
  value = EEPROM.read(addr);         // Reading the previous state of the DigiPot

  /************************ Stepper Motor initial position setup *******************/
  digitalWrite(ENABLE,HIGH);

  digitalWrite(DIR, LOW);

  for(int i=0; i<100; i++)
  {
    digitalWrite(STEP,HIGH);
    delay(t);
    digitalWrite(STEP,LOW);
    delay(t);
  }

  digitalWrite(ENABLE,LOW);

  digitalWrite(M0,LOW);
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
    value = EEPROM.read(addr);
    if(value < 256)
    {
      value -= 1;
      EEPROM.write(addr, value);
      pot(value);
    }

  }

  if(Iplus == false)// && prev_Iplus == true )
  {
    delay(50);
    value = EEPROM.read(addr);

    if(value > 1)
    {
      value += 1;
      EEPROM.write(addr,value);
      pot(value);

    }


  }

  if(Fplus == false)// && prev_Fplus == true )
  {
    digitalWrite(ENABLE,LOW);
    digitalWrite(DIR, HIGH);
    if(count >= 450 && count < 665)
    {
      digitalWrite(STEP,HIGH);
      delay(t);
      digitalWrite(STEP,LOW);
      delay(t); 

      if(count!= 665)
      {
        count++;
      }
    }

    digitalWrite(ENABLE,HIGH);

  }
  if(Fminus == false) //&& prev_Fminus == true )
  {
    digitalWrite(ENABLE,LOW);

    digitalWrite(DIR, LOW);
    if(count > 450 && count <= 665)
    {
      digitalWrite(STEP,HIGH);
      delay(t);
      digitalWrite(STEP,LOW);
      delay(t); 

      if(count!=450)
      {
        count--;
      }
    }

    digitalWrite(ENABLE,HIGH);  
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

/************************************************* Digipot value setting function ************************************************************/

int pot(int setOutput)
{
  digiPot.write(2,setOutput);            //Writing to Non-volatile register that reflects on the volatile wiper register during POR
  digiPot.write(4,setOutput);            //Setting TCON register bits ---> Wiper 1 is used
  digiPot.write(1,setOutput);             // this is the example method, all the rest is formatting, this method will return 1 if the write was succesful, 0 otherwise

}







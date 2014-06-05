#include <EEPROM.h>
#include "MCP4561.h"
#include <Wire.h>

/****************************** Defining Foot switch pins ***********************/
#define swI1 12   // I-  PB4
#define swI2 4  // I+  PB5
#define swF1 8  // F-  PD4
#define swF2 9  //F+  PD6
#define swT 6    //T   PD7

/**************************** LT3464 *******************************************/

#define nBOOSTenable 7

/**************************** LiquidLens ***************************************/

char ack, d = '0';
String data;
#define LiquidLens 0b0100011

/**************************** LDO **********************************************/

#define LDOenable 5

/**************************** Foot switch variables ****************************/
boolean Iminus = true;
boolean Iplus = true;

boolean Fminus = true;
boolean Fplus = true;

boolean prev_Trigger = true;
boolean Trigger = true;
int count = 5;

/************************************* Digipot class instance ************************/
MCP4561 digiPot(47); // object for MCP4661 digipot
byte value = 126;
int addr = 3;

void setup()
{
  Serial.begin(19200);
  /*********************************************** Setting the clock ***************************************************/

  CLKSEL0 |= (1 << EXTE);
  while (!(CLKSTA & (1 << EXTON))) {
  }
  CLKSEL0 |= (1 << CLKS);
  CLKSEL0 &= ~(1 << RCE);

  CLKSEL1 = 0x0F;

  CLKPR = 0x80; // enable prescalar change
  CLKPR = 0x00; // prescalar set to zero

  // DISABLE JTAG - take control of F port
  MCUCR = _BV(JTD);
  MCUCR = _BV(JTD);

  TWCR |= _BV(TWEN);   // enabling I2C on PORT D

  /*********************************************************************************************************************/


  Wire.begin(); //join i2c bus as master

  pinMode(swI1, INPUT_PULLUP); // Illumination -
  pinMode(swI2, INPUT_PULLUP); // Illumination +
  pinMode(swF1, INPUT_PULLUP); // Focus+
  pinMode(swF2, INPUT_PULLUP); // Focus-
  pinMode(swT, INPUT_PULLUP); // Trigger

  pinMode(LDOenable, OUTPUT);
  pinMode(nBOOSTenable, OUTPUT);

  /******************************** Stepper Driver pins ************************/

  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(SLEEP, OUTPUT);
  pinMode(nENABLE, OUTPUT);

  value = EEPROM.read(addr);         // Reading the previous state of the DigiPot

  digitalWrite(SLEEP, HIGH); // wake up from sleep mode
  digitalWrite(M0, LOW);     // Mode 0 pin for Stepper motor steps assignment
  digitalWrite(M1, HIGH);   // Mode 1 pin for Stepper motor steps assignment

  digitalWrite(nBOOSTenable, LOW);    //to enable Boost converter IC
  digitalWrite(LDOenable, HIGH);     // to enable LDO

}

void loop()
{

  digitalWrite(STEP, LOW);   // ensuring the motor is OFF

  Iminus = digitalRead(swI1);
  Iplus = digitalRead(swI2);
  Fminus = digitalRead(swF2);
  Fplus = digitalRead(swF1);
  Trigger = digitalRead(swT);

  /**************************************** Illumination Control *************************************************/

  if (Iminus == false)
  {
    value = EEPROM.read(addr);
    if (value > 0)
    {
      value -= 2;
    }
    pot(value);
    EEPROM.write(addr, value);
    int  add = digiPot.read(addr);
  }

  if (Iplus == false)
  {
    value = EEPROM.read(addr);
    if (value < 254)
    {
      value += 2;
    }
    pot(value);
    EEPROM.write(addr, value);
    int  add = digiPot.read(addr);
  }


  /******************************************************** Focus Control *******************************************/

  if (Fplus == false)
  {
    if (voltValue > 0)
    {
      Wire.beginTransmission(0b0100011);    // 7-bit address as per datasheet
      ack = Wire.write(voltValue);  //What to write in the above register
      Wire.endTransmission();
    }

    if (voltValue != 0)
      voltValue--;
  }

  if (Fminus == false)
  {
    if (voltValue < 255)
    {
      Wire.beginTransmission(0b0100011);    // 7-bit address as per datasheet
      ack = Wire.write(voltValue);  //What to write in the above register
      Wire.endTransmission();
    }

    if (voltValue < 255)
      voltValue++;
  }

  /**************************************** Trigger ****************************************/

  if (Trigger == false && prev_Trigger == true )
  {
    delay(200);
    if (Trigger == false && prev_Trigger == true )
    {
      digitalWrite(nBOOSTenable, HIGH);
      delay(70);
    }
  }
  digitalWrite(nBOOSTenable, LOW);
  prev_Trigger = Trigger;
}


/************************************************* Digipot value setting function ************************************************************/

int pot(byte setOutput)
{
  digiPot.write(0, setOutput);           //Writing to Non-volatile register that reflects on the volatile wiper register during POR
  digiPot.write(2, setOutput);            // this is the example method, all the rest is formatting, this method will return 1 if the write was succesful, 0 otherwise
}








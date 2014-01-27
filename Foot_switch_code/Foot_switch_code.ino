
#define swI1 2
#define swI2 3
#define swF1 4
#define swF2 5
#define swT 6

boolean stateI1 = false;
boolean stateI2 = false;
boolean stateF1 = false;
boolean stateF2 = false;
boolean stateT = false;


void setup() 
{
  pinMode(swI1,INPUT_PULLUP); // Illumination -
  pinMode(swI2,INPUT_PULLUP); // Illumination +
  pinMode(swF1,INPUT_PULLUP); // Focus+
  pinMode(swF2,INPUT_PULLUP); // Focus-
  pinMode(swT,INPUT_PULLUP); // Trigger
  //pinMode(7,INPUT);        // common
}

void loop() 
{
   
  if (digitalRead(swI1) == LOW && stateI1 == false)
  {  // switch is pressed - pullup keeps pin high normally
    delay(120);                        // delay to debounce switch
  if (digitalRead(swI1) == LOW && stateI1 == false)
  {  
    Serial.println("Illumination -"); // indicate
    stateI1 = !stateI1;                // toggle running variable
  }
  }
  stateI1 = !stateI1;
  if (digitalRead(swI2) == LOW && stateI2 == false)
  {  // switch is pressed - pullup keeps pin high normally
    delay(120);                        // delay to debounce switch
  if (digitalRead(swI2) == LOW && stateI2 == false)
  {  
    Serial.println("Illumination +"); // indicate
    stateI2 = !stateI2;                // toggle running variable
  }
  }
  stateI2 = !stateI2;
  if (digitalRead(swF1) == LOW && stateF1 == false)
  {  // switch is pressed - pullup keeps pin high normally
    delay(120);                        // delay to debounce switch
  if (digitalRead(swF1) == LOW && stateF1 == false)
  {  
    Serial.println("Focus +"); // indicate
    stateF1 = !stateF1;                // toggle running variable
  }
  }
  stateF1 = !stateF1;
  if (digitalRead(swF2) == LOW && stateF2 == false)
  {  // switch is pressed - pullup keeps pin high normally
    delay(120);       // delay to debounce switch
    if (digitalRead(swF2) == LOW && stateF2 == false)
  {
    Serial.println("Focus -"); // indicate
    stateF2 = !stateF2;                // toggle running variable
  }
  }
  stateF2 = !stateF2;
  if (digitalRead(swT) == LOW && stateT == false)
  {  // switch is pressed - pullup keeps pin high normally
    delay(120);                        // delay to debounce switch
      if (digitalRead(swT) == LOW && stateT == false)
      {
    Serial.println("Triggggggrrrrr"); // indicate
    stateT = !stateT;                // toggle running variable
      }
  }
  stateT = !stateT;

}



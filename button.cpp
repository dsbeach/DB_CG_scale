#include "DB_CG_scale-master.h"

void Button::init()
{
//button pin modes
  pinMode(B1PIN,INPUT_PULLUP);
  pinMode(B2PIN,INPUT_PULLUP);
  pinMode(B3PIN,INPUT_PULLUP);  
}

int Button::readButton()
{
  static bool b1down = false;
  static bool b2down = false;
  static bool b3down = false;
  static unsigned int lastPress;

  if ((millis() - lastPress) < 1000) return 0; // attempt to avoid false press due to bouncing switches
  
  if (b1down == false && digitalRead(B1PIN) == 0){b1down = true;}
  else{if (b1down == true && digitalRead(B1PIN) == 1){b1down = false;lastPress = millis(); return BUTTON1;}} 
    
  //b2
  if (b2down == false && digitalRead(B2PIN) == 0){b2down = true;}
  else{if (b2down == true && digitalRead(B2PIN) == 1){b2down = false;lastPress = millis();return BUTTON2;}} 

   //b3
  if (b3down == false && digitalRead(B3PIN) == 0){b3down = true;}
  else{if (b3down == true && digitalRead(B3PIN) == 1){b3down = false;lastPress = millis();return BUTTON3;}} 

  // no button pressed
  return 0;
}

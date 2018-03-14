#include "DB_CG_scale.h"

#define DEBUG true

I2C_LCD lcd;
HX711 frontCell(FRONT_CELL_DOUT, FRONT_CELL_SCK);  
HX711 rearCell(REAR_CELL_DOUT, REAR_CELL_SCK); 
int handlerIndex;
MainHandler mainHandler;
RawHandler rawHandler;
CalibrateHandler calibrateHandler;
OptionHandler optionHandler;
EepromValues eepromValues;



void setup() {

  if (DEBUG)
  {
    Serial.begin(115200);
    Serial.println("DEBUG is active!");
  }

  lcd.init();
  Button::init();
  
  lcd.printrow(0,"DB_CG_Scale v0.0");
  lcd.printrow(1, "Zero front...");
  
  eepromValues = Eeprom::getValues();
  frontCell.set_scale(eepromValues.frontScale);
  rearCell.set_scale(eepromValues.rearScale);

  handlerIndex = MAIN_ID;

  frontCell.tare(CELL_SAMPLE_ITERATIONS);
  lcd.printrow(1, "Zero rear...");
  rearCell.tare(CELL_SAMPLE_ITERATIONS);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (handlerIndex)
  {
    case MAIN_ID:
      handlerIndex = mainHandler.handle(Button::readButton(), lcd, &frontCell, &rearCell, &eepromValues);
      break;

    case CALIBRATE_ID:
      handlerIndex = calibrateHandler.handle(Button::readButton(), lcd, &frontCell, &rearCell, &eepromValues);
      break;

    case RAW_ID:
      handlerIndex = rawHandler.handle(Button::readButton(), lcd, &frontCell, &rearCell, &eepromValues);
      break;

    case OPTION_ID:
      handlerIndex = optionHandler.handle(Button::readButton(), lcd, &frontCell, &rearCell, &eepromValues);
      break;

  }
}






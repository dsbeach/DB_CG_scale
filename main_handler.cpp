#include "DB_CG_scale.h"

int MainHandler::handle(int button, I2C_LCD lcd, HX711 *frontCell, HX711 *rearCell, EepromValues *eepromValues) {

  static MovingAverage avgFront(CELL_SAMPLE_ITERATIONS);
  static MovingAverage avgRear(CELL_SAMPLE_ITERATIONS);
  static unsigned long lastSwitch = millis();
  static bool showGrams = true;

  if (status == WAITING)
  {
    lcd.printrow(0, "Main is working");
    lcd.printrow(1, "");
    status = WORKING;
  }
  switch (button)
  {
    case BUTTON1:
      status = WAITING;
      return CALIBRATE_ID;
      break;

    case BUTTON2:
      status = WAITING;
      return RAW_ID;
      break;

    case BUTTON3:
      status = WAITING;
      return OPTION_ID;
      break;
  }

  // read sensors (average to whole grams)
  avgFront.update(frontCell->get_units(1));
  avgRear.update(rearCell->get_units(1));
  float frontUnits = roundf(avgFront.get());
  float rearUnits = roundf(avgRear.get());
  float totalWeight = frontUnits + rearUnits;
  float totalForce = (frontUnits * eepromValues->pegDistance)  + (rearUnits *  (eepromValues->pegDistance + eepromValues->spanDistance));
  float cg = totalForce / totalWeight;

  // grams or ounces?
  switch (eepromValues->gramsOuncesOption) {
    case 0:
      showGrams = true;
      break;
    case 1:
      showGrams = false;
      break;
    case 2:
      unsigned long now = millis();
      if ((now - lastSwitch) > 5000ul) {
        showGrams = !showGrams;
        lastSwitch = now;
      }
      break;
  }
  
  if (showGrams == true) // showing grams
  {
    lcd.printrow(0, "Weight: " + String(totalWeight,0) + " g");
  } else {
    lcd.printrow(0, "Weight: " + String((totalWeight * GRAMS_OUNCES_FACTOR), 1) + " oz");
  }
  lcd.printrow(1, "CG: " + String(cg, 1) + " mm");

  return MAIN_ID;
}


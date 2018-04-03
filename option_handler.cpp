#include "DB_CG_scale-master.h"

void changeValue(int button,float *value, float adj)
{
  switch (button)
  {
    case BUTTON2:
      *value += adj;
      break;
    case BUTTON3:
      *value -= adj;
      break;
  }
}

int OptionHandler::handle(int button, I2C_LCD *lcd, HX711 *frontCell, HX711 *rearCell, EepromValues *eepromValues) {
  static int step = 0;
    
  if (status == WAITING)
  {
    status = WORKING;
    step = 0;
  }
  switch (step) {
    case 0:
      lcd->printrow(0, "Change options?");
      lcd->printrow(1, "Btn 1 = Yes");
      if ((button == BUTTON2) || (button == BUTTON3)) {
          status = WAITING;
          return MAIN_ID;
      }
      break;
    case 1:
      lcd->printrow(0, "Span Dist. 1's");
      lcd->printrow(1, String(eepromValues->spanDistance,1));
      changeValue(button, &eepromValues->spanDistance, 1.0);
      break;
    case 2:
      lcd->printrow(0, "Span Dist. .1's");
      lcd->printrow(1, String(eepromValues->spanDistance,1));
      changeValue(button, &eepromValues->spanDistance, 0.1);
      break;
    case 3:
      lcd->printrow(0, "Peg Dist. 1's");
      lcd->printrow(1, String(eepromValues->pegDistance,1));
      changeValue(button, &eepromValues->pegDistance, 1.0);
      break;
    case 4:
      lcd->printrow(0, "Peg Dist. .1's");
      lcd->printrow(1, String(eepromValues->pegDistance,1));
      changeValue(button, &eepromValues->pegDistance, 0.1);
      break;
    // set units of measure
    case 5:
      lcd->printrow(0, "Btn 1 g Btn 2 oz");
      lcd->printrow(1, "Btn 3 = both");
      switch (button)
      {
        case BUTTON1:
          eepromValues->gramsOuncesOption = 0;
          step++;
          break;
        case BUTTON2:
          eepromValues->gramsOuncesOption = 1;
          step++;
          break;
        case BUTTON3:
          eepromValues->gramsOuncesOption = 2;
          step++;
          break;
      }
      break;
      
    default:
      lcd->printrow(0, "Saving values ...");
      lcd->printrow(1, "");
      Eeprom::putValues(*eepromValues);
      delay(500);
      status = WAITING;
      return MAIN_ID;
      break;
  }

  switch (button) {
    case BUTTON1:
      step++;
      break;
  }
  return OPTION_ID;
}



#include "DB_CG_scale-master.h"

int CalibrateHandler::handle(int button, I2C_LCD *lcd, HX711 *frontCell, HX711 *rearCell, EepromValues *eepromValues) {
  static int step = 0;
  static float calibrationWeight;
  static long rawEmpty;
  static long rawWeighted;
    
  if (status == WAITING)
  {
    status = WORKING;
    step = 0;
  }
  switch (step) {
    case 0:
      lcd->printrow(0, "Calibrate?");
      lcd->printrow(1, "Btn 1 = Yes");
      if ((button == BUTTON2) || (button == BUTTON3)) {
          status = WAITING;
          return MAIN_ID;
      }
      break;
    case 1:
      lcd->printrow(0, "Target wt (100s)");
      lcd->printrow(1, String(eepromValues->calibrationWeight,0));
      switch (button)
      {
        case BUTTON2:
          eepromValues->calibrationWeight += 100;
          break;
        case BUTTON3:
          eepromValues->calibrationWeight -= 100;
          break;
      }
      break;
    case 2:
      lcd->printrow(0, "Target wt (10s)");
      lcd->printrow(1, String(eepromValues->calibrationWeight,0));
      switch (button)
      {
        case BUTTON2:
          eepromValues->calibrationWeight += 10;
          break;
        case BUTTON3:
          eepromValues->calibrationWeight -= 10;
          break;
      }
      break;
    case 3:
      lcd->printrow(0, "Target wt (1s)");
      lcd->printrow(1, String(eepromValues->calibrationWeight,0));
      switch (button)
      {
        case BUTTON2:
          eepromValues->calibrationWeight += 1;
          break;
        case BUTTON3:
          eepromValues->calibrationWeight -= 1;
          break;
      }
      break;
    case 4:
      lcd->printrow(0, "F. cradle empty?");
      lcd->printrow(1, "Btn 1 = Ready");
      if (button == BUTTON1) {
        lcd->printrow(1, "Zeroing front...");
        rawEmpty = frontCell->read_average(CELL_SAMPLE_ITERATIONS * 4);
        Serial.println("Front rawEmpty= " + String(rawEmpty));
      }
      break;
    case 5:
      lcd->printrow(0, "F. weighted?");
      lcd->printrow(1, "Btn 1 = Ready");
      if (button == BUTTON1) {
        lcd->printrow(0, "Reading front");
        lcd->printrow(1, "...");
        rawWeighted = frontCell->read_average(CELL_SAMPLE_ITERATIONS * 4);
        Serial.println("Front rawWeighted= " + String(rawWeighted));
        eepromValues->frontScale = (rawWeighted - rawEmpty) / eepromValues->calibrationWeight;
        Serial.println("Front scale: " + String(eepromValues->frontScale, 4));
        frontCell->set_scale(eepromValues->frontScale);
      }
      break;
    case 6:
      lcd->printrow(0, "R. cradle empty?");
      lcd->printrow(1, "Btn 1 = Ready");
      if (button == BUTTON1) {
        lcd->printrow(1, "Zeroing rear...");
        rawEmpty = rearCell->read_average(CELL_SAMPLE_ITERATIONS * 4);
        Serial.println("Rear rawEmpty= " + String(rawEmpty));
      }
      break;
    case 7:
      lcd->printrow(0, "R. weighted?");
      lcd->printrow(1, "Btn 1 = Ready");
      if (button == BUTTON1) {
        lcd->printrow(0, "Reading rear");
        lcd->printrow(1, "...");
        rawWeighted = rearCell->read_average(CELL_SAMPLE_ITERATIONS * 4);
        Serial.println("Rear rawWeighted= " + String(rawWeighted));
        eepromValues->rearScale = (rawWeighted - rawEmpty) / eepromValues->calibrationWeight;
        Serial.println("Rear scale: " + String(eepromValues->rearScale, 4));
        rearCell->set_scale(eepromValues->rearScale);
      }
      break;
    default:
      lcd->printrow(0, "Saving values ...");
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
  return CALIBRATE_ID;
}



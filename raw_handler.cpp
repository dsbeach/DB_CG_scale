#include "DB_CG_scale.h"

int RawHandler::handle(int button, I2C_LCD lcd, HX711 *frontCell, HX711 *rearCell, EepromValues *eepromValues) {

  static MovingAverage avgFront(CELL_SAMPLE_ITERATIONS);
  static MovingAverage avgRear(CELL_SAMPLE_ITERATIONS);
  
  if (status == WAITING)
  {
    lcd.printrow(0, "Raw is working");
    lcd.printrow(1, "");
    status = WORKING;
  }
  if (button == BUTTON1)
  {
    status = WAITING;
    return MAIN_ID;
  } else {
    if (button == BUTTON3)
    {
      lcd.printrow(0, "Setting tare");
      
      lcd.printrow(1, "Front cell");
      frontCell->tare(CELL_SAMPLE_ITERATIONS);
      avgFront.reset(frontCell->get_units(1));
      
      lcd.printrow(1, "Rear cell");
      rearCell->tare(CELL_SAMPLE_ITERATIONS);
      avgRear.reset(rearCell->get_units(1));
    }
  }

  double front = frontCell->get_units(1);
  avgFront.update(front);
  double rear = rearCell->get_units(1);
  avgRear.update(rear);
  
  lcd.printrow(0,String(front,2) + " " + String(rear,2));
  lcd.printrow(1,String((int)(avgFront.get() + 0.5f)) + "    " + String((int)(avgRear.get() + 0.5f)));

  return RAW_ID;
}


#ifndef CALIBRATE_HANDLER_H
#define CALIBRATE_HANDLER_H

#include "DB_CG_scale-master.h"

class CalibrateHandler {
  public:
    CalibrateHandler() { status = WAITING; }
    int handle(int button, I2C_LCD *lcd, HX711 *frontCell, HX711 *rear_cell, EepromValues *eepromValues);
  private:
    Status status;
};

#endif


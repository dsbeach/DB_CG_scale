#ifndef RAW_HANDLER_H
#define RAW_HANDLER_H

#include "DB_CG_scale.h"

class RawHandler {
  public:
    RawHandler() { status = WAITING; }
    int handle(int button, I2C_LCD lcd, HX711 *frontCell, HX711 *rear_cell, EepromValues *eepromValues);
  private:
    Status status;
};

#endif

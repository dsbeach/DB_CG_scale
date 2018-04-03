#ifndef MAIN_HANDLER_H
#define MAIN_HANDLER_H

#include "DB_CG_scale-master.h"

#define GRAMS_OUNCES_FACTOR 0.035274f

class MainHandler {
  public:
    MainHandler() { status = WAITING; };
    int handle(int button, I2C_LCD *lcd, HX711 *frontCell, HX711 *rear_cell, EepromValues *eepromValues);
    Status status;
};

#endif

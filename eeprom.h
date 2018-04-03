#ifndef EEPROM_H
#define EEPROM_H

#include "DB_CG_scale-master.h"

#define FRONT_SCALE_ADDRESS 0
#define REAR_SCALE_ADDRESS 4
#define CALIBRATION_WEIGHT_ADDRESS 8
#define SPAN_DISTANCE_ADDRESS 12
#define PEG_DISTANCE_ADDRESS 16
#define GRAMS_OUNCES_OPTION_ADDRESS 20

struct EepromValues {
  float frontScale;
  float rearScale;
  float calibrationWeight;
  float spanDistance; // distance between pivot points
  float pegDistance; // leading edge peg to first pivot point
  uint32_t gramsOuncesOption;
};

#include "DB_CG_scale-master.h"

class Eeprom {
  private:
    Eeprom() {};
  public:
    static EepromValues getValues();
    static void putValues(EepromValues eepromValues);
};

#endif


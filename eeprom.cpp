#include "DB_CG_scale.h"

EepromValues Eeprom::getValues()
{
  EepromValues eepromValues;

  //reset EEPROM if button down
  if (digitalRead(B3PIN) == 0)
    {
    for (int i = 0;i<EEPROM.length();i++) EEPROM.write(i, 0xff);  
    eepromValues.frontScale = 1000.0;
    eepromValues.rearScale = 1000.0;
    eepromValues.calibrationWeight = 1000.0;
    eepromValues.spanDistance = 120.0;
    eepromValues.pegDistance = 30.0;
    eepromValues.gramsOuncesOption = 0;
    putValues(eepromValues);
    }
    else //read values from eeprom
    {
    EEPROM.get(FRONT_SCALE_ADDRESS,eepromValues.frontScale);
    EEPROM.get(REAR_SCALE_ADDRESS,eepromValues.rearScale);
    EEPROM.get(CALIBRATION_WEIGHT_ADDRESS, eepromValues.calibrationWeight);  
    EEPROM.get(SPAN_DISTANCE_ADDRESS, eepromValues.spanDistance);
    EEPROM.get(PEG_DISTANCE_ADDRESS, eepromValues.pegDistance);
    EEPROM.get(GRAMS_OUNCES_OPTION_ADDRESS, eepromValues.gramsOuncesOption);
    }

    if (isnan(eepromValues.frontScale) || (eepromValues.frontScale == 0.0)) { eepromValues.frontScale = 1000.0; }
    if (isnan(eepromValues.rearScale) || (eepromValues.rearScale == 0.0)) { eepromValues.rearScale = 1000.0; }
    if (isnan(eepromValues.calibrationWeight) || (eepromValues.calibrationWeight == 0.0)) { eepromValues.calibrationWeight = 1000.0; }
    if (isnan(eepromValues.spanDistance) || (eepromValues.spanDistance == 0.0)) { eepromValues.spanDistance = 120.0; }
    if (isnan(eepromValues.pegDistance) || (eepromValues.pegDistance == 0.0)) { eepromValues.pegDistance = 30.0; }
    if (isnan(eepromValues.gramsOuncesOption)) { eepromValues.gramsOuncesOption = 0; }
    
    Serial.println("Front scale:" + String(eepromValues.frontScale,2));
    Serial.println("Rear scale:" + String(eepromValues.rearScale,2));
    Serial.println("Cal. weight:" + String(eepromValues.calibrationWeight));
    Serial.println("Span distance:" + String(eepromValues.spanDistance,2));
    Serial.println("Peg distance:" + String(eepromValues.pegDistance,2));
    Serial.print("Grams/ounces option:");
    Serial.println(eepromValues.gramsOuncesOption, DEC);
  
  return eepromValues;
}

void Eeprom::putValues(EepromValues eepromValues)
{
    EEPROM.put(FRONT_SCALE_ADDRESS,eepromValues.frontScale);
    EEPROM.put(REAR_SCALE_ADDRESS,eepromValues.rearScale);
    EEPROM.put(CALIBRATION_WEIGHT_ADDRESS, eepromValues.calibrationWeight);
    EEPROM.put(SPAN_DISTANCE_ADDRESS, eepromValues.spanDistance);
    EEPROM.put(PEG_DISTANCE_ADDRESS, eepromValues.pegDistance);
    EEPROM.put(GRAMS_OUNCES_OPTION_ADDRESS, eepromValues.gramsOuncesOption);
}


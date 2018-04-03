#ifndef DB_CG_SCALE_H
#define DB_CG_SCALE_H

#include <Wire.h>
#include <Arduino.h>
#include <HX711.h>
#include <MovingAverage.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

enum Status { WORKING, WAITING };

#include "i2c_lcd.h"
#include "button.h"
#include "eeprom.h"
#include "main_handler.h"
#include "raw_handler.h"
#include "calibrate_handler.h"
#include "option_handler.h"

#define MAIN_ID 0
#define CALIBRATE_ID 1
#define RAW_ID 2
#define OPTION_ID 3

// load cells
#define CELL_SAMPLE_ITERATIONS 25
#define FRONT_CELL_DOUT A2
#define FRONT_CELL_SCK A3
#define REAR_CELL_DOUT A0
#define REAR_CELL_SCK A1

#endif

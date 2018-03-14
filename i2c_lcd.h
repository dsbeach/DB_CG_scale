#ifndef I2C_LCD_H
#define I2C_LCD_H

#include "DB_CG_scale.h"

//display
#define I2C_ADDR    0x3f
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define LCD_COLS 16
#define LCD_ROWS 2

class I2C_LCD :  LiquidCrystal_I2C {
  public:
    I2C_LCD() : LiquidCrystal_I2C(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin) {};
    void init();
    void printrow(int row, String text);
  private:
};

#endif


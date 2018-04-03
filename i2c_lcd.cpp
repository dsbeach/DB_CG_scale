#include "DB_CG_scale-master.h"

void I2C_LCD::init()
{
  begin(LCD_COLS, LCD_ROWS);
  home();
  setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  setBacklight(HIGH);
}

void I2C_LCD::printrow(int row, String text)
{
  static String buffer[LCD_ROWS] = {"", ""}; // holds the last displayed values

  if (buffer[row] != text)
  {
    buffer[row] = text;
    setCursor(0, row);
    print(text);
    for (int x = text.length(); x < LCD_COLS; x++)
    {
      print(" ");
    }
  }
  
}


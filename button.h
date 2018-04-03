#ifndef BUTTON_H
#define BUTTON_H

#include "DB_CG_scale-master.h"

// button pins
#define B1PIN 2
#define B2PIN 3
#define B3PIN 4

// button constants
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3


class Button
{
  private:
    Button() {};
  public:
    static void init();
    static int readButton();
};

#endif

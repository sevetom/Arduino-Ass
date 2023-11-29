#ifndef __LCD_DISPLAY__
#define __LCD_DISPLAY__

#define MAX_LENGTH 16
#define MAX_LINES 2

#include <LiquidCrystal_I2C.h> 
#include <Arduino.h>
#include <string.h>

/*
* Wiring: SDA => A4, SCL => A5
*/
class LcdDisplay{
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, MAX_LENGTH, MAX_LINES);
    bool printed;
public:
    void init();
    void printLong(const char* text);
    void print(const char* text, int line, int row);
    void clear();
    bool getPrintStatus();
};

#endif
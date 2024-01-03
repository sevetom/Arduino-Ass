#ifndef __LCD_DISPLAY__
#define __LCD_DISPLAY__

#define MAX_LENGTH 16
#define MAX_LINES 2

#include <LiquidCrystal_I2C.h> 
#include <Arduino.h>
#include <string.h>

/*
* Class that handles a LCD display
*/
class LcdDisplay{
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, MAX_LENGTH, MAX_LINES);
public:
    /**
     * Initialize the LCD display
     * Wiring: SDA => A4, SCL => A5
    */
    LcdDisplay();
    /**
     * Print a text on multiple lines on the LCD display
     * Clears the screen before printing
     * @param text The text to print
    */
    void printLong(const char* text);
    /**
     * Print a text on a specific line and row on the LCD display
     * @param text The text to print
     * @param row The row to print the text on
     * @param line The line to print the text on
    */
    void printText(const char* text, int row, int line);
    /**
     * Print two texts on two lines on the LCD display
     * Clears the screen before printing
     * @param text1 The text to print on the first line
     * @param text2 The text to print on the second line
    */
    void printTwoLines(const char* text1, const char* text2);
    /**
     * Clears the LCD display
    */
    void clear();
};

#endif
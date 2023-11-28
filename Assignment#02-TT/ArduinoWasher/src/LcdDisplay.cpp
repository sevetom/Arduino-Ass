#include "LcdDisplay.h"

void LcdDisplay::init() {
  this->lcd.init();
  this->lcd.backlight();
  this->lcd.clear();
  this->printed = false;
}

void LcdDisplay::print(const char* text) {
  this->lcd.setCursor(0, 0);
  this->lcd.print(text);
  this->printed = true;
}

void LcdDisplay::print(const char* text, int row) {
  this->lcd.setCursor(row, 0);
  this->lcd.print(text);
  this->printed = true;
}

void LcdDisplay::print(const char* text, int row, int line) {
  this->lcd.setCursor(row, line);
  this->lcd.print(text);
  this->printed = true;
}

void LcdDisplay::clear() {
  this->lcd.clear();
  this->printed = false;
}

bool LcdDisplay::getPrintStatus() {
  return this->printed;
}
#include "LcdDisplay.h"

void LcdDisplay::init() {
  this->lcd.init();
  this->lcd.backlight();
  this->lcd.clear();
  this->printed = false;
}

void LcdDisplay::printLong(const char* text) {
  char* token = strtok((char*)text, "\n");
  if (token != NULL) {
    this->lcd.setCursor(0, 0);
    this->lcd.print(token);
  }
  token = strtok(NULL, "\n");
  if (token != NULL) {
    this->lcd.setCursor(0, 1);
    this->lcd.print(token);
  }
  this->printed = true;
}

void LcdDisplay::print(const char* text, int line, int row) {
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
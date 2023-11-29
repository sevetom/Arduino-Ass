#include "LcdDisplay.h"

LcdDisplay::LcdDisplay() {
  this->lcd.init();
  this->lcd.backlight();
  this->printed = false;
}

void LcdDisplay::printLong(const char* text) {
  this->lcd.clear();
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

void LcdDisplay::printText(const char* text, int line, int row) {
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
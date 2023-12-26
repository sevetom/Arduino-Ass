#include "LcdDisplay.h"

LcdDisplay::LcdDisplay() {
  this->lcd.init();
  this->lcd.backlight();
}

void LcdDisplay::printLong(const char* text) {
  char textCopy[strlen(text) + 1];
  strcpy(textCopy, text);

  this->lcd.clear();
  
  char* token = strtok(textCopy, "\n");
  if (token != NULL) {
    this->lcd.setCursor(0, 0);
    this->lcd.print(token);
  }

  token = strtok(NULL, "\n");
  if (token != NULL) {
    this->lcd.setCursor(0, 1);
    this->lcd.print(token);
  }
}

void LcdDisplay::printText(const char* text, int row, int line) {
  this->lcd.setCursor(row, line);
  this->lcd.print(text);
}

void LcdDisplay::printTwoLines(const char* text1, const char* text2) {
  this->lcd.clear();
  this->lcd.setCursor(0, 0);
  this->lcd.print(text1);
  this->lcd.setCursor(0, 1);
  this->lcd.print(text2);
}

void LcdDisplay::clear() {
  this->lcd.clear();
}
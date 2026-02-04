#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  // put your setup code here, to run once:
  lcd.init(); //Init the board
  lcd.backlight(); // turn on the backlight
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(5,0);
  lcd.print("Arduino");
  lcd.setCursor(7,1);
  lcd.print("I2C");
  delay(2000);
  lcd.clear();
  delay(1000);
}

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
	// initialize the LCD
	lcd.begin();
	lcd.print(" Hello World (^__^)");
  lcd.setCursor(0, 1);
  lcd.print("Velleman for makers");
  lcd.setCursor(0, 2);
  lcd.print("         At        ");
  lcd.setCursor(0, 3);
  lcd.print("   www.velleman.eu");
}

void loop()
{
	// Do nothing here...
}

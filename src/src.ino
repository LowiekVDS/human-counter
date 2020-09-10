#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "Counter.h"

// PIR pins
#define PIR_1_INPUT 6
#define PIR_2_INPUT 7

// Buttons
#define START_BTN 8
#define STOP_BTN 9
#define RS_BTN 10

// Global Counter object
Counter counter;

//Global LCD object
LiquidCrystal_I2C lcd(0x27, 20, 4);

// state values

#define STATE_ACTIVE 1
#define STATE_IDLE 0

bool PIR1State = false;
bool PIR2State = false;
bool resetBtnState = false;
bool startBtnState = false;
bool stopBtnState = false;
int globalState = STATE_IDLE;

// Others

#define DEBOUNCE_MS 50
#define SLOWDOWN_MS 5

void updateLcd();

void setup() {
  // Set up PIR sensors
  pinMode(PIR_1_INPUT, INPUT);
  pinMode(PIR_2_INPUT, INPUT);

  // Set up buttons
  pinMode(START_BTN, INPUT_PULLUP);
  pinMode(STOP_BTN, INPUT_PULLUP);
  pinMode(RS_BTN, INPUT_PULLUP);

  counter.reset();
  lcd.begin();
  updateLcd();

  Serial.begin(115200);
  Serial.println("Setup finished");
}

void loop() {

  if (globalState == STATE_ACTIVE) {
    // Handlers
    if (digitalRead(PIR_1_INPUT) && !PIR1State) {
      PIR1State = true;
      Serial.println("PIR 1 detected movement. Incrementing counter...");
      counter.increase();
      updateLcd();
      delay(DEBOUNCE_MS);
    } else {
      PIR1State = digitalRead(PIR_1_INPUT);
    }

    if (digitalRead(PIR_2_INPUT) && !PIR2State) {
      PIR2State = true;
      Serial.println("PIR 2 detected movement. Decreasing counter...");
      counter.decrease();
      updateLcd();
      delay(DEBOUNCE_MS);
    } else {
      PIR2State = digitalRead(PIR_2_INPUT);
    }
  }

  if (digitalRead(STOP_BTN) == 0) {
    globalState = STATE_IDLE;
    updateLcd();
    Serial.println("Stop button was pressed");
    delay(DEBOUNCE_MS);
    while (digitalRead(STOP_BTN) == 0) {}
  }

  if (digitalRead(START_BTN) == 0) {
    globalState = STATE_ACTIVE;
    updateLcd();
    Serial.println("Start button was pressed");
    delay(DEBOUNCE_MS);
    while (digitalRead(START_BTN) == 0) {}
  }

  if (digitalRead(RS_BTN) == 0) {
    counter.reset();
    updateLcd();
    Serial.println("Reset button was pressed");
    delay(DEBOUNCE_MS);
    while (digitalRead(RS_BTN) == 0) {}
  }
  delay(SLOWDOWN_MS);
}

void updateLcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("#People: ");
  lcd.print(counter.getCounter());
  lcd.setCursor(0, 2);
  lcd.print("State: ");
  if (globalState == STATE_ACTIVE) {
    lcd.print("Active");
  } else if (globalState == STATE_IDLE) {
    lcd.print("Idle");
  } else {
    lcd.print("Unknown");
  }
}

#include "ChessClock.h"
#include "ChessClockGlobals.h"

void setup() {
  Serial.begin(115200);
  display1_init(); 
  display2_init();

  // Setting pin modes for various buttons 
  pinMode(PLAYER_BTN_1, INPUT);
  pinMode(PLAYER_BTN_2, INPUT);
  pinMode(MODE_BTN, INPUT);

  attachInterrupt(digitalPinToInterrupt(PLAYER_BTN_1), player2Playing, FALLING);
  attachInterrupt(digitalPinToInterrupt(PLAYER_BTN_2), player1Playing, FALLING); 
  pinMode(INCREMENT_BTN, INPUT);
  pinMode(DECREMENT_BTN, INPUT);

  display1_on(NONE);
  display2_on(NONE);
  set_display1_time();
}

void loop() {
  if(should_timer_1_be_on == true) {
    should_timer_2_be_on = false;
    timer1_on();
  }
  if(should_timer_2_be_on == true) {
    should_timer_1_be_on = false;
    timer2_on();
  }
}

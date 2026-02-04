#ifndef CHESS_CLOCK_GLOBALS_H
#define CHESS_CLOCK_GLOBALS_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "ChessClock.h"

extern Adafruit_SSD1306 display1;
extern Adafruit_SSD1306 display2;

extern volatile int hours_1;
extern volatile int mins_1;
extern volatile int secs_1;

extern int increment_1_min;
extern int increment_1_sec;
extern int increment_2_min;
extern int increment_2_sec;

extern volatile int hours_2;
extern volatile int mins_2;
extern volatile int secs_2;

extern char buffer1[15];
extern char buffer2[15];
extern char buffer3[15];
extern char buffer4[15];

extern int initial_state;
extern int mode_counter;

extern volatile bool should_timer_1_be_on;
extern volatile bool should_timer_2_be_on;

extern volatile int flag;

#endif

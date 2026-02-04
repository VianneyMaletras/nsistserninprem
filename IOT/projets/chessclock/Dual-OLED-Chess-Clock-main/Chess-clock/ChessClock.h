#ifndef CHESS_CLOCK_H
#define CHESS_CLOCK_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1  // Reset pin not used
#define SCREEN_1_ADDRESS 0x3C // First OLED
#define SCREEN_2_ADDRESS 0x3D // Second OLED

#define MODE_BTN      35
#define INCREMENT_BTN 14
#define DECREMENT_BTN 27
#define PLAYER_BTN_1  32
#define PLAYER_BTN_2  33

enum TimeField { NONE, HOURS, MINUTES, SECONDS };

// Function declarations
void display1_init(void);
void display2_init(void);
void display1_on(TimeField highlight = NONE);
void display2_on(TimeField highlight = NONE);
void display1_increment_on(TimeField highlight);
void display2_increment_on(TimeField highlight);
void display1_off(void);
void display2_off(void);
void timer1_on(void);
void timer2_on(void);
void set_display1_time(void);
void IRAM_ATTR player1Playing();
void IRAM_ATTR player2Playing();

#endif

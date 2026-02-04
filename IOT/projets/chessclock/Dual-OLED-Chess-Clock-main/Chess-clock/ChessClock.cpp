#include "ChessClock.h"
#include "ChessClockGlobals.h"

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile int hours_1 = 0;
volatile int mins_1  = 10;
volatile int secs_1  = 0;

int increment_1_min = 0;
int increment_1_sec = 5;
int increment_2_min = 0;
int increment_2_sec = 5; 

volatile int hours_2 = 0;
volatile int mins_2  = 10;
volatile int secs_2  = 0;

char buffer1[15];
char buffer2[15];
char buffer3[15];
char buffer4[15];

int initial_state = 0;
int mode_counter = 0;

volatile bool should_timer_1_be_on = false;
volatile bool should_timer_2_be_on = false;

volatile int flag = 0;

void IRAM_ATTR player2Playing() {
  if(flag == 0) {
    should_timer_2_be_on = true;
    should_timer_1_be_on = false;
  }
  else {
    should_timer_2_be_on = false;
    should_timer_1_be_on = true;
  }
}

void IRAM_ATTR player1Playing() {
  if(flag == 0) {
    should_timer_2_be_on = false;
    should_timer_1_be_on = true;
  }
  else {
    should_timer_2_be_on = true;
    should_timer_1_be_on = false;
  }
}

void display1_init(void) {
  if (!display1.begin(SSD1306_SWITCHCAPVCC, SCREEN_1_ADDRESS)) {
    Serial.println(F("SSD1306 display 1 allocation failed"));
    for (;;);
  }
}

void display2_init(void) {
  if (!display2.begin(SSD1306_SWITCHCAPVCC, SCREEN_2_ADDRESS)) {
    Serial.println(F("SSD1306 display 2 allocation failed"));
    for (;;);
  }
}

void display1_on(TimeField highlight) {
  display1.clearDisplay();
  display1.setTextSize(3);
  display1.setTextColor(WHITE);
  display1.setCursor(0, 30);
  
  sprintf(buffer1, "%d:%02d:%02d", hours_1, mins_1, secs_1);
  display1.println(buffer1); 

  // HEADING
  display1.setTextSize(1);
  display1.setCursor(45, 5);
  display1.println("TIMER 1");

  // UNDERLINE
  if (highlight != NONE) {
    int underlineY = 60; // bottom Y of text line
    int xStart = 0;
    int xEnd = 0;

    switch (highlight) {
      case HOURS:
        xStart = 0;
        xEnd = 30;  // Width of hours part at size 3
        break;
      case MINUTES:
        xStart = 44;
        xEnd = 75;
        break;
      case SECONDS:
        xStart = 88;
        xEnd = 123;
        break;
    }
    display1.drawLine(xStart, underlineY, xEnd, underlineY, WHITE);
  }

  display1.display();
}

void display2_on(TimeField highlight) {
  display2.clearDisplay();
  display2.setTextSize(3);
  display2.setTextColor(WHITE);
  display2.setCursor(0, 30);
  
  sprintf(buffer2, "%d:%02d:%02d", hours_2, mins_2, secs_2);
  display2.println(buffer2);
  
  // HEADING
  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(45, 5);
  display2.println("TIMER 2");
  
  if (highlight != NONE) {
    int underlineY = 60; // bottom Y of text line
    int xStart = 0;
    int xEnd = 0;

    switch (highlight) {
      case HOURS:
        xStart = 0;
        xEnd = 30;  // Width of hours part at size 3
        break;
      case MINUTES:
        xStart = 44;
        xEnd = 75;
        break;
      case SECONDS:
        xStart = 88;
        xEnd = 123;
        break;
    }
    display2.drawLine(xStart, underlineY, xEnd, underlineY, WHITE);
  }

  display2.display();
}

void display1_increment_on(TimeField highlight) {
  display1.clearDisplay();
  display1.setTextSize(3);
  display1.setTextColor(WHITE);
  display1.setCursor(0, 30);
  
  sprintf(buffer3, "X:%02d:%02d", increment_1_min, increment_1_sec);
  display1.println(buffer3); 
  
  // HEADING
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(45, 5);
  display1.println("INCREMENT");

  if (highlight != NONE) {
    int underlineY = 60; // bottom Y of text line
    int xStart = 0;
    int xEnd = 0;

    switch (highlight) {
      case HOURS:
        xStart = 0;
        xEnd = 30;  // Width of hours part at size 3
        break;
      case MINUTES:
        xStart = 44;
        xEnd = 75;
        break;
      case SECONDS:
        xStart = 88;
        xEnd = 123;
        break;
    }
    display1.drawLine(xStart, underlineY, xEnd, underlineY, WHITE);
  }

  display1.display();
}

void display2_increment_on(TimeField highlight) {
  display2.clearDisplay();
  display2.setTextSize(3);
  display2.setTextColor(WHITE);
  display2.setCursor(0, 30);

  sprintf(buffer4, "X:%02d:%02d", increment_2_min, increment_2_sec);
  display2.println(buffer4);
  
  // HEADING
  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(45, 5);
  display2.println("INCREMENT");

  if (highlight != NONE) {
    int underlineY = 60; // bottom Y of text line
    int xStart = 0;
    int xEnd = 0;

    switch (highlight) {
      case HOURS:
        xStart = 0;
        xEnd = 30;  // Width of hours part at size 3
        break;
      case MINUTES:
        xStart = 44;
        xEnd = 75;
        break;
      case SECONDS:
        xStart = 88;
        xEnd = 123;
        break;
    }
    display2.drawLine(xStart, underlineY, xEnd, underlineY, WHITE);
  }

  display2.display();
}

void display1_off(void) {
  display1.clearDisplay();
  display1.display();
}

void display2_off(void) {
  display2.clearDisplay();
  display2.display();
}

#include "ChessClock.h"
#include "ChessClockGlobals.h"

void timer1_on(void) {
  if(should_timer_1_be_on == true) {
    while (hours_1 > 0 || mins_1 > 0 || secs_1 >= 0) {
      display1_on(NONE);
      delay(1000);
      secs_1--;

      if (secs_1 < 0) {
        if (mins_1 > 0) {
          mins_1--;
          secs_1 = 59;
        } else if (hours_1 > 0) {
          hours_1--;
          mins_1 = 59;
          secs_1 = 59;
        }
      }
      
      if(should_timer_1_be_on == true)
        continue;
      else
        break;
    } 
  }

  if(should_timer_1_be_on == false) {
    secs_1 += increment_1_sec;
    if (secs_1 > 59) {
      mins_1 += secs_1 / 59;
      secs_1 = (secs_1 % 59);
    }
    mins_1 += increment_1_min;
    if (mins_1 > 59) {
      hours_1 += mins_1 / 59;
      mins_1 = (mins_1 % 59);
    }
    display1_on(NONE);
    return;
  }
}

void timer2_on(void) {
  if(should_timer_2_be_on == true) {
    while (hours_2 > 0 || mins_2 > 0 || secs_2 >= 0) {
      display2_on(NONE);
      delay(1000);
      secs_2--;

      if (secs_2 < 0) {
        if (mins_2 > 0) {
          mins_2--;
          secs_2 = 59;
        } else if (hours_2 > 0) {
          hours_2--;
          mins_2 = 59;
          secs_2 = 59;
        }
      }
      
      if(should_timer_2_be_on == true)
        continue;
      else
        break;
    } 
  }

  if(should_timer_2_be_on == false) {
    secs_2 += increment_2_sec;
    if (secs_2 >= 60) {
      mins_2 += secs_2 / 60;
      secs_2 = (secs_2 % 60) + 1;
    }
    mins_2 += increment_2_min;
    if (mins_2 >= 60) {
      hours_2 += mins_2 / 60;
      mins_2 = (mins_2 % 60) + 1;
    }
    display2_on(NONE);
    return;
  }
}

void set_display1_time(void) {
  while(true) {
    if(digitalRead(MODE_BTN) == HIGH) {
      delay(500);
      mode_counter++;
    }

    // HOURS INCREMENT AND DECREMENT
    if(mode_counter == 1) { 
      display1_on(HOURS);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        hours_1++; 
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(hours_1 != 0) {
          delay(500);
          hours_1--;
        }
      }
    }
    
    // MINUTES INCREMENT DECREMENT 
    if(mode_counter == 2) {
      display1_on(MINUTES);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        mins_1++;
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(mins_1 != 0) {
          delay(500);
          mins_1--;
        }
      }
    }
    
    // SET seconds for timer 1
    if(mode_counter == 3) {
      display1_on(SECONDS);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        secs_1++;
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(secs_1 != 0) {
          delay(500);
          secs_1--;
        }
      }
    }

    // Ability to set increment of minutes 
    if(mode_counter == 4) {
      display1_increment_on(MINUTES);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        increment_1_min++;
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(increment_1_min != 0) {
          delay(500);
          increment_1_min--;
        }
      }
    } 

    // set increment seconds 
    if(mode_counter == 5) {
      display1_increment_on(SECONDS);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        increment_1_sec++;
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(increment_1_sec != 0) {
          delay(500);
          increment_1_sec--;
        }
      }
    } 

    if(mode_counter == 6) {
      display1_on();
      display2_on(HOURS);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        hours_2++;
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(hours_2 != 0) {
          delay(500);
          hours_2--;
        }
      }
    } 
    
    if(mode_counter == 7) {
      display2_on(MINUTES);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        mins_2++;
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(mins_2 != 0) {
          delay(500);
          mins_2--;
        }
      }
    } 

    if(mode_counter == 8) {
      display2_on(SECONDS);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        secs_2++;
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(secs_2 != 0) {
          delay(500);
          secs_2--;
        }
      }
    } 

    if(mode_counter == 9) {
      display2_increment_on(MINUTES);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        increment_2_min++;
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(increment_2_min != 0) {
          delay(500);
          increment_2_min--;
        }
      }
    }

    if(mode_counter == 10) {
      display2_increment_on(SECONDS);
      if(digitalRead(INCREMENT_BTN) == HIGH) {
        delay(500);
        increment_2_sec++;
      }
      if(digitalRead(DECREMENT_BTN) == HIGH) {
        if(increment_2_sec != 0) {
          delay(500);
          increment_2_sec--;
        }
      }
    }

    if (mode_counter > 10) {
      display2_on(NONE);
      mode_counter = 0;
      return;
    }
  }
}

#include <Arduino.h>
#include <stdio.h>
#include <U8g2lib.h>

#include "esp_timer.h"

#include "definitions.h"
#include "input.h"
#include "led.h"
#include "buzzer.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);   // EastRising 0.42" OLED

int mode = MAIN_TIMER;

int countdown_main = TIMER_MAIN_START;
int countdown_minute = TIMER_PERIOD; // 1 minute
int goals_home = 0;
int goals_away = 0;
int bat_value;

void timer_callback(void *arg) {
  countdown_main--;
  countdown_minute--;

  // Main timer - x minutes 
  if (countdown_main > 0 && countdown_main < 6) {
    start_buzzer(300);
  }
  else if (countdown_main == 0) {
    start_buzzer(800);
    countdown_main = TIMER_MAIN_PERIOD;
  }
  else if(countdown_main % 60 == 0) {
    start_buzzer(150, 1); //Mark each minute with a beep
  }

  // Periodic timer - 1 minute
  if (countdown_minute == 0) {
    adc_read_bat();
    countdown_minute = TIMER_PERIOD;
  }
}

void setup(void) {
  Serial.begin(115200);

  init_display();
  init_inputs();
  
  input_t* button_up = create_button((gpio_num_t)BUTTON_UP_PIN, false, &button_up_click, &button_up_hold, &button_up_dbl_click);
  input_t* button_down = create_button((gpio_num_t)BUTTON_DOWN_PIN, false, &button_down_click, &button_down_hold, &button_down_dbl_click);

  click_count_t click_hold = {1, 1};
  add_click_handler(button_up, click_hold, button_up_click_hold);

  init_adc();
  init_timer();
  init_buzzer();
  init_rgb_led();
  init_player();

  adc_read_bat();
  timer_start();
}

void loop(void) {
  draw();
  delay(100);
}
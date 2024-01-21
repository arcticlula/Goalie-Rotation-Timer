#include "buzzer.h"

// Add Home Goal
void button_up_click(input_t *input_p) {
  if(goals_home < 99 ) goals_home++;
}

// Revert Home Goal
void button_up_dbl_click(input_t *input_p) {
  if(goals_home > 0 ) goals_home--;
}

void button_up_click_hold(input_t *input_p) {
  play_song(NULL);
}

// Change Screens
void button_up_hold(input_t *input_p) {
  mode = mode == MAIN_TIMER ? MAIN_SCORE : MAIN_TIMER;
}

// Add Away Goal
void button_down_click(input_t *input_p) {
  if(goals_away < 99 ) goals_away++;
}

// Revert Away Goal
void button_down_dbl_click(input_t *input_p) {
  if(goals_away > 0 ) goals_away--;
}

// Toggle Volume
void button_down_hold(input_t *input_p) {
  int vol = get_buzzer_volume();
  switch(vol) {
    case 0: 
      vol = 1;
      break;
    case 1: 
      vol = 10;
      break;
    case 10: 
      vol = 25;
      break;
    case 25: 
      vol = 50;
      break;
    default:
      vol = 0;
  }
  set_buzzer_volume(vol);
  start_buzzer(150); //Test Volume
}
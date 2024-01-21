#include "buzzer.h"

int buzzer_volume = 0;

esp_timer_handle_t timer_stop_buzzer_handle;

// Pwm
ledc_timer_config_t buzzer_pwm_timer = {
    .speed_mode       = LEDC_MODE,
    .duty_resolution  = LEDC_DUTY_RES,
    .timer_num        = LEDC_TIMER,
    .freq_hz          = LEDC_FREQUENCY,
    .clk_cfg          = LEDC_AUTO_CLK
};

ledc_channel_config_t buzzer_pwm_channel = {
    .gpio_num       = BUZZER_PIN,
    .speed_mode     = LEDC_MODE,
    .channel        = LEDC_CHANNEL,
    .intr_type      = LEDC_INTR_DISABLE,
    .timer_sel      = LEDC_TIMER,
    .duty           = 0,
    .hpoint         = 0
};

void init_buzzer(void) {
  pwm_init();
  timer_init();
}

void set_buzzer_volume(int vol) {
  buzzer_volume = vol;
}

int get_buzzer_volume(void) {
  return buzzer_volume;
}

static void pwm_init(void) {
  // Configure LEDC PWM timer and channel for the Buzzer
  ledc_timer_config(&buzzer_pwm_timer);
  ledc_channel_config(&buzzer_pwm_channel);
}

static void timer_init(void) {
  esp_timer_create_args_t timer_stop_buzzer_args = {
      .callback = &stop_buzzer,
      .arg = NULL,
      .dispatch_method = ESP_TIMER_TASK,
      .name = "timer stop buzzer"
  };

  esp_timer_create(&timer_stop_buzzer_args, &timer_stop_buzzer_handle);
}

static void set_buzzer_duty(int vol) {
  int duty = 40.95 * vol; //Calculate duty from percentage - maximum is 4095 (2^13 - 1)
  ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
  ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

static void set_buzzer_freq(int freq) {
  buzzer_pwm_timer.freq_hz = freq;
  ledc_timer_config(&buzzer_pwm_timer);
}

static void start_buzzer_params(const buzzer_params& p) {
  int volume = p.volume == -1 ? buzzer_volume : p.volume;
  p.freq ? turn_led_on(100, 0, 100) : turn_led_off();

  set_buzzer_freq(p.freq);
  set_buzzer_duty(p.freq == 0 ? 0 : volume); //Debug on min vol
  esp_timer_start_once(timer_stop_buzzer_handle, p.time_ms * 1000);
}

void start_buzzer(int time_ms) {
  start_buzzer_params({ time_ms, LEDC_FREQUENCY, -1 });
}

void start_buzzer(int time_ms, int frequency) {
  start_buzzer_params({ time_ms, frequency, -1 });
}

void start_buzzer(int time_ms, int frequency, int volume) {
  start_buzzer_params({ time_ms, frequency, volume });
}

void stop_buzzer(void *arg) {
  turn_led_off();
  set_buzzer_duty(0);
}
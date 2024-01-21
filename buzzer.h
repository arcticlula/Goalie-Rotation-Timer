#pragma once

#include <stdlib.h>
#include "driver/ledc.h"
#include "esp_timer.h"

#include "definitions.h"
#include "led.h"

#define LEDC_TIMER        LEDC_TIMER_0
#define LEDC_MODE         LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL      LEDC_CHANNEL_0
#define LEDC_DUTY_RES     LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY_PER     50 // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY    2000 // Frequency in Hertz.

struct buzzer_params {
    int time_ms;
    int freq;
    int volume;
};

void init_buzzer(void);
int get_buzzer_volume(void);
void set_buzzer_volume(int vol);

static void pwm_init(void);
static void timer_init(void);

static void set_buzzer_duty(int vol);
static void set_buzzer_freq(int freq);

static void start_buzzer_params(const buzzer_params& p);

void start_buzzer(int time_ms);
void start_buzzer(int time_ms, int frequency);
void start_buzzer(int time_ms, int frequency, int volume);

void stop_buzzer(void *arg);
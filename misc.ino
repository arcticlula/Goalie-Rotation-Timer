// Timer
esp_timer_handle_t timer_handle;

static void init_timer(void) {
  esp_timer_create_args_t timer_args = {
    .callback = &timer_callback,
    .arg = NULL,
    .dispatch_method = ESP_TIMER_TASK,
    .name = "timer 1 sec"
  };

  esp_timer_create(&timer_args, &timer_handle);
}

static void timer_start(void) {
  esp_timer_start_periodic(timer_handle, TIMER_BASE * 1000);
}

// ADC
static void init_adc(void) {
  pinMode(ADC_BAT_EN_PIN, OUTPUT);
  digitalWrite(ADC_BAT_EN_PIN, HIGH);
}

void adc_read_bat() {
  digitalWrite(ADC_BAT_EN_PIN, LOW); //Reading will be enable for aprox 2ms
  int bat_reading = analogReadMilliVolts(ADC_BAT_PIN) * 2;
  digitalWrite(ADC_BAT_EN_PIN, HIGH);

  #ifdef DEBUG_BAT
    Serial.println(bat_reading);
    bat_value = bat_reading;
    return;
  #endif

  if(bat_reading <= BAT_MIN_LEVEL) { bat_value = 0; }
  else if(bat_reading >= BAT_MAX_LEVEL) { bat_value = 100; }
  else {
    int bat_100 = BAT_MAX_LEVEL - BAT_MIN_LEVEL;
    int bat_x = bat_reading - BAT_MIN_LEVEL;
    bat_value = (bat_x * 100) / bat_100;
  }
}
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "definitions.h"

Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGB_LED_PIN, NEO_GRB + NEO_KHZ800); //Onboard RGB Led

void init_rgb_led() {
  led.begin();
  led.setBrightness(50);
  led.show();
}

void turn_led_on(uint8_t r, uint8_t g, uint8_t b) {
  led.setPixelColor(0, led.Color(r,g,b));
  led.show();
}

void turn_led_off() {
  led.clear();
  led.show();
}

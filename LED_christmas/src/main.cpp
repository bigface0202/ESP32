#include <Arduino.h>
#include "FastLED.h"

#define NUM_LEDS 9
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, 21>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for(int i = 0; i < 8; i++){
    leds[i] = CRGB::Red;
    delay(400);
    FastLED.show();
  }
  for(int i = 0; i < 8; i++){
    leds[i] = CRGB::Green;
    delay(400);
    FastLED.show();
  }
  for(int i = 0; i < 8; i++){
    leds[i] = CRGB::Blue;
    delay(400);
    FastLED.show();
  }
}
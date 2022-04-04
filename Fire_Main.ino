#include "FastLED.h"

#define NUM_LEDS  50     // Enter the total number of LEDs on the strip
#define PIN       7      // The pin connected to DATA line to control the LEDs

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);    // Set power limit of LED strip to 5V, 1500mA
  FastLED.clear();                                    // Initialize all LEDs to "OFF"
}

void loop() {
  Fire(50, 100, 10);
}

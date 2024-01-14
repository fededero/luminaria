#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 52
CRGB leds[NUM_LEDS];

void setup() 
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() 
{
  leds[0] = 0x000001;
  FastLED.show();
  delay(100);
}

#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 22

CRGB leds[NUM_LEDS];

void setup() 
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //grb order

  
}

void loop() 
{
  int i;

  i=0x000100;
  leds[0] = i;
  //leds[1] = CRGB::Red;
  FastLED.show();
  delay(100);
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  FastLED.show();
  delay(100);
  
  
}

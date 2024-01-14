#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 52

#define MAX_C 0xFF
bool access = false;

CRGB leds[NUM_LEDS];

void setup() 
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //grb order

  
}

void loop() 
{
  access=true;
  int del=100;
  //warmColorsCycle(del);
  allColorsCycle(del);
}

//cycles between red and yellow minus a difference
void warmColorsCycle(int d)
{
  uint8_t i;
  int diff=80;
  while(access)
  {
    leds[0].r=MAX_C;
    for(i=0;i<MAX_C-diff;i++)
    {
      leds[0].g=i;
      FastLED.show();
      delay(d);
    }
    for(i=MAX_C-diff;i<0;i--)
    {
      leds[0].g=i;
      FastLED.show();
      delay(d);
    }
  }
}

//cycles all colors
void allColorsCycle(int d)
{
  uint8_t i;
  leds[0].r=MAX_C;
  FastLED.show();
  while(access)
  {
    //from red to yellow (r+g)
    for(i=0;i<MAX_C;i++)
    {
      leds[0].g=i;
      FastLED.show();
      delay(d);
    }
    //from yellow to green
    for(i=MAX_C;i<0;i--)
    {
      leds[0].r=i;
      FastLED.show();
      delay(d);
    }
    //from green to cyan (g+b)
    for(i=0;i<MAX_C;i++)
    {
      leds[0].b=i;
      FastLED.show();
      delay(d);
    }
    //from cyan to blue
    for(i=MAX_C;i<0;i--)
    {
      leds[0].g=i;
      FastLED.show();
      delay(d);
    }
    //from blue to purple (b+r)
    for(i=0;i<MAX_C;i++)
    {
      leds[0].r=i;
      FastLED.show();
      delay(d);
    }
    //from purple to red
    for(i=MAX_C;i<0;i--)
    {
      leds[0].b=i;
      FastLED.show();
      delay(d);
    }
  }
}

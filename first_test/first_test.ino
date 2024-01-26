#include <FastLED.h>

#define NUM_LEDS 300
#define ACTUAL_LEDS 180
#define DATA_PIN 5

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
  ultraWarmColorsCycle(del);
  //allColorsCycle(del);
  //randomColors(del);
}

//function to set the value of a given choice between r,g,b of all ACTUAL_LEDS
//it modifies only the value in the public array without showing it on the led strip (use of FastLED.show(); needed)
void setColor(char color,uint8_t value)
{
  uint8_t j;
  switch(color)
  {
    case 'r': 

      for(j=0;j<ACTUAL_LEDS;j++)
      {
        leds[j].r=value;
      }
      break;

    case 'g': 

      for(j=0;j<ACTUAL_LEDS;j++)
      {
        leds[j].g=value;
      }
      break;

    case 'b': 

      for(j=0;j<ACTUAL_LEDS;j++)
      {
        leds[j].b=value;
      }
      break;
  }
}

//cycles between red and yellow minus a difference
void warmColorsCycle(int d)
{
  uint8_t i;
  int diff=80;
  while(access)
  {
    setColor("r",MAX_C);
    for(i=0;i<MAX_C-diff;i++)
    {
      setColor("g",i);
      FastLED.show();
      delay(d);
    }
    for(i=MAX_C-diff;i>0;i--)
    {
      setColor("g",i);
      FastLED.show();
      delay(d);
    }
  }
}

//cycles between red and yellow minus a larger difference 
void ultraWarmColorsCycle(int d)
{
  uint8_t i;
  uint8_t j;
  int diff=140;
  while(access)
  {
    setColor("r",MAX_C);
    for(i=0;i<MAX_C-diff;i++)
    {
      setColor("g",i);
      FastLED.show();
      delay(d);
    }
    for(i=MAX_C-diff;i>0;i--)
    {
      setColor("g",i);
      FastLED.show();
      delay(d);
    }
  }
}

//cycles all colors 
void allColorsCycle(int d)
{
  uint8_t i;
  setColor("r",MAX_C);
  FastLED.show();
  while(access)
  {
    //from red to yellow (r+g)
    for(i=0;i<MAX_C;i++)
    {
      setColor("g",i);
      FastLED.show();
      delay(d);
    }
    //from yellow to green
    for(i=MAX_C;i>0;i--)
    {
      setColor("r",i);
      FastLED.show();
      delay(d);
    }
    //from green to cyan (g+b)
    for(i=0;i<MAX_C;i++)
    {
      setColor("b",i);
      FastLED.show();
      delay(d);
    }
    //from cyan to blue
    for(i=MAX_C;i<0;i--)
    {
      setColor("g",i);
      FastLED.show();
      delay(d);
    }
    //from blue to purple (b+r)
    for(i=0;i<MAX_C;i++)
    {
      setColor("r",i);
      FastLED.show();
      delay(d);
    }
    //from purple to red
    for(i=MAX_C;i<0;i--)
    {
      setColor("b",i);
      FastLED.show();
      delay(d);
    }
  }
}

//displays random colors
void randomColors(int del)
{
  uint8_t i,excl;
  while(access)
  {
    for(i=0;i<ACTUAL_LEDS;i++)
    {
      excl=random(1,4);
      switch(excl)
      {
        case 1:
          leds[i].r=0;
          leds[i].g=random(0,256);
          leds[i].b=random(0,256);
          break;
        case 2:
          leds[i].r=random(0,256);
          leds[i].g=0;
          leds[i].b=random(0,256);
          break;
        case 3:
          leds[i].r=random(0,256);
          leds[i].g=random(0,256);
          leds[i].b=0;
          break;
      }
    }
    FastLED.show();
    delay(del);
  }
}

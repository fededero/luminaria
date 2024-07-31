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

  
  //pulse(10, 'r');
  //strobe(50, CRGB::White);
  pingPongFast(1, CRGB::Blue, 8);
  //warmColorsCycle(del);
  //ultraWarmColorsCycle(del);
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

/*
 *@brief Single bouncing light
 *@param time between two frames, color of the light, lenght in number of LEDs
 *
*/
void pingPongEffect(int del, CRGB color, int trail){
  int position=1;
  bool increasing=true;
  while(access){
    for (size_t i = 0; i < ACTUAL_LEDS; i++)
    {
      if(i<position || i>=position+trail)
        leds[i] = CRGB::Black;
      else 
        leds[i] = color;
    }
    if(increasing==true){
      position++;
    }
    else{
      position--;
    }
    
    if(position>ACTUAL_LEDS-trail)
      increasing=false;
    if(position==0)
      increasing=true;

    FastLED.show();
    
    //delay(del);
  }
  return;
}

void pingPongFast(int del, CRGB color, int trail){
  int position=0;
  bool increasing=true;
  for (size_t i = 0; i < trail; i++)
    {
      leds[position+i]= color;
    }
  while(access){
    if(increasing==true){
      leds[position-1]=CRGB::Black;
      leds[position+trail-1]=color;
      position++;
    }
    if(increasing==false){
      leds[position]=color;
      leds[position+trail]=CRGB::Black;
      position--;
    }
    
    if(position>ACTUAL_LEDS-trail)
      increasing=false;
    if(position==0)
      increasing=true;

    FastLED.show();
    
    //delay(del);
  }
  return;
}

void strobe(int del, CRGB color){
  bool on = false;

  while(access){
    if(on == false){
      setCRGBColor(color);
      on = true;
    }
    else{
      setCRGBColor(CRGB::Black);
      on = false;
    }
    FastLED.show();
    delay(del);
  }
  return;
}

void setCRGBColor(CRGB color){

  for(int i=0; i<ACTUAL_LEDS; i++){
    leds[i]=color;
  }
  return;
}

void pulse(int del, char color){
  int value=0;
  bool inc=true;
  while(access){
    setColor(color, value);
    if(inc==true)
      value++;
     else
      value--;

    if(value=0)
      inc=true;
     if(value=255)
      inc=false;
    
    FastLED.show();
    delay(del);
  }
}

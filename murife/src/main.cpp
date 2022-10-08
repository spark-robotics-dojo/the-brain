#include <Arduino.h>

// import the custom library
#include <blink_library.h>

void setup()
{
  // put your setup code here, to run once:
  blinkSetup();
}

void loop()
{
  // put your main code here, to run repeatedly:
  // blinkNormal();
  blinkFast();
  // blinkSlow();
}

#include "blink_library.h"

// Set up the LED
void blinkSetup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

// Sample function - 1s delay
void blinkSlow()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

// Sample function - 0.5s delay
void blinkNormal()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

// Sample function - 0.25s delay
void blinkFast()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}
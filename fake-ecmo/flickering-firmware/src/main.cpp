#include <Arduino.h>

uint8_t flickeringPin1 = 3;
uint8_t flickeringPin2 = 4;
uint8_t flickeringPin3 = 5;

unsigned int fps = 1000 / 75;
unsigned int delayMs = 1000 / fps;
unsigned int minFluorescent = 50 * 100;
unsigned int minRandom = 85 * 100;
unsigned int max = 99 * 100;
unsigned int fluorescentFlickerPercent = 985 * 10;

void setup()
{
  pinMode(flickeringPin1, OUTPUT);
  pinMode(flickeringPin2, OUTPUT);
  pinMode(flickeringPin3, OUTPUT);
}

unsigned int brightness = max;
unsigned int brightnessRaw;

void flickerPin(uint8_t pin)
{
  brightness = max;

  if (random(0, 10000) > fluorescentFlickerPercent)
  {
    brightness = minFluorescent;
  }
  else
  {
    brightness = random(minRandom, max);
  }
  brightnessRaw = map(brightness, 0, 10000, 0, 255);
  analogWrite(pin, brightnessRaw);
}

void loop()
{
  flickerPin(flickeringPin1);
  flickerPin(flickeringPin2);
  flickerPin(flickeringPin3);
  delay(delayMs);
}
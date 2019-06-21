#include <Arduino.h>

uint8_t flickeringPin1 = 3;
uint8_t flickeringPin2 = 5;
uint8_t flickeringPin3 = 6;
uint8_t builtinLedPin = 13;

double sinusMin = 0.6;
double sinusMax = 1.0;
double radiansPerSecond = 0.06;

unsigned int fps = 16;

double minFluorescent = 0.2;
double minRandom = 0.85;
double fluorescentFlickerPercent = 0.994;

double blackoutsPerSecond = 0.0015;
unsigned int blackoutDurationMs = 5700;

// static calc
unsigned int delayMs = 1000 / fps;
double radiansPerFrame = radiansPerSecond / (double)fps;
double fullCircleRadians = 2 * 3.141592;
long blackoutProbability_100kP = (long)(blackoutsPerSecond * (double)100000) / (long)fps;

void setup()
{
  pinMode(flickeringPin1, OUTPUT);
  pinMode(flickeringPin2, OUTPUT);
  pinMode(flickeringPin3, OUTPUT);
  pinMode(builtinLedPin, OUTPUT);
}

double brightness = 1.0;
unsigned int brightnessRaw;
double sinRotationRadians = 0.0;

void flickerPin(uint8_t pin)
{
  brightness = 1.0;

  sinRotationRadians += radiansPerFrame;
  if (sinRotationRadians > fullCircleRadians)
    sinRotationRadians -= fullCircleRadians;
  brightness = sinusMin + sin(sinRotationRadians) * (sinusMax - sinusMin);

  if (random(0, 10000) > (unsigned int)((double)10000 * fluorescentFlickerPercent))
  {
    brightness *= minFluorescent;
  }
  else
  {
    brightness *= ((double)random((long)(minRandom * 1000), 1000) / (double)1000);
  }
  brightnessRaw = (unsigned int)(floor(brightness * (double)255));
  analogWrite(pin, brightnessRaw);
}

void blackoutPin(uint8_t pin)
{
  analogWrite(pin, 0);
}

void loop()
{
  if (blackoutProbability_100kP > random(0, 100000))
  {
    blackoutPin(flickeringPin1);
    blackoutPin(flickeringPin2);
    blackoutPin(flickeringPin3);
    blackoutPin(builtinLedPin);
    delay(blackoutDurationMs);
  }

  flickerPin(flickeringPin1);
  flickerPin(flickeringPin2);
  flickerPin(flickeringPin3);
  flickerPin(builtinLedPin);
  delay(delayMs);
}
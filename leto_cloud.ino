#include <Adafruit_NeoPixel.h>

#define PIN 8

const long MIN_LIGHTNING_INTERVAL = 1000;
const long MAX_LIGHTNING_INTERVAL = 12000;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
unsigned long lastUpdatedMs = 0;
long lightningInterval;           // milliseconds of time between lightning
bool isSunsetMode = false;
long sunsetInterval = 10000;      // milliseconds of time until next sunset transition

void setup() {
  randomSeed(analogRead(0));
  strip.begin();
  strip.setBrightness(100);
  strip.show(); // Initialize all pixels to 'off'
  lightningInterval = 8000;
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    int inChar = Serial.read();
    isSunsetMode = !isSunsetMode;
    lastUpdatedMs = 0;
  }

  isSunsetMode ? SunsetMode() : LightningMode();
}

void SunsetMode()
{
  if (millis() - lastUpdatedMs >= sunsetInterval)
    {
      strip.setPixelColor(0, strip.Color(155, 0, 55));
      strip.show();
      lastUpdatedMs = millis();
    }
}

void LightningMode()
{
  if (millis() - lastUpdatedMs >= lightningInterval)
    {
      uint8_t lightningType = random(0, 5);
      uint8_t pixelPosition = random(0, strip.numPixels() - 1);
      switch(lightningType)
      {
        case 0: 
        {
          NormalLightning(pixelPosition);
          break;
        }
        case 1: 
        {
          PurpleLightning(pixelPosition);
          break;
        }
        case 2: 
        {
          DramaticLightning(pixelPosition);
          break;
        } 
        case 3: 
        {
          WhiteLightning(pixelPosition);
          break;
        }
        case 4: 
        {
          NormalLightning(pixelPosition);
          break;
        }
      }
      lastUpdatedMs = millis();
      lightningInterval = random(MIN_LIGHTNING_INTERVAL, MAX_LIGHTNING_INTERVAL);
      Serial.println(lightningInterval);
    }
  
    strip.setPixelColor(0, strip.Color(5, 0, 5));
    strip.show();
    delay(10);
}

void SetLightningPixel(uint8_t wait, uint8_t pixelPosition, uint8_t r, uint8_t g, uint8_t b) 
{
  strip.setPixelColor(pixelPosition, strip.Color(r, g, b));
  strip.show();
  delay(wait);
}

void DramaticLightning(uint8_t pixelPosition)
{
  strip.setBrightness(100);
  SetLightningPixel(10000, pixelPosition, 255, 255, 255); //white
  SetLightningPixel(3000, pixelPosition, 0, 0, 255); // blue
  SetLightningPixel(1000, pixelPosition, 255, 0, 255); //purple
  Serial.println("drama");
}

void WhiteLightning(uint8_t pixelPosition)
{
  strip.setBrightness(80);
  SetLightningPixel(10000, pixelPosition, 255, 255, 255); //white
  Serial.println("white");
}

void PurpleLightning(uint8_t pixelPosition)
{
  strip.setBrightness(100);
  SetLightningPixel(1000, pixelPosition, 255, 255, 255); //white
  SetLightningPixel(3000, pixelPosition, 155, 0, 255); //purple
  Serial.println("purple");
}

void NormalLightning(uint8_t pixelPosition)
{
  strip.setBrightness(50);
  SetLightningPixel(10000, pixelPosition, 255, 255, 255); //white
  SetLightningPixel(1000, pixelPosition, 55, 0, 255); //blue purple
  Serial.println("normal");
}

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN_RGB1 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN_RGB1, NEO_GRB + NEO_KHZ800);

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  
  strip.begin();
  strip.setBrightness(250);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Your custom routines
  solidColor(strip.Color(0, 0, 255), 2000);      // Blue solid for 2 seconds
  blinkColor(strip.Color(0, 0, 255), 500, 5);    // Blue blinking (500ms on/off, 5 times)
  
  solidColor(strip.Color(0, 255, 0), 2000);      // Green solid for 2 seconds
  blinkColor(strip.Color(0, 255, 0), 500, 5);    // Green blinking (500ms on/off, 5 times)
  
  solidColor(strip.Color(255, 255, 0), 2000);    // Yellow solid for 2 seconds
}

// Display a solid color for a specified duration
void solidColor(uint32_t c, uint16_t duration) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(duration);
}

// Blink all LEDs with a color
void blinkColor(uint32_t c, uint16_t interval, uint8_t times) {
  for(uint8_t i=0; i<times; i++) {
    // Turn on
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, c);
    }
    strip.show();
    delay(interval);
    
    // Turn off
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, 0);
    }
    strip.show();
    delay(interval);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) {
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);
      }
      strip.show();
      delay(wait);
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);
      }
    }
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));
      }
      strip.show();
      delay(wait);
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);
      }
    }
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
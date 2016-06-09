#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define MOTION_SENSOR 2
#define SOUND_TRIGGER 4
#define STATUS_LED 13
#define EYES_LED 5
#define NUM_EYES_LED 2

boolean hooting = false;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_EYES_LED, EYES_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  //Serial.begin(115200);
  pinMode(MOTION_SENSOR, INPUT);
  pinMode(SOUND_TRIGGER, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(MOTION_SENSOR), motionDetected, RISING);

  strip.begin();
  strip.setBrightness(30);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
}

void motionDetected() {
    digitalWrite(STATUS_LED, HIGH);    
    digitalWrite(SOUND_TRIGGER, HIGH);
    rainbowEyes(20);
    eyesOff(20);
    digitalWrite(SOUND_TRIGGER, LOW); 
    digitalWrite(STATUS_LED, LOW);
}

void rainbowEyes(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++)
  {
    for(i=0; i<strip.numPixels(); i++)
    {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void eyesOff(uint8_t wait) {
  uint16_t i, j;
  for (j=255; j!=0; j--)
  {
    for (i=0; i<strip.numPixels(); i++)
    {
      strip.setPixelColor(i, j, 0, 0);
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

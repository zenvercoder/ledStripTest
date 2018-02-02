#include "FastLED.h"

FASTLED_USING_NAMESPACE

#define LED_PIN 11
#define CLOCK_PIN 10
// the little black very tiny integrated circuit in the led
#define CHIPSET APA102
// adjust this to test how many leds in your strip
#define NUM_LEDS 70
#define FRAMES_PER_SECOND 10

#if FASTLED_VERSION < 3001001
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

uint8_t brightnessFactor = 2; // divide 255 by this
CRGB leds[NUM_LEDS];

uint8_t head = 0; // the head pixel position
void trailOfSeven();

void setup() {

    Serial.begin(9600);

    FastLED.addLeds<CHIPSET, LED_PIN, CLOCK_PIN, BGR, DATA_RATE_MHZ(4)>(leds, NUM_LEDS);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(255 / brightnessFactor); //0-255
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // Set all leds black
    FastLED.show();
}

void loop() {

    trailOfSeven();

    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);

}

void trailOfSeven() {

    fadeToBlackBy(leds, NUM_LEDS, 255);

    if (++head == NUM_LEDS) {
        head = 0;
    }

    leds[head] = CRGB::Blue;

}
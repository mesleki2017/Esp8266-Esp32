
#include <Adafruit_NeoPixel.h>


#define PIN        D3 // On Trinket or Gemma, suggest changing this to 1

#define NUMPIXELS 24// Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 200 // Time (in milliseconds) to pause between pixels

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20); 
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(random(0,255), random(0,255),random(0,255)));

    pixels.show();   // Send the updated pixel colors to the hardware.

   // delay(DELAYVAL); // Pause before next pass through loop
  }
}

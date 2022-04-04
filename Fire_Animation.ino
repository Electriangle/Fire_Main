// FlameHeight - Use larger value for shorter flames, default=50.
// Sparks - Use larger value for more ignitions and a more active fire (between 0 to 255), default=100.
// DelayDuration - Use larger value for slower flame speed, default=10.

void Fire(int FlameHeight, int Sparks, int DelayDuration) {
  static byte heat[NUM_LEDS];
  int cooldown;
  
  // Cool down each cell a little
  for(int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((FlameHeight * 10) / NUM_LEDS) + 2);
   
    if(cooldown > heat[i]) {
      heat[i] = 0;
    }
    else {
      heat[i] = heat[i] - cooldown;
    }
  }
  
  // Heat from each cell drifts up and diffuses slightly
  for(int k = (NUM_LEDS - 1); k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
  
  // Randomly ignite new Sparks near bottom of the flame
  if(random(255) < Sparks) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
  }
  
  // Convert heat to LED colors
  for(int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j]);
  }
  
  FastLED.show();
  delay(DelayDuration);
}

void setPixelHeatColor(int Pixel, byte temperature) {
  // Rescale heat from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);
  
  // Calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0...63
  heatramp <<= 2; // scale up to 0...252
  
  // Figure out which third of the spectrum we're in:
  if(t192 > 0x80) {                    // hottest
    leds[Pixel].setRGB(255, 255, heatramp);
  }
  else if(t192 > 0x40) {               // middle
    leds[Pixel].setRGB(255, heatramp, 0);
  }
  else {                               // coolest
    leds[Pixel].setRGB(heatramp, 0, 0);
  }
}

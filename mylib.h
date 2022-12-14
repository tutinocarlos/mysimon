
void apagar(int ronda=1) {

if(ronda !=1 ){
  strip.fill(strip.Color(255, 255, 255, 255), 0, 48);
  }else{
      strip.clear();
    }
 ;
  strip.show();
}
void segmento(uint32_t color, int desde, int hasta, int wait) {

  for (int i = desde; i <= hasta; i++) { // For each pixel in strip...

    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment

  }

}
void error() {
 segmento(strip.Color(255,0,0,255),0, 48,1); 

}
void inicio() {
 segmento(strip.Color(0,255,0, 255),0, 48, DEFAULT_DELAY);
 strip.show();

}
void encenderTodo(){
  segmento(strip.Color(255,0,0,255),0, 11, DEFAULT_DELAY); 
  segmento(strip.Color(0,0,255, 255),12, 23, DEFAULT_DELAY);
  segmento(strip.Color(255,255,0, 255),24, 35, DEFAULT_DELAY); 
  segmento(strip.Color(0,255,0, 255),36, 48, DEFAULT_DELAY);

}

void activarSegmentoError(int led, int speed) {

  switch (led) {
    case 2:
   
      segmento(strip.Color(  255, 0,   0, 255), 0, 11, speed); // True white (not RGB white)
      segmento(strip.Color(255, 255,   255,255), 12, 48, speed); // True white (not RGB white)
     
      break;
    case 3:
      segmento(strip.Color( 255,255,255,255), 0, 11, speed); // True white (not RGB white)
      segmento(strip.Color(  255,  0,   0, 255), 12, 23, speed); // True white (not RGB white)
      segmento(strip.Color(255,255,255,255), 24, 38, speed); // True white (not RGB white)
      break;
    case 4:
      segmento(strip.Color(255,255,255,255), 0,23, speed); // True white (not RGB white)
      segmento(strip.Color(  255,   0,0, 255), 24, 35, speed); // True white (not RGB white)
      segmento(strip.Color(255,255,255,255), 36, 48, speed); // True white (not RGB white)
      break;
    case 5:
     segmento(strip.Color(255,255,255,255), 0, 36, speed); // True white (not RGB white)
      segmento(strip.Color(255,0,0, 255), 36, 48, speed); // True white (not RGB white)
      break;

  }
}

void activarSegmento(int led, int speed) {

  switch (led) {
    case 2:
   
      segmento(strip.Color(  255, 0,   0, 255), 0, 11, speed); // True white (not RGB white)
      segmento(strip.Color(0, 0,   0, 0), 12, 23, speed); // True white (not RGB white)
      segmento(strip.Color(  0,   0,   0, 0), 24, 35, speed); // True white (not RGB white)
      segmento(strip.Color(  0,   0,   0, 0), 36, 48, speed); // True white (not RGB white)
      break;
    case 3:
      segmento(strip.Color(  0,   0,   0, 0), 0, 11, speed); // True white (not RGB white)
      segmento(strip.Color(  0,  0,   255, 255), 12, 23, speed); // True white (not RGB white)
      segmento(strip.Color(  0,   0,   0, 255), 24, 35, speed); // True white (not RGB white)
      segmento(strip.Color(  0,   0,   0, 255), 36, 48, speed); // True white (not RGB white)
      break;
    case 4:
      segmento(strip.Color(  0,   0,   0, 0), 0, 11, speed); // True white (not RGB white)
      segmento(strip.Color(  0,   0,   0, 0), 12, 23, speed); // True white (not RGB white)
      segmento(strip.Color(  255,   255,0, 255), 24, 35, speed); // True white (not RGB white)
      segmento(strip.Color(  0,   0,   0, 0), 36, 48, speed); // True white (not RGB white)
      break;
    case 5:
      segmento(strip.Color(  0,   0,   0, 0), 0, 11, speed); // True white (not RGB white)
      segmento(strip.Color(  0,   0,   0, 0), 12, 23, speed); // True white (not RGB white)
      segmento(strip.Color(  0,   0,   0, 0), 24, 35, speed); // True white (not RGB white)
      segmento(strip.Color(  0,   255,   0, 255), 36, 48, speed); // True white (not RGB white)
      break;

  }
}

void pintarSegmento(int led) {


  switch (led) {
    case 2:
   segmento(strip.Color(  255, 0,   0, 255), 0, 11, DEFAULT_DELAY); // True white (not RGB white)
      segmento(strip.Color(255, 255,   255, 255), 12, 23, DEFAULT_DELAY); // True white (not RGB white)
      segmento(strip.Color(  255, 255, 255,255), 24, 35, DEFAULT_DELAY); // True white (not RGB white)
      segmento(strip.Color(  255,  255,255,255), 36, 48, DEFAULT_DELAY); // True white (not RGB white)
      break;
    case 3:
     segmento(strip.Color(  255,255,255, 255), 0, 11, DEFAULT_DELAY); // True white (not RGB white)
      segmento(strip.Color(  0,0,255, 255), 12, 23, DEFAULT_DELAY); // True white (not RGB white)
       segmento(strip.Color(  255, 255,255, 255), 24, 48, DEFAULT_DELAY); // True white (not RGB white)
      break;
    case 4:
    segmento(strip.Color(255,255,255, 255), 0, 23, DEFAULT_DELAY); // True white (not RGB white)
      segmento(strip.Color(  255,   255,0, 255), 24, 35, DEFAULT_DELAY); // True white (not RGB white)
      segmento(strip.Color(255,255,255, 255), 36, 48, DEFAULT_DELAY); // True white (not RGB white)
      
      break;
    case 5:
     segmento(strip.Color(  255,255,255, 255), 0, 35, DEFAULT_DELAY); // True white (not RGB white)
      segmento(strip.Color(  0,   255,   0, 255), 36, 48, DEFAULT_DELAY); // True white (not RGB white)
      break;

  }
}

void s2() {
  Serial.println("funct 2");
  segmento(strip.Color(  255, 255,   0, 0), 0, 11, DEFAULT_DELAY); // True white (not RGB white)

  segmento(strip.Color(0, 0,   0, 0), 12, 23, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   0,   0, 0), 24, 35, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   0,   0, 0), 36, 48, DEFAULT_DELAY); // True white (not RGB white)

  //  segmento(strip.Color(  0,   0,   0, 0), 0, 11, DEFAULT_DELAY); // True white (not RGB white)
}

void s3() {
  Serial.println("funct 3");
  segmento(strip.Color(  0,   0,   0, 255), 0, 11, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,  0,   255, 255), 12, 23, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   0,   0, 255), 24, 35, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   0,   0, 255), 36, 48, DEFAULT_DELAY); // True white (not RGB white)

  //  segmento(strip.Color(  0,  0,   0, 0), 12, 23, DEFAULT_DELAY); // True white (not RGB white)
}

void s4() {
  Serial.println("funct 4");
  segmento(strip.Color(  0,   0,   0, 0), 0, 11, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   0,   0, 0), 12, 23, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   255,   0, 255), 24, 35, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   0,   0, 0), 36, 48, DEFAULT_DELAY); // True white (not RGB white)

  //  segmento(strip.Color(  0,   0,   0, 0), 24, 35, DEFAULT_DELAY); // True white (not RGB white)
}

void s5() {
  Serial.println("funct 5");
  segmento(strip.Color(  0,   0,   0, 0), 0, 11, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   0,   0, 0), 12, 23, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   0,   0, 0), 24, 35, DEFAULT_DELAY); // True white (not RGB white)
  segmento(strip.Color(  0,   0,   255, 255), 36, 48, DEFAULT_DELAY); // True white (not RGB white)

  //  segmento(strip.Color(  0,   0,   0, 0), 36, 48, DEFAULT_DELAY); // True white (not RGB white)
}

void whiteOverRainbow(int whiteSpeed, int whiteLength) {

  if (whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;

  int      head          = whiteLength - 1;
  int      tail          = 0;
  int      loops         = 3;
  int      loopNum       = 0;
  uint32_t lastTime      = millis();
  uint32_t firstPixelHue = 0;

  for (;;) { // Repeat forever (or until a 'break' or 'return')

    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      if (((i >= tail) && (i <= head)) ||     //  If between head & tail...
          ((tail > head) && ((i >= tail) || (i <= head)))) {
        strip.setPixelColor(i, strip.Color(0, 0, 0, 255)); // Set white
      } else {                                             // else set rainbow
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
    }

    strip.show(); // Update strip with new contents
    // There's no delay here, it just runs full-tilt until the timer and
    // counter combination below runs out.

    firstPixelHue += 40; // Advance just a little along the color wheel

    if ((millis() - lastTime) > whiteSpeed) { // Time to update head/tail?
      if (++head >= strip.numPixels()) {     // Advance head, wrap around
        head = 0;
        if (++loopNum >= loops) return;
      }
      if (++tail >= strip.numPixels()) {     // Advance tail, wrap around
        tail = 0;
      }
      lastTime = millis();                   // Save time of last movement
    }
  }
}

void rainbowFade2White(int wait, int rainbowLoops, int whiteLoops, int  ronda ) {

  int fadeVal = 0, fadeMax = 100;


  // Hue of first pixel runs 'rainbowLoops' complete loops through the color
  // wheel. Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to rainbowLoops*65536, using steps of 256 so we
  // advance around the wheel at a decent clip.

  for (uint32_t firstPixelHue = 0; firstPixelHue < rainbowLoops * 65536;
       firstPixelHue += 256) {


    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...

      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      uint32_t pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());

      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the three-argument variant, though the
      // second value (saturation) is a constant 255.
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue, 255,
                                           255 * fadeVal / fadeMax)));
    }

    strip.show();
    delay(wait);

    if (firstPixelHue < 65536) {                             // First loop,
      if (fadeVal < fadeMax) fadeVal++;                      // fade in
    } else if (firstPixelHue >= ((rainbowLoops - 1) * 65536)) { // Last loop,
      if (fadeVal > 0) fadeVal--;                            // fade out
    } else {
      fadeVal = fadeMax; // Interim loop, make sure fade is at max
    }
  }

  for (int k = 0; k < whiteLoops; k++) {
    for (int j = 0; j < 256; j++) { // Ramp up 0 to 255
      // Fill entire strip with white at gamma-corrected brightness level 'j':
      strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
      strip.show();
    }
    delay(1000); // Pause 1 second
    for (int j = 255; j >= 0; j--) { // Ramp down 255 to 0
      strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
      strip.show();
    }
  }

  delay(500); // Pause 1/2 second
}

// in this example a ring of 8 RGB LEDs are used


#include "WS2811_Lib_for_ESP32.h"

#define LEDS_COUNT  24
#define LEDS_PIN	2
#define CHANNEL		0

uint8_t led3_red[3] = 	 {0, 200, 0};       // green, red, blue
uint8_t led3_orange[3] = {90, 200, 0};  	// green, red, blue
uint8_t led3_white[3] =  {60, 60, 50};      // green, red, blue


ESP32_WS2811 strip = ESP32_WS2811(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);


void setup() {
  
  Serial.begin(115200);
  
  Serial.println("reset all leds");
  strip.begin();
  strip.show();			
  delay(5000);

  strip.setBrightness(20);						// global brightness for some of the functions 0-255
  
  
  Serial.println("set_rgb red");
  strip.set_rgb(0, 0, 20, 0);  					// index, green, red, blue
  strip.show();
  delay(2000);
  strip.set_rgb(3, 0, 20, 0);
  strip.show();
  delay(2000);
  strip.set_rgb(6, 0, 20, 0);
  strip.show();
  delay(2000);
  strip.set_rgb(9, 0, 20, 0);
  strip.show();
  delay(2000);
  strip.set_rgb(12, 0, 20, 0);
  strip.show();
  delay(2000);
  strip.set_rgb(15, 0, 20, 0);
  strip.show();
  delay(2000);
  strip.set_rgb(18, 0, 20, 0);
  strip.show();
  delay(2000);
  strip.set_rgb(21, 0, 20, 0);
  strip.show();
  delay(5000);
  
  strip.off();
  strip.show();
  delay(2000);
  
   
  Serial.println("set predefined color red");	//set_led3(index, name of color, brightness 0-255)
  strip.set_led3(0, led3_red, 50); 
  strip.show();
  delay(5000);

  Serial.println("set predefined color orange");
  strip.set_led3(3, led3_orange, 100); 
  strip.show();
  delay(5000);

  Serial.println("set predefined color white");
  strip.set_led3(6, led3_white, 100); 
  strip.show();
  delay(5000);  
  
  strip.off();
  strip.show();
  delay(2000);  


  // set single pixel
  Serial.println("set single pixel");
  strip.set_pixel(1, 50);  						// index: 0 green  1 red  2 blue, brightness
  strip.show();
  delay(5000);
  
  strip.off();
  strip.show();
  delay(2000);   
  
 
  // Specific for the folowing functions:
  // The order of the pixels is corrected by the parameter TYPE_??? to RGB.
  // The brightnes is set by strip.setBrightness(x); 
  
  Serial.println("setLedColorData");
  strip.setLedColorData(0, 255, 0, 0);			// index, red, green, blue
  strip.show();
  delay(2000);
  strip.setLedColorData(3, 0, 255, 0);
  strip.show();
  delay(2000);
  strip.setLedColorData(6, 0, 0, 255);
  strip.show();
  delay(2000);
  strip.setLedColorData(9, 255, 0, 0);
  strip.show();
  delay(2000);
  strip.setLedColorData(12, 0, 255, 0);
  strip.show();
  delay(2000);
  strip.setLedColorData(15, 0, 0, 255);
  strip.show();
  delay(2000);
  strip.setLedColorData(18, 255, 0, 0);
  strip.show();
  delay(2000);
  strip.setLedColorData(21, 0, 255, 0);
  strip.show();
  delay(5000);

  strip.off();
  strip.show();
  delay(2000);                 
  
  
  // same color for all LEDs
  Serial.println("setAllLedsColorData");
  strip.setAllLedsColorData(0, 100, 0);  		// red, green, blue
  strip.show();
  delay(5000);
  
  strip.off();
  strip.show();
  delay(2000);  
   
  
  // show some random colors
  for (int i = 0; i < 10; i++){ 
    Serial.println("random colors");
    Serial.println(i);
    strip.random();
    strip.show();
    delay(1000);
  }
  
  strip.off();
  strip.show();
  delay(2000);  
  
}

void loop() {
 
  for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < LEDS_COUNT; i+= 3) {
      strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
    }
    strip.show();
    delay(10);
  } 

   
}

// in this example 3 RGBW LEDs are used


#include "WS2811_Lib_for_ESP32.h"

#define LEDS_COUNT  12    // 3 LEDs whith 4 pixels each = 12
#define LEDS_PIN	  2     // hook up GPIO 2 or any other pin which works as an output
#define CHANNEL		  0

// define some colors at maximum brightnes needed
uint8_t led4_white[4] = { 0, 50, 0, 255};      // green, red, blue, white
uint8_t led4_blue[4] =  { 0,  0, 255, 0};      // green, red, blue, white


//ESP32_WS2811 strip = ESP32_WS2811(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);
ESP32_WS2811 strip = ESP32_WS2811(LEDS_COUNT, LEDS_PIN, CHANNEL);


void setup() {
  
  Serial.begin(115200);
  
  Serial.println("reset all leds");
  strip.begin();
  strip.show();			
  delay(5000);


  Serial.println("set rgbw white");
  strip.set_rgbw(4, 0, 10, 0, 40);    // index, green, red, blue, white
  strip.show();
  delay(5000); 


  Serial.println("set predefined color white and brightness");
  strip.set_led4(8, led4_white, 50);  // index, name of predefined color, brightness
  strip.show();
  delay(5000); 

  
  // set single pixel
  Serial.println("set_pixel 0");
  strip.set_pixel(0, 50);             // index: 0 green  1 red  2 blue  3 white , brightness
  strip.show();
  delay(5000);
  
  strip.off();
  strip.show();
  delay(2000);   

  Serial.println("set_pixel 1");
  strip.set_pixel(1, 50);             // index: 0 green  1 red  2 blue  3 white , brightness
  strip.show();
  delay(5000);
  
  strip.off();
  strip.show();
  delay(2000);   

  Serial.println("set_pixel 2");
  strip.set_pixel(2, 50);             // index: 0 green  1 red  2 blue  3 white , brightness
  strip.show();
  delay(5000);
  
  strip.off();
  strip.show();
  delay(2000);   

  Serial.println("set_pixel 3");
  strip.set_pixel(3, 50);             // index: 0 green  1 red  2 blue  3 white , brightness
  strip.show();
  delay(5000);
  
  strip.off();
  strip.show();
  delay(2000);        
  
}

void loop() {
  strip.set_led4(0, led4_blue, 50);
  strip.set_led4(8, led4_blue,  0); 
  strip.show();
  delay(250);

  strip.set_led4(0, led4_blue,  0);
  strip.set_led4(8, led4_blue, 50); 
  strip.show();
  delay(250);        
}

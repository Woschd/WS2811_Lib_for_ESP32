// WS2811_Lib_for_ESP32.h
/**
 * Brief	A library for controlling ws2811 or ws2812 in esp32 platform.
 * original Author	ZhentaoLin
 * Company	Freenove
 * Date		2021-10-15
 *
 * modified by Andreas_ 2022
 */

#ifndef _WS2811_LIB_FOR_ESP32_h
#define _WS2811_LIB_FOR_ESP32_h

// !! muss das extra eingebunden werden, oder macht das Arduino direkt?
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#endif


enum LED_TYPE
{					  //R  G  B
	TYPE_RGB = 0x06,  //00 01 10
	TYPE_RBG = 0x09,  //00 10 01
	TYPE_GRB = 0x12,  //01 00 10
	TYPE_GBR = 0x21,  //10 00 01
	TYPE_BRG = 0x18,  //01 10 00
	TYPE_BGR = 0x24	  //10 01 00
};

class ESP32_WS2811
{
protected:
	
	uint16_t ledCounts;		
	uint8_t pin;
	uint8_t br;				// brightness 0-255
	uint8_t rmt_chn;		// rmt channel 0-7
	
	uint8_t rOffset;
	uint8_t gOffset;
	uint8_t bOffset;
	
	float realTick;
	rmt_reserve_memsize_t rmt_mem;
	rmt_data_t *led_data;
	rmt_obj_t* rmt_send = NULL;

public:
	ESP32_WS2811(uint16_t n = 8,
	uint8_t pin_gpio = 2,
	 uint8_t chn = 0,
	  LED_TYPE t = TYPE_GRB);

    ~ESP32_WS2811();

    esp_err_t  random();

	bool begin();				
	void setLedType(LED_TYPE t);
	void setBrightness(uint8_t brightness);	//brightness 0-255

	

	// schreibt den Wert eines einzelnen Pixels
	esp_err_t set_pixel(int index, uint8_t x);								
	
	// schreibt den LED Wert mit 3 Pixeln in den Speicher, Ausgabe mit show()
	esp_err_t set_rgb(int index, uint8_t r, uint8_t g, uint8_t b);			
	

	// schreibt den LED Wert mit 4 Pixeln in den Speicher, Ausgabe mit show()
	esp_err_t set_rgbw(int index, uint8_t r, uint8_t g, uint8_t b, uint8_t w );
	
	
	// schreibt den vordefinierten LED Wert aus Array mit 3 Pixeln und Helligkeit in den Speicher, Ausgabe mit show()
	esp_err_t set_led3(int index, uint8_t col[], uint8_t pwr);

	
	// schreibt den vordefinierten LED Wert aus Array mit 3 Pixeln und Helligkeit in den Speicher, Ausgabe mit show()
	esp_err_t set_led4(int index, uint8_t col[], uint8_t pwr);
	
	
	esp_err_t setLedColorData(int index, uint32_t rgb);					
	esp_err_t setLedColorData(int index, uint8_t r, uint8_t g, uint8_t b);	

	
	// ruft setLedColorData auf
	esp_err_t setAllLedsColorData(uint32_t rgb);						
	esp_err_t setAllLedsColorData(uint8_t r, uint8_t g, uint8_t b);			


	// alle LEDs ausschalten
	esp_err_t off();
	
	esp_err_t show();														

	uint32_t Wheel(byte pos);												
};

#endif


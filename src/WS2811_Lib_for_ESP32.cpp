// 
// 
// 
/**
 * Brief	A library for controlling ws2811 or ws2812 in esp32 platform.
 * original Author	ZhentaoLin
 * Company	Freenove
 * Date		2021-10-15
 *
 * modified by Andreas_ 2022
 */

#include "WS2811_Lib_for_ESP32.h"
#include <Arduino.h>

ESP32_WS2811::ESP32_WS2811(uint16_t  n /*= 8*/, uint8_t  pin_gpio /*= 2*/, uint8_t  chn /*= 0*/, LED_TYPE t /*= TYPE_GRB*/)
{
    led_data = new rmt_data_t[24*n];
	ledCounts = n;
	pin = pin_gpio;
	rmt_chn = chn;
	rmt_mem = RMT_MEM_64;
	br = 255;
	setLedType(t);
}

ESP32_WS2811::~ESP32_WS2811()
{
	delete led_data;
	led_data = NULL;
}

bool ESP32_WS2811::begin()
{	
	switch(rmt_chn){
		case 0:
			rmt_mem=RMT_MEM_64;break;
		case 1:
			rmt_mem=RMT_MEM_128;break;
		case 2:
			rmt_mem=RMT_MEM_192;break;
		case 3:
			rmt_mem=RMT_MEM_256;break;
		case 4:
			rmt_mem=RMT_MEM_320;break;
		case 5:
			rmt_mem=RMT_MEM_384;break;
		case 6:
			rmt_mem=RMT_MEM_448;break;
		case 7:
			rmt_mem=RMT_MEM_512;break;		
		default:
			rmt_mem=RMT_MEM_64;break;
	}
	if ((rmt_send = rmtInit(pin, true, rmt_mem)) == NULL){
		return false;
	}
	for(int i=0;i<ledCounts;i++)
	{
		for (int bit = 0; bit < 8; bit++) {		
			led_data[i*8+bit].level0 = 1;
			led_data[i*8+bit].duration0 = 4;
			led_data[i*8+bit].level1 = 0;
			led_data[i*8+bit].duration1 = 8;
		}
	}
	realTick = rmtSetTick(rmt_send, 100);
	return true;
}


void ESP32_WS2811::setLedType(LED_TYPE t)
{
	rOffset = (t >> 4) & 0x03;
	gOffset = (t >> 2) & 0x03;
	bOffset = t & 0x03;
}


void ESP32_WS2811::setBrightness(uint8_t  brightness)
{
	br = constrain(brightness, 0, 255);
}


esp_err_t ESP32_WS2811::setLedColorData(int index, uint32_t  rgb)
{
	return setLedColorData(index, rgb >> 16, rgb >> 8, rgb);
}


esp_err_t ESP32_WS2811::setLedColorData(int index, uint8_t  r, uint8_t  g, uint8_t  b)
{
	uint8_t  p[3];
	p[rOffset] = r * br / 255;
	p[gOffset] = g * br / 255;
	p[bOffset] = b * br / 255;

	return set_rgb(index, p[0], p[1], p[2]);
}


esp_err_t ESP32_WS2811::set_pixel(int index, uint8_t x)
{
	uint32_t  color = x;
	for (int bit = 0; bit < 8; bit++) {
		if (color & (1 << (7-bit))) {
			led_data[index*8+bit].level0 = 1;
			led_data[index*8+bit].duration0 = 8;
			led_data[index*8+bit].level1 = 0;
			led_data[index*8+bit].duration1 = 4;
		} else {
			led_data[index*8+bit].level0 = 1;
			led_data[index*8+bit].duration0 = 4;
			led_data[index*8+bit].level1 = 0;
			led_data[index*8+bit].duration1 = 8;
		}
	}
	return ESP_OK;
}


esp_err_t ESP32_WS2811::set_rgb(int index, uint8_t  r, uint8_t  g, uint8_t  b)
{	
	uint32_t  color = r << 16 | g << 8 | b ;
	for (int bit = 0; bit < 24; bit++) {
		if (color & (1 << (23-bit))) {
			led_data[index*8+bit].level0 = 1;
			led_data[index*8+bit].duration0 = 8;
			led_data[index*8+bit].level1 = 0;
			led_data[index*8+bit].duration1 = 4;
		} else {
			led_data[index*8+bit].level0 = 1;
			led_data[index*8+bit].duration0 = 4;
			led_data[index*8+bit].level1 = 0;
			led_data[index*8+bit].duration1 = 8;
		}
	}
	return ESP_OK;
}


esp_err_t ESP32_WS2811::set_rgbw(int index, uint8_t  r, uint8_t  g, uint8_t  b, uint8_t  w)
{	
	uint32_t  color = r << 24 | g << 16 | b << 8 | w ;
	for (int bit = 0; bit < 32; bit++) {
		if (color & (1 << (31-bit))) {
			led_data[index*8+bit].level0 = 1;			
			led_data[index*8+bit].duration0 = 8;
			led_data[index*8+bit].level1 = 0;
			led_data[index*8+bit].duration1 = 4;
		} else {
			led_data[index*8+bit].level0 = 1;
			led_data[index*8+bit].duration0 = 4;
			led_data[index*8+bit].level1 = 0;
			led_data[index*8+bit].duration1 = 8;
		}
	}
	return ESP_OK;
}


esp_err_t ESP32_WS2811::set_led3(int index, uint8_t col[], uint8_t pwr)
{
	uint8_t  c[3];
	c[0] = col[0] * pwr / 255;
	c[1] = col[1] * pwr / 255;
	c[2] = col[2] * pwr / 255;

	return set_rgb(index, c[0], c[1], c[2]);
}


esp_err_t ESP32_WS2811::set_led4(int index, uint8_t col[], uint8_t pwr)
{
	uint8_t  c[4];
	c[0] = col[0] * pwr / 255;
	c[1] = col[1] * pwr / 255;
	c[2] = col[2] * pwr / 255;
	c[3] = col[3] * pwr / 255;

	return set_rgbw(index, c[0], c[1], c[2], c[3]);
}


esp_err_t  ESP32_WS2811::random() {
	for(int x = 0; x<ledCounts; x += 3) {
		uint32_t c = Wheel(::random(UINT8_MAX));
		setLedColorData(x, c);
	}

    return ESP_OK;
}


esp_err_t ESP32_WS2811::setAllLedsColorData(uint32_t  rgb)
{
	for (int i = 0; i < ledCounts; i += 3)
	{
		setLedColorData(i, rgb);
	}
	return ESP_OK;
}


esp_err_t ESP32_WS2811::setAllLedsColorData(uint8_t  r, uint8_t  g, uint8_t  b)
{
	for (int i = 0; i < ledCounts; i += 3)
	{
		setLedColorData(i, r, g, b);
	}
	return ESP_OK;
}


esp_err_t ESP32_WS2811::off()
{
	for(int i=0;i<ledCounts;i++)
	{
		for (int bit = 0; bit < 8; bit++) {
			led_data[i*8+bit].level0 = 1;
			led_data[i*8+bit].duration0 = 4;
			led_data[i*8+bit].level1 = 0;
			led_data[i*8+bit].duration1 = 8;
		}
	}
	realTick = rmtSetTick(rmt_send, 100);
	return ESP_OK;
}


esp_err_t ESP32_WS2811::show()
{
	return rmtWrite(rmt_send, led_data, ledCounts*8);
}


uint32_t ESP32_WS2811::Wheel(byte pos)
{
	uint32_t  WheelPos = pos % 0xff;
	if (WheelPos < 85) {
		return ((255 - WheelPos * 3) << 16) | ((WheelPos * 3) << 8);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return (((255 - WheelPos * 3) << 8) | (WheelPos * 3));
	}
	WheelPos -= 170;
	return ((WheelPos * 3) << 16 | (255 - WheelPos * 3));
}


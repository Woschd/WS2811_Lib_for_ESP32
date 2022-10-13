# WS2812 Lib for ESP32

## Beschreibung

Diese Library stammt ursprünglich von https://github.com/Freenove/Freenove_WS2812_Lib_for_ESP32.

Sie wurde verändert um in einem Bus seriell ansteuerbare RGB und RGBW Leds gemischt mit WS2811 als Portexpander ansteuern zu können.

Die LEDs sind unter Neopixel, WS2812 und WS8612 für kleines Geld zu bekommen. 
Der Baustein WS2811 hat drei regelbare Konstantstromanschlüsse für LEDs und wird fetrig auf kleinen Platinen angeboten. Das ist praktisch für Positionslichter, Bremslichter etc. Mit einem nachgeschalteten Transistor kann auch ein Motor für z.B. ein Radar angesteuert werden.

Mit einem ESP32 können bis zu 8 voneinander unabhängige Busse mit jeweils theoretisch mehreren hundert LEDs angesteuert werden. 
In einem Schiff, bei dem der vordere und hintere Teil der Aufbauten getrennt abnehmbar sind bietet es sich an, für die Beleuchtung im Rumpf und den beiden Deck Teilen jeweils einen eigenen Bus vorzusehen. So gibt es jeweils nur einen dreipoligen Stecker zu lösen.

## Beispiel

Schalten eines einzelnen Pixels

```
#include "WS2811_Lib_for_ESP32.h"

#define LEDS_COUNT     24
#define LEDS_PIN	2
#define CHANNEL		0

ESP32_WS2811 strip = ESP32_WS2811(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

void setup() {
 
  strip.begin();
  strip.show();			
  delay(5000);

  strip.set_pixel(0, 50);  						// index: 0 green  1 red  2 blue, brightness
  strip.show();
}

void loop() {
 
}
```

## Die Funktionen

Für jeden der 8 möglichen Busse gibt es eine Definition nach folgendem Muster:

```
ESP32_WS2811 strip = ESP32_WS2811(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);
```

| Parameter      | Beschreibung |
| ----------- | ----------------------------------------------------------------------------- |
| strip 		| ist die Benennung des Busses zur Unterscheidung. Z.B. Rumpf, Deck1 Deck2 etc. |
| LEDS_COUNT	| Anzahl der einezelnen LEDs. Eine RGB Led enthält drei LEDs und zählt 3, eine RGBW Led entsprechend 4 und ein WS2811 zählt 3 |
| LEDS_PIN	| der für den Bus verwendete Anschluss des ESP32. Alle Pins die als Ausgang funktionieren, können hier zugewiesen werden. |
| CHANNEL	| Nummer des verwendeten Kanals 0-7 |
| TYPE_GRB	| siehe setLedType unten, nicht für alle Funktionen benötigt |

 ---
```
strip.begin();
```
Das muss innerhalb Setup aufgerufen werden um den Kanal zu konfigurieren und alle LEDs dunkel zu schalten. 

---
```
strip.show();
```
Alle Funktionen, die die Farbe oder Helligkeit von LEDs verändern sollen, schreiben ihre Werte in den Speicher des ESP32.
Mit strip.show() wird der Speicherinhalt in die LEDs geschoben und somit das Ergebnis sichtbar. show() muss also immer auf einen oder mehrere srip.set_XXX Befehle folgen.
Der Speicherinhalt bleibt nach show() erhalten.

---
```
strip.off();
```
Im laufenden Betrieb ist das eine schnelle Methode um alles auzuschalten.

---
```
strip.set_pixel(index, x);
```
index		Nummer der einzelnen Led aus z.B. einer RGB oder RGBW Led, siehe LEDS_COUNT. Die Zählung beginnt bei 0. 
		Die Reihenfolge ist üblicherweise GRB bzw. GRBW, kann aber auch abweichen.
x		Helligkeit des Pixels 0-255

---
```
strip.set_rgb(index, r, g, b);
```
Wie set_pixel, schreibt ab index beginnend 3 LEDs. Die Reihenfolge ist üblicherweise GRB, bitte ausprobieren.

---
```
strup.set_rgbw(index, r, g, b, w);
```
Wie set_pixel, schreibt ab index beginnend 4 LEDs. Die Reihenfolge ist üblicherweise GRBW, bitte ausprobieren.

---
```
strip.set_led3(index, color, pwr);
strip.set_led4(index, color, pwr);
```
Bringt vordefinierte Farben zur Anzeige. Die Helligket wird mit pwr 0-255 festgelegt.
set_led3 für RGB und set_led4 für RGBW.

---
Farben und maximale Helligkeit werden wie folgt festgelegt:

für **RGB** LEDs
```
const uint8_t led3_red[3] =    {0, 200, 0};      // grün, rot, blau
const uint8_t led3_orange[3] = {90, 200, 0};     // grün, rot, blau
const uint8_t led3_ws[3] =     {60, 60, 50};     // grün, rot, blau
```

für **RGBW** LEDs
```
const uint8_t led4_white[4] = { 0, 50, 0, 255};  // grün, rot, blau, weiß
const uint8_t led4_blue[4] =  { 0,  0, 255, 0};  // grün, rot, blau, weiß
```

---
```
setLedType(LED_TYPE t);
```
Die Reihenfolge der verschiedenen Farben innerhalb der RGB LEDs kann bauartbedingt unterschiedlich sein.
Das kann für einige der nachfolgenden Funktionen korrigiert werden, so dass die Farben tatsächlich mit RGB gesetzt werden können.

Gültige Werte:

	TYPE_RGB
	TYPE_RBG
	TYPE_GRB
	TYPE_GBR
	TYPE_BRG
	TYPE_BGR

---
```
setBrightness(uint8_t  brightness);
```
Legt die globale Helligkeit für einige der nachfolgenden Funktionen fest.

---
```
setLedColorData(int index, uint32_t  rgb)
setLedColorData(int index, uint8_t  r, uint8_t  g, uint8_t  b)
```
Wie set_rgb, korrigiert zusätzlich die Reihenfolge der Pixel aus setLedType und berücksichtigt die Helligkeit aus setBrightness

---
```
setAllLedsColorData(uint32_t  rgb)
setAllLedsColorData(uint8_t  r, uint8_t  g, uint8_t  b)
```
Setzt für alle LEDs die gleiche Farbe und Helligkeit. Korrigiert die Reihenfolge der Pixel aus setLedType und berücksichtigt die Helligkeit aus setBrightness

---
```
random()
```
Setzt alle RGB LEDs auf eine zufällige Farbe. Korrigiert zusätzlich die Reihenfolge der Pixel aus setLedType und berücksichtigt die Helligkeit aus setBrightness

---
```
Wheel(byte pos)
```

A simple color picker.
	 i: 0-255.
<img src='extras/ColorWheel.jpg' width='100%'/>


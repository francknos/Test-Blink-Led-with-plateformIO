#ifndef DIGIT_H
#define DIGIT_H
#include <Adafruit_NeoPixel.h>

/**
 * This Class is composed of 2 digits (88) 28 leds
 * Each digit is composed of 14 Leds
 * Each bar of digit is composed od 2 leds
 * So 2*7(bar) = 14 Led 
*/

//Converter to indicate which pixels need to be showing for 7 segments digit
/* Cablage suivant
       11  10
   12           9
   13           8
        1   0
    2           7
    3           6
        4   5
*/
int converter[10][14] = {
   //0  1  2  3  4  5  6  7  8  9 10  11  12  13
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1}, //0
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,  0,  0,  0}, //1
    {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1,  1,  0,  0}, //2
    {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,  1,  0,  0}, //3
    {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0,  0,  1,  1}, //4
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1,  1,  1,  1}, //5
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,  1,  1,  1}, //6
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,  1,  0,  0}, //7
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1}, //8
    {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1}  //9
};

class Digit
{
private:
    Adafruit_NeoPixel _led;
    short _bright;
    int _numPixels;
    bool _printDizaine;

public:
    Digit(int pinLed, int nbDigits);
    ~Digit();
    void begin();
    void black(int start = 0, int nbLed = -1 /*-1 => numPixel*/);
    void printNumber(short num, uint32_t color);
    void fill(uint16_t first, uint16_t nb, uint32_t color);
    void setPixelColor(uint16_t idx, uint32_t color);

// Accesseurs
    void    setBrightness(uint8_t b) { _bright = b; _led.setBrightness(_bright); }
    uint8_t getBrigthness() { return _bright; }
    void    setPrintDizaine(bool b=true) { _printDizaine = b; }
    bool    getPrintDizaine() { return _printDizaine; }
    int     getNumPixel() { return _numPixels; }
    

    //Next function directly take from Adafuit;
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) { return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b; }
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) { return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b; }
    static uint32_t ColorHSV(uint16_t hue, uint8_t sat = 255, uint8_t val = 255) { return Adafruit_NeoPixel::ColorHSV(hue, sat, val); }
    static uint32_t gamma32(uint32_t x) { return Adafruit_NeoPixel::gamma32(x); }
    static uint8_t gamma8(uint8_t x) { return Adafruit_NeoPixel::gamma8(x); }
};

Digit::Digit(int pinLed, int numPixel)
{
    _printDizaine = true;
    _numPixels = numPixel;
    _bright = 30;
    _led = Adafruit_NeoPixel(_numPixels, pinLed, NEO_GRBW + NEO_KHZ800);
}

void Digit::begin()
{
    _led.begin();
    _led.setBrightness(_bright);
    _led.clear();
    _led.show();
}

void Digit::black(int start, int nbLed /*-1 => numPixel*/)
{
    if(nbLed<=0)
        _led.fill(0, 0, _numPixels);
    else
        _led.fill(0, start, nbLed);

    _led.show();
}

void Digit::printNumber(short num, uint32_t color)
{
    if(num>99 || num<0)
        return;

    short dizaine = num/10;
    short unitee = num%10;
    short nbPixelsDigit = _numPixels/2;

    //Unité
    for (int i = 0; i<nbPixelsDigit ;i++)
	{
		if(converter[unitee][i] == 1)
		{
			_led.setPixelColor(i, color);
		}
		else
		{
			_led.setPixelColor(i, 0);
		}
    }

    //dizaine
    if (dizaine != 0 || _printDizaine)
    {
        for (int i = nbPixelsDigit; i < _numPixels; i++)
        {
            if (converter[dizaine][i%nbPixelsDigit] == 1)
            {
                _led.setPixelColor(i, color);
            }
            else
            {
                _led.setPixelColor(i, 0);
            }
        }
    }else{
        _led.fill(0, nbPixelsDigit, nbPixelsDigit);
    }
    _led.show();
}

void Digit::fill(uint16_t first, uint16_t nb, uint32_t color)
{
    _led.fill(color, first, nb);
    _led.show();
}

void Digit::setPixelColor(uint16_t idx, uint32_t color)
{
    _led.setPixelColor(idx, color);
    _led.show();
}

Digit::~Digit()
{}

#endif // DIGIT_H

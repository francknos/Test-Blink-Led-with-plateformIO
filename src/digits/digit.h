#include <Adafruit_NeoPixel.h>


/**
 * This Class is composed of 2 digits (88) 28 leds
 * Each digit is composed of 14 Leds
 * Each bar of digit is composed od 2 leds
 * So 2*7(bar) = 14 Led 
*/

//Converter to indicate which pixels need to be showing for 7 segments digit
/* Cablage suivant
        5   4
    6           3
    7           2
        0   1
    8          13
    9          12
       10  11
*/

int converter[10][14] = {
   //0  1  2  3  4  5  6  7  8  9 10  11  12  13
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1}, //0
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,  0,  0,  0}, //1
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1,  1,  1,  1}, //2
    {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,  1,  0,  0}, //3
    {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,  0,  0,  0}, //4
    {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1,  1,  0,  0}, //5
    {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1,  1,  1,  1}, //6
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,  0,  0,  0}, //7
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1}, //8
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  0,  0}  //9
};

class Digit
{
private:
    Adafruit_NeoPixel _led;
    short _bright;
    short _numPixels;
    bool _printDizaine;

public:
    Digit(short pinLed, short nbDigits);
    ~Digit();
    void begin();
    void setBrightness(uint8_t b);
    void black(short start=0, short nbLed=-1 /*-1 => numPixel*/);
    void printNumber(short num, uint32_t color);
};

Digit::Digit(short pinLed, short numPixel)
{
    _printDizaine = true;
    _numPixels = numPixel;
    _bright = 10;
    _led = Adafruit_NeoPixel(_numPixels, pinLed, NEO_GRBW + NEO_KHZ800);
}

void Digit::begin()
{
    _led.begin();
    _led.setBrightness(_bright);
    _led.clear();
    _led.show();
}

void Digit::black(short start, short nbLed /*-1 => numPixel*/)
{
    if(nbLed<=0)
        _led.fill(0, 0, _numPixels);
    else
        _led.fill(0, start, nbLed);
}

void Digit::setBrightness(uint8_t b)
{
    _led.setBrightness(b);
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
    if (_printDizaine)
    {
        for (int i = nbPixelsDigit; i < nbPixelsDigit; i++)
        {
            if (converter[dizaine][i] == 1)
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

Digit::~Digit()
{
}

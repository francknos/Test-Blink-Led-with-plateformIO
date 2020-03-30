#include <Arduino.h>
#include "myLib/Digit.h"
#include "myLib/Time.h"

short NB_LED_HOURS 	= 14*2;
short PIN_LED_HOURS =  6;

Digit ledHours = Digit(PIN_LED_HOURS, NB_LED_HOURS);
Time time;

void testNumber();

void setup()
{
	// put your setup code here, to run once:
	pinMode(LED_BUILTIN, OUTPUT);

	ledHours.begin();
	ledHours.setPrintDizaine(false);
	time.begin();
	Serial.begin(9600);
}

void loop()
{
	if (Serial.available())
	{
		/*GetDateStuff(Year, Month, Date, DoW, Hour, Minute, Second);

		Clock.setClockMode(false); // set to 24h
		Clock.setYear(Year);
		Clock.setMonth(Month);
		Clock.setDate(Date);
		Clock.setDoW(DoW);
		Clock.setHour(Hour);
		Clock.setMinute(Minute);
		Clock.setSecond(Second);
		*/
	}
	
	if(time.available())
	{
		String s = time.timeToString();
		/*double temp = Clock.getTemperature();
		Serial.print("Température: ");
		Serial.println(temp);
		Serial.println("");*/
		delay(1000);
	}else{
		// Pas de capteur RTC
		Serial.println("Capteur DS3231 is not avalible.");
		testNumber();
	}
}

void testNumber()
{
	int pause = 150;
		int max = 100;

		// Rouge
		for (int i = 0; i<max; i++)
		{
			ledHours.printNumber(i, Digit::Color(255, 0, 0) );
			delay(pause);
		}
		ledHours.black();
		delay(500);

		// Vert
		for (int i = 0; i<max; i++)
		{
			ledHours.printNumber(i, Digit::Color(0, 255, 0) );
			delay(pause/2);
		}
		ledHours.black();
		delay(pause);

		// bleu
		for (int i = 0; i<max; i++)
		{
			ledHours.printNumber(i, Digit::Color(255, 0, 180) );
			delay(pause/2);
		}
		ledHours.black();
		delay(pause);

		// BLANC
		for (int i = 0; i<max; i++)
		{
			ledHours.printNumber(i, Digit::Color(0, 0, 0, 255) );
			delay(pause / 2);
		}
		ledHours.black();
		delay(pause);

		//chenillard
		for (int i = 0; i < ledHours.getNumPixel(); i++)
		{
			ledHours.setPixelColor(i, Digit::Color(200, 40, 80));
			delay(pause/2);
		}
		for (int i = ledHours.getNumPixel()-1; i >=0; i--)
		{
			ledHours.setPixelColor(i,0);
			delay(pause/4);
		}

		for (int i = 0; i < ledHours.getNumPixel(); i++)
		{
			ledHours.setPixelColor(i, Digit::Color(40, 200, 80));
			delay(pause/4);
		}
		for (int i = ledHours.getNumPixel()-1; i >=0; i--)
		{
			ledHours.setPixelColor(i,0);
			delay(pause/6);
		}

		for (int i = 0; i < ledHours.getNumPixel(); i++)
		{
			ledHours.setPixelColor(i, Digit::Color(40, 80, 200));
			delay(pause/6);
		}
		for (int i = ledHours.getNumPixel()-1; i >=0; i--)
		{
			ledHours.setPixelColor(i,0);
			delay(pause/8);
		}
}

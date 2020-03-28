#include <Arduino.h>
#include <DS3231.h>
#include "digits/digit.h"

DS3231 Clock;

short NB_LED_HOURS 	= 14*2;
short PIN_LED_HOURS =  6;

Digit ledHours = Digit(PIN_LED_HOURS, NB_LED_HOURS);

byte Year;
byte Month;
byte Date;
byte DoW;
byte Hour;
byte Minute;
byte Second;


void GetDateStuff(byte &Year, byte &Month, byte &Day, byte &DoW,
				  byte &Hour, byte &Minute, byte &Second){
	// Call this if you notice something coming in on
	// the serial port. The stuff coming in should be in
	// the order YYMMDDwHHMMSS, with an 'x' at the end.
	boolean GotString = false;
	char InChar;
	byte Temp1, Temp2;
	char InString[20];

	byte j = 0;
	while (!GotString)
	{
		if (Serial.available())
		{
			InChar = Serial.read();
			InString[j] = InChar;
			j += 1;
			if (InChar == 'x')
			{
				GotString = true;
			}
		}
	}
	Serial.println(InString);
	// Read Year first
	Temp1 = (byte)InString[0] - 48;
	Temp2 = (byte)InString[1] - 48;
	Year = Temp1 * 10 + Temp2;
	// now month
	Temp1 = (byte)InString[2] - 48;
	Temp2 = (byte)InString[3] - 48;
	Month = Temp1 * 10 + Temp2;
	// now date
	Temp1 = (byte)InString[4] - 48;
	Temp2 = (byte)InString[5] - 48;
	Day = Temp1 * 10 + Temp2;
	// now Day of Week
	DoW = (byte)InString[6] - 48;
	// now Hour
	Temp1 = (byte)InString[7] - 48;
	Temp2 = (byte)InString[8] - 48;
	Hour = Temp1 * 10 + Temp2;
	// now Minute
	Temp1 = (byte)InString[9] - 48;
	Temp2 = (byte)InString[10] - 48;
	Minute = Temp1 * 10 + Temp2;
	// now Second
	Temp1 = (byte)InString[11] - 48;
	Temp2 = (byte)InString[12] - 48;
	Second = Temp1 * 10 + Temp2;
}

void printDateTime(){
	String listOfDays[] = {"indice 0", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
	String listOfMonth[] = {"indice 0", "Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

	// Refresh Date Hour
	DoW = Clock.getDoW();
	Date = Clock.getDate();
	Month = Clock.getMonth();
	Year = Clock.getYear();
	Hour = Clock.getHour();
	Minute = Clock.getMinute();
	Second = Clock.getSecond();

	Serial.print(listOfDays[DoW]);
	Serial.print(" ");
	Serial.print(DoW);
	Serial.print(" ");
	Serial.print(listOfMonth[Month]);
	Serial.print(" 20");
	Serial.print(Year);
	Serial.print(" <> ");

	Serial.print(Hour);
	Serial.print("H ");
	Serial.print(Minute);
	Serial.print("M ");
	Serial.print(Second);
	Serial.print("s - [");

	Serial.print(Date);
	Serial.print("/");
	Serial.print(Month);
	Serial.print("/");
	Serial.print(Year);
	Serial.println("]");
}

void setup()
{
	// put your setup code here, to run once:
	pinMode(LED_BUILTIN, OUTPUT);

	ledHours.begin();
	ledHours.setPrintDizaine(false);
	Serial.begin(9600);
	Clock.begin();
}

void loop()
{
	if (Serial.available())
	{
		GetDateStuff(Year, Month, Date, DoW, Hour, Minute, Second);

		Clock.setClockMode(false); // set to 24h
		Clock.setYear(Year);
		Clock.setMonth(Month);
		Clock.setDate(Date);
		Clock.setDoW(DoW);
		Clock.setHour(Hour);
		Clock.setMinute(Minute);
		Clock.setSecond(Second);
	}

	delay(1000);
	
	if(Clock.available())
	{
		printDateTime();
		double temp = Clock.getTemperature();
		Serial.print("Température: ");
		Serial.println(temp);
		Serial.println("");
	}else{
		// Pas de capteur RTC
		Serial.println("Capteur DS3231 is not avalible.");
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
}

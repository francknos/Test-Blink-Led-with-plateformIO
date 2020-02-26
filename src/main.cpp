#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <DS3231.h>

unsigned int cpt = 0;
DS3231 Clock;

bool century = false;
bool am_pm = false, h12 = false;

byte Year;
byte Month;
byte Date;
byte DoW;
byte Hour;
byte Minute;
byte Second;

void GetDateStuff(byte &Year, byte &Month, byte &Day, byte &DoW,
				  byte &Hour, byte &Minute, byte &Second)
{
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

void printDateTime()
{
	bool b;
	Serial.print(Clock.getHour());
	Serial.print("H ");
	Serial.print(Clock.getMinute());
	Serial.print("M ");
	Serial.print(Clock.getSecond());
	Serial.print("s - ");
	Serial.print(Clock.getDate());
	Serial.print("/");
	Serial.print(Clock.getMonth(b));
	Serial.print("/");
	Serial.println(Clock.getYear());
}

void setup()
{
	// put your setup code here, to run once:
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(9600);
	Wire.begin();
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
	
	if (Clock.available())
	{
		printDateTime();

		Serial.print("Température: ");
		Serial.println(Clock.getTemperature());
		Serial.println("");
	}else{
		Serial.println("Capteur DS3231 is not avalible.");
	}
}

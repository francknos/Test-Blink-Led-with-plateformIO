#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <DS3231.h>

unsigned int cpt = 0;
DS3231 Clock;

short NB_LED_BANDEAU 	= 14;
short PIN_LED_HOURS 	=  6;
Adafruit_NeoPixel ledBandeau = Adafruit_NeoPixel(NB_LED_BANDEAU, PIN_LED_HOURS, NEO_GRBW + NEO_KHZ800);

void printNumber(int num, uint32_t couleur);
void black();

byte Year;
byte Month;
byte Date;
byte DoW;
byte Hour;
byte Minute;
byte Second;

//					   0 1 2 3 4 5 6 7 8 9 10 11 12 13	
int number[10][14] = {{0,0,1,1,1,1,1,1,1,1, 1, 1, 1, 1},//0
					  {0,0,0,0,0,0,1,1,1,1, 0, 0, 0, 0},//1
					  {1,1,0,0,1,1,1,1,0,0, 1, 1, 1, 1},//2
					  {1,1,0,0,1,1,1,1,1,1, 1, 1, 0, 0},//3
					  {1,1,1,1,0,0,1,1,1,1, 0, 0, 0, 0},//4
					  {1,1,1,1,1,1,0,0,1,1, 1, 1, 0, 0},//5
					  {1,1,1,1,1,1,0,0,1,1, 1, 1, 1, 1},//6
					  {0,0,0,0,1,1,1,1,1,1, 0, 0, 0, 0},//7
					  {1,1,1,1,1,1,1,1,1,1, 1, 1, 1, 1},//8
					  {1,1,1,1,1,1,1,1,1,1, 1, 1, 0, 0} //9
					  };

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

	ledBandeau.begin();
	ledBandeau.setBrightness(40);
	ledBandeau.clear();
	ledBandeau.show();

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

		ledBandeau.clear();
		for(int i=0 ; i<(int)ledBandeau.numPixels() ; i++)
		{
			if(temp> (i*0.25+21))
				ledBandeau.setPixelColor(i, i*(255/8), (7-i)*(255/8) , 0);
			else
				ledBandeau.setPixelColor(i, 0);	
		}
		ledBandeau.show();

		Serial.print("Température: ");
		Serial.println(temp);
		Serial.println("");
	}else{

		// Pas de capteur RTC
		Serial.println("Capteur DS3231 is not avalible.");

		int pause = 100;
		// Rouge
		for (int i = 0; i<10; i++)
		{
			printNumber(i, ledBandeau.Color(255,0,0));
			delay(pause);
		}
		black();
		delay(500);

		// Vert
		for (int i = 0; i<10; i++)
		{
			printNumber(i, ledBandeau.Color(0,255,0));
			delay(pause);
		}
		black();
		delay(500);

		// bleu
		for (int i = 0; i<10; i++)
		{
			printNumber(i, ledBandeau.Color(0,0,255));
			delay(pause);
		}
		black();
		delay(500);

		// BLANC
		for (int i = 0; i<10; i++)
		{
			printNumber(i, ledBandeau.Color(0,0,0,255));
			delay(pause);
		}
		black();
	}
}


void black()
{
	ledBandeau.fill(0, 0, ledBandeau.numPixels());
	ledBandeau.show();
}
void printNumber(int num, uint32_t couleur)
{

	if (num < 0 || num > 9)
		return;

	for (int i = 0; i < ledBandeau.numPixels(); i++)
	{
		if (number[num][i] == 1)
		{
			ledBandeau.setPixelColor(i, couleur);
		}
		else
		{
			ledBandeau.setPixelColor(i, 0);
		}
	}
	ledBandeau.show();
}

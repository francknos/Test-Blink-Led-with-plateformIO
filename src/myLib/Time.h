#ifndef TIME_H
#define TIME_H

#include <DS3231.h>

class Time
{
public:
    DS3231 _clock;
    byte _year;
    byte _month;
    byte _day;
    byte _DoW;
    byte _hour;
    byte _minute;
    byte _second;

public:
    Time();
    ~Time();
    void begin();
    String timeToString(bool print = false);

    //recall basic function
    bool available() { return _clock.available(); }
};

Time::Time()
{
}

Time::~Time(){}

void Time::begin(){
    _clock.begin();
}

String Time::timeToString(bool print)
{
    String listOfDays[] = {"indice 0", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
	String listOfMonth[] = {"indice 0", "Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};
    String out = "";

	// Refresh Date Hour
	_DoW = _clock.getDoW();
	_day = _clock.getDate();
	_month = _clock.getMonth();
	_year = _clock.getYear();
	_hour = _clock.getHour();
	_minute = _clock.getMinute();
	_second = _clock.getSecond();

    out.concat(listOfDays[_DoW]);
	out.concat(" ");
	out.concat(_DoW);
	out.concat(" ");
	out.concat(listOfMonth[_month]);
	out.concat(" 20");
	out.concat(_year);
	out.concat(" <> ");

	out.concat(_hour);
	out.concat("H ");
	out.concat(_minute);
	out.concat("M ");
	out.concat(_second);
	out.concat("s - [");

	out.concat(_day);
	out.concat("/");
    out.concat(_month);
    out.concat("/");
    out.concat(_year);
    out.concat("]");

    if (print == false)
        return out;

    Serial.print(listOfDays[_DoW]);
    Serial.print(" ");
    Serial.print(_DoW);
    Serial.print(" ");
    Serial.print(listOfMonth[_month]);
    Serial.print(" 20");
    Serial.print(_year);
    Serial.print(" <> ");

    Serial.print(_hour);
    Serial.print("H ");
    Serial.print(_minute);
    Serial.print("M ");
    Serial.print(_second);
    Serial.print("s - [");

    Serial.print(_day);
    Serial.print("/");
    Serial.print(_month);
    Serial.print("/");
    Serial.print(_year);
    Serial.println("]");

    return out;
}





/**
 * 
 * to set time
 * void GetDateStuff(byte &Year, byte &Month, byte &Day, byte &DoW,
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
 * 
 * 
 * 
 * 
 */
 
 #endif // TIME_H
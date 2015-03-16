
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

void setup () 
{
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
    // Se l'ora e' errata la aggiorna 
    // con quella del computer
    DateTime OraRTC = RTC.now();
    DateTime OraPC = DateTime(__DATE__, __TIME__);
    if (OraRTC.unixtime() < OraPC.unixtime())
       Serial.println("L'RTC e' indietro! Lo aggiorno con quello del PC!");
    RTC.adjust(OraPC);
    if (! RTC.isrunning())
        Serial.println("RTC is NOT running!");
}

void printShortDateTime(DateTime now)
{
  char buffer[25]={'\0'};
  sprintf(buffer, "%02u%02u%u_%02u%02u%02u", 
                  now.year(),now.month(),now.day(),
                  now.hour(), now.minute(), now.second());
  Serial.println(buffer);
}

void printLongDateTime(DateTime now)
{
   const char* days[] =  {"Lunedi'", "Martedi'", "Mercoledi'", 
                           "Giovedi'", "Venerdi'", "Sabato",  "Domenica" };
   const char* months[] = { "Gennaio", "Febbraio", "Marzo", "Aprile", 
                            "Maggio", "Giugno", "Luglio", "Agosto",
                            "Settembre", "Ottobre", "Novembre", "Dicembre"};
  char buffer[40];

  sprintf(buffer, "%s, %u %s %u %02u:%02u:%02u", 
                  days[now.dayOfWeek()-1], now.day(), months[now.month()-1],now.year(),
                  now.hour(), now.minute(), now.second());
  Serial.println(buffer);
}

void loop () 
{
    printLongDateTime(RTC.now());
    printShortDateTime(RTC.now());
    delay(1000);
}

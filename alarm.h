#ifndef Alarm_H_INCLUDED
#define Alarm_H_INCLUDED

#include "definition.h"
List *initializeAlarmList(Alarm *anAlarm);
void displayAnAlarm(Alarm *anAlarm);
void displayAlarms(List *AlarmList);
List *saveAlarm(List *AlarmList, Alarm *anAlarm);
List *deleteAlarm(List *AlarmList, int ID);
List *searchAlarmID(List *AlarmList, int ID);
struct tm * getTime ();
void delay(unsigned int mseconds);
void displayMagic();
void closeMagic();
#endif // Alarm_H_INCLUDED

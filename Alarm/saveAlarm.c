#include <stdio.h>
#include <stdlib.h>
#include "definition.h"

List *saveAlarm(List *AlarmList, Alarm *anAlarm)
{
        Alarm *newAlarm =malloc(sizeof(*newAlarm));

        strcpy(newAlarm->alarmName,anAlarm->alarmName);
        newAlarm->day=anAlarm->day;
        newAlarm->hour=anAlarm->hour;
        newAlarm->min=anAlarm->min;
        strcpy(newAlarm->musicName,anAlarm->musicName);
        newAlarm->enabled=anAlarm->enabled;
        newAlarm->running=anAlarm->running;
        newAlarm->beamy_id=anAlarm->beamy_id;
        newAlarm->alarm_id=anAlarm->alarm_id;
        newAlarm->next=AlarmList->first;
        AlarmList->first=newAlarm;
        return AlarmList;
}
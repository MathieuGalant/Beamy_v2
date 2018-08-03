#include <stdio.h>
#include <stdlib.h>
#include "definition.h"

List *initializeAlarmList(Alarm *anAlarm)
{
    List *AlarmList=malloc(sizeof(*AlarmList));
    Alarm *newAlarm=malloc(sizeof(*anAlarm));


    if (AlarmList==NULL || anAlarm == NULL)
        {
        exit(EXIT_FAILURE);
        }

    strcpy(newAlarm->alarmName,anAlarm->alarmName);
    newAlarm->day=anAlarm->day;
    newAlarm->hour=anAlarm->hour;
    newAlarm->min=anAlarm->min;
    strcpy(newAlarm->musicName,anAlarm->musicName);
    newAlarm->enabled=anAlarm->enabled;
    newAlarm->running=anAlarm->running;
    newAlarm->beamy_id=anAlarm->beamy_id;
    newAlarm->alarm_id=anAlarm->alarm_id;
    newAlarm->next=NULL;


    AlarmList->first=newAlarm;


    return AlarmList;
}
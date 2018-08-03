#include <stdio.h>
#include <stdlib.h>
#include "definition.h"

List *searchAlarmID(List *AlarmList, int ID, int numberOfAlarm)
{
    Alarm *tmp=AlarmList->first;

    while(tmp!=NULL )
    {
        if(tmp->alarm_id == ID)
        {
            AlarmList=deleteAlarm(AlarmList,ID);
        }
        else
        {
            numberOfAlarm++;
        }
        tmp=tmp->next;
    }
    return AlarmList;
}
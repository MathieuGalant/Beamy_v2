#include <stdio.h>
#include <stdlib.h>
#include "definition.h"

List *deleteAlarm(List *AlarmList, int ID)
{
    Alarm *tmp=AlarmList->first;
    Alarm *modif;

    if(tmp->next==NULL)
    {
        AlarmList->first=NULL;
        return AlarmList;
    }
    while(tmp!=NULL)
    {
        if(tmp->alarm_id == ID)
        {
            modif->next=tmp->next;
        }
        else
        {
            modif->next=tmp;
        }
        tmp=tmp->next;
    }
    AlarmList->first=modif;

    return AlarmList;
}
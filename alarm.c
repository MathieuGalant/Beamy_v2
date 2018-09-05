
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void displayAlarms(List *AlarmList)
{
    printf("\n Alarms :\n");
    Alarm *current=AlarmList->first;

    while (current!=NULL )
    {
            printf("Alarm name : %s \n",current->alarmName);
            printf("Day : %d \n",current->day);
            printf("Hour : %d \n",current->hour);
            printf("Minutes : %d \n",current->min);
            printf("Music name : %s \n",current->musicName);
            printf("Enabled : %d \n",current->enabled);
            printf("Running : %d \n",current->running);
            printf("Beamy ID : %d \n ",current->beamy_id);
            printf("Alarm ID : %d \n \n",current->alarm_id);
            current =current->next;
    }

}

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
        //printf("new Alarm added");

        newAlarm->next=AlarmList->first;
        AlarmList->first=newAlarm;
        return AlarmList;


}

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








struct tm * getTime ()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
 // printf ( "The current date/time is: %s", asctime (timeinfo) );

  return timeinfo;
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void displayMagic()
{
    pid_t pid=fork();
    if (pid==0)
    { /* child process */
        system("cd ~/MagicMirror/ && pm2 start mm.sh");

        exit(127); /* only if execv fails */
    }
    system("cd ~/Desktop/beamy/button/");
}

void closeMagic()
{
    system("cd ~/MagicMirror/ && pm2 stop all");
}

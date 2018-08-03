#include <stdlib.h>
#include <stdio.h>

void getAlarmServer(int ID, char *alarmFile, char *token)
{
    char alarmServer[200];
    printf("ok");
    sprintf(alarmServer,"curl -o %s -X GET \"http://localhost:8000/api/alarm/%d/?token=%s\"",alarmFile,ID,token);
    printf("%s\n",alarmServer);
    system(alarmServer);
}
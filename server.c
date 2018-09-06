#include <time.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "definition.h"

void getTokenServer(char *tokenFile)
{
    char tokenServer[100];
    printf("ok");
    sprintf(tokenServer,"curl -o %s -X GET \"10.237.104.63:8000/api/auth/?username=pi&password=raspberry&imei=1234\"",tokenFile);
    printf("%s\n",tokenServer);
    pid_t pid=fork();
    if (pid==0)
    { /* child process */
        system(tokenServer);
        exit(127); /* only if execv fails */
    }
}

void getAlarmServer(int ID, char *alarmFile, char *token)
{
    char alarmServer[200];
    printf("ok");
    sprintf(alarmServer,"curl -o %s -X GET \"10.237.104.63:8000/api/alarm/%d/?token=%s\"",alarmFile,ID,token);
    printf("%s\n",alarmServer);
    system(alarmServer);
}


void getMusicFilesServer(int ID, char *musicFile, char *token) // need update
{
    char musicServer[200];
    printf("ok");
    sprintf(musicServer,"curl -o %s -X GET \"10.237.104.63:8000/api/files/song/%d/?token=%s\"",musicFile,ID,token);
    printf("%s\n",musicServer);
    system(musicServer);
}

void getVideoFilesServer(int ID, char *videoFile, char *token) // need update
{
    char videoServer[200];
    printf("ok");
    sprintf(videoServer,"curl -o %s -X GET \"10.237.104.63:8000/api/files/video/%d/?token=%s\"",videoFile,ID,token);
    printf("%s\n",videoServer);
    system(videoServer);
}

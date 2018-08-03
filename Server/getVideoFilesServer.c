#include <stdlib.h>
#include <stdio.h>

void getVideoFilesServer(int ID, char *videoFile, char *token) 
{
    char videoServer[200];
    printf("ok");
    sprintf(videoServer,"curl -o %s -X GET \"http://localhost:8000/api/files/video/%d/?token=%s\"",videoFile,ID,token);
    printf("%s\n",videoServer);
    system(videoServer);
}
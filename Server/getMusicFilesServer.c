#include <stdlib.h>
#include <stdio.h>

void getMusicFilesServer(int ID, char *musicFile, char *token) 
{
    char musicServer[200];
    printf("ok");
    sprintf(musicServer,"curl -o %s -X GET \"http://localhost:8000/api/files/song/%d/?token=%s\"",musicFile,ID,token);
    printf("%s\n",musicServer);
    system(musicServer);
}
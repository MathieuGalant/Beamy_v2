#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <stdlib.h>
#include <stdio.h>

void playVideo(char *videoFolder,char videoName[])
{
    char *videoPlaying;
    sprintf(videoPlaying,"omxplayer --win \"1000 500 1920 1080\" %s/%s",videoFolder,videoName);
    printf("%s\n",videoPlaying);
    pid_t pid=fork();
    if (pid==0)
    { /* child process */
        system(videoPlaying);
        exit(127); /* only if execv fails */
    }
}
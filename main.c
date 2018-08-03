#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include <fmod.h>
#include <dirent.h>
#include "xml.h"
#include "command.h"
#include "alarm.h"
#include "definition.h"
#include "video.h"
#include <curl/curl.h>
#include "server.h"


int getPositionMusic(char name[],char *musicName[20]);
void getFolderFiles(char *foldername,char *musicName[]);




int main(int argc, char **argv)
{

    int musicNumber=20;
    char *musicFolder="media/music";
    char *videoFolder="media/video";
    char *alarmFolder="alarm";
    char *addAlarmFile="XML/addAlarm.xml";
    char *commandFile= "XML/command.xml";
    char *commandMusicFile="XML/commandMusic.xml";
    char *commandAlarmFile="XML/commandAlarm.xml";
    char *commandVideoFile="XML/commandVideo.xml";
    char *commandMagicFile="XML/magic.xml";
    char *alarmFile="XML/alarm.xml";
    char *musicFile="XML/music.xml";
    char *videoFile="XML/video.xml";
    char *tokenFile="XML/token.xml";
    char *musicNames[20]={"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};
    char *addAlarm[2]={"0","0"};
    char *command[3]={"0","0","0"};
    char *commandVideo[2]={"0","0"};
    char *commandMusic[2]={"0","0"};
    char *commandAlarm[2]={"0","0"};
    char *commandMagic[2]={"0","0"};

    char musicPlaying[50];
    char name[50];
    char alarmPlaying[50];
    char videoName[50];
    int continuer=1;
    char token[50];

    int numberOfAlarm=0;
    Alarm *anAlarm;
    List *alarmList=NULL;
    Alarm *searchAlarm=NULL;
    struct tm * timeinfo;

    clock_t time_1;
    clock_t time_2;
    time_1=clock();

    FMOD_SYSTEM *syst;
    FMOD_CHANNEL *channel = 0;
    FMOD_RESULT resultat;
    void *extradriverdata = 0;
    FMOD_CREATESOUNDEXINFO exinfo;

           /* Create a System object and initialize.*/

    FMOD_System_Create(&syst);
    FMOD_System_Init(syst, 32, FMOD_INIT_NORMAL, extradriverdata);

        /* Increase the file buffer size a little bit to account for Internet lag. */

    FMOD_System_SetStreamBufferSize(syst,64*1024, FMOD_TIMEUNIT_RAWBYTES);

    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.filebuffersize = 1024*16;


    float volume=0.5;
    FMOD_SOUND *music;


    getTokenServer(tokenFile);
    readTokenXmlFile(tokenFile,token);


    int action=0;
    int actionMusic=0;
    int actionVideo=0;
    int actionAlarm=0;
    int onetime=0;
    int playingMusic=0;
    int playingVideo=0;
    int playingAlarm=0;
    int showingMagic=0;
    int musicPosition=0;
    while (continuer)
    {
        FMOD_System_Update(syst);

        readXmlFile(commandFile,command);
        strcpy(name,command[1]);
        action=returnAction(command);

        time_2=clock();
        timeinfo=getTime();

        if((float)(time_2-time_1)/CLOCKS_PER_SEC>60) // get xml alarm from the server every minute
        {
            getAlarmServer(1,alarmFile,token);
            time_1=clock();
            printf("ok\n");
        }

        readXmlFile(addAlarmFile, addAlarm); //read the addAlarm XML
        if (strcmp(addAlarm[0],"1")==0) // check if someone is adding an alarm
        {
            readAlarmXmlFile(alarmFile,anAlarm);
            if(numberOfAlarm==0)
            {
                alarmList=initializeAlarmList(anAlarm);
                numberOfAlarm++;
                modifyXml(addAlarmFile);
                displayAlarms(alarmList);
            }
            else
            {
                alarmList=searchAlarmID(alarmList,anAlarm->alarm_id);
                displayAlarms(alarmList);

                alarmList=saveAlarm(alarmList,anAlarm);
                displayAlarms(alarmList);
                printf("%d\n",numberOfAlarm);
                modifyXml(addAlarmFile);
            }
        }


        if (numberOfAlarm >0)
        {
            Alarm *current=alarmList->first;
            while (current!=NULL)
            {

                if (timeinfo->tm_wday==current->day && timeinfo->tm_hour==current->hour && timeinfo->tm_min==current->min && timeinfo->tm_sec<5 && playingAlarm==0)
                {
                    FMOD_Sound_Release(music);
                    sprintf(alarmPlaying,"%s/%s",musicFolder,current->musicName);
                    printf("%s\n",alarmPlaying);
                    resultat=FMOD_System_CreateStream(syst, alarmPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);
                    if (resultat != FMOD_OK)
                        {
                        fprintf(stderr, "Cannot read the mp3 file\n");
                        exit(EXIT_FAILURE);
                        }
                    FMOD_Channel_SetVolume(channel, volume);
                    FMOD_System_PlaySound(syst,  music, 0, 0, &channel);
                    playingAlarm=1;
                }
                current =current->next;
            }
        }
        switch(action)
        {
            case 1: //play music
                {
                FMOD_Sound_Release(music);
                sprintf(musicPlaying,"%s/%s",musicFolder,name);
                printf("%s",musicPlaying);
                resultat=FMOD_System_CreateStream(syst, musicPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);
                if (resultat != FMOD_OK)
                    {
                    fprintf(stderr, "Cannot read the mp3 file\n");
                    exit(EXIT_FAILURE);
                    }
                FMOD_Channel_SetVolume(channel, volume);
                FMOD_System_PlaySound(syst,  music, 0, 0, &channel);
                modifyXml(commandFile);
                playingMusic=1;
                break;
                }
            case 2: //play random music
                {
                FMOD_Sound_Release(music);
                srand(time(NULL));
                int r = rand()%musicNumber;
                getFolderFiles(musicFolder,musicNames);
                sprintf(musicPlaying,"%s/%s",musicFolder,musicNames[r]);
                resultat=FMOD_System_CreateStream(syst, musicPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);
                if (resultat != FMOD_OK)
                    {
                    fprintf(stderr, "Cannot read the mp3 file\n");
                    exit(EXIT_FAILURE);
                    }
                FMOD_Channel_SetVolume(channel, volume);
                FMOD_System_PlaySound(syst,  music, 0, 0, &channel);
                modifyXml(commandFile);
                playingMusic=1;
                break;
                }
            case 3 : //play video
                {
                printf("%s  %s\n",command[0],command[1]);
                strcpy(videoName,name);
                playVideo(videoFolder,videoName);
                playingVideo=1;
                modifyXml(commandFile);
                break;
                }
        }
        if (playingMusic==1) // check if an music is playing
        {
            readXmlFile(commandMusicFile,commandMusic); // read the command music XML
            actionMusic=returnMusicAction(commandMusic); // return an action base on what is on the XML music
            switch(actionMusic)
            {
                case 1: // quit the music
                    {
                    FMOD_Sound_Release(music);
                    playingMusic = 0;
                    modifyXml(commandMusicFile);
                    break;
                    }
                case 2: // pause the music
                    {
                    resultat=FMOD_Channel_SetPaused(channel, 1);
                    if (resultat != FMOD_OK)
                        {
                        fprintf(stderr, "Cannot pause file\n");
                        }
                    modifyXml(commandMusicFile);
                    break;
                    }
                case 3: // continue the music
                    {
                    FMOD_Channel_SetPaused(channel, 0);
                    modifyXml(commandMusicFile);
                    break;
                    }

                case 4: // make the music louder
                    {
                    volume=volume +0.01;
                    resultat=FMOD_Channel_SetVolume(channel, volume);
                    if (resultat != FMOD_OK)
                    {
                        printf( "pas de changement de volume");
                    }
                    else
                    {
                        printf("plus fort");
                    }
                    modifyXml(commandMusicFile);
                    break;
                    }
                case 5: // make the music quieter
                    {
                    volume=volume -0.01;
                    resultat=FMOD_Channel_SetVolume(channel, volume);
                    if (resultat != FMOD_OK)
                    {
                        printf( "pas de changement de volume");
                    }
                    else
                    {
                        printf("moins fort");
                    }
                    modifyXml(commandMusicFile);
                    break;
                    }
                case 6: //next music
                    {
                    FMOD_Sound_Release(music);
                    getFolderFiles(musicFolder,musicNames);
                    musicPosition=getPositionMusic(name, musicNames);
                    sprintf(musicPlaying,"%s/%s",musicFolder,musicNames[musicPosition+1]);
                    printf("%s",musicPlaying);
                    resultat=FMOD_System_CreateStream(syst, musicPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);

                    if (resultat != FMOD_OK)
                    {
                    fprintf(stderr, "Cannot read the mp3 file\n");
                    exit(EXIT_FAILURE);
                    }

                    FMOD_Channel_SetVolume(channel, volume);
                    FMOD_System_PlaySound(syst,  music, 0, 0, &channel);
                    modifyXml(commandFile);
                    playingMusic=1;
                    break;

                    }
                case 7: //previous music
                    {
                    FMOD_Sound_Release(music);
                    getFolderFiles(musicFolder,musicNames);
                    musicPosition=getPositionMusic(name, musicNames);
                    sprintf(musicPlaying,"%s/%s",musicFolder,musicNames[musicPosition-1]);
                    printf("%s",musicPlaying);
                    resultat=FMOD_System_CreateStream(syst, musicPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);

                    if (resultat != FMOD_OK)
                        {
                        fprintf(stderr, "Cannot read the mp3 file\n");
                        exit(EXIT_FAILURE);
                        }
                    FMOD_Channel_SetVolume(channel, volume);
                    FMOD_System_PlaySound(syst,  music, 0, 0, &channel);
                    modifyXml(commandFile);
                    playingMusic=1;
                    break;
                    }
            }
        }
        if(playingVideo==1) // check if a video is playing
        {
            readXmlFile(commandVideoFile,commandVideo);
            actionVideo=returnVideoAction(commandVideo);
            switch(actionVideo)
            {
                case 1: // quit the video
                    {
                    stopVideo();
                    modifyXml(commandVideoFile);
                    playingVideo=0;
                    break;
                    }
                case 2: // pause the video
                    {
                    pauseVideo();
                    modifyXml(commandVideoFile);
                    break;
                    }
                case 3: // continue the video
                    {
                    continueVideo();
                    modifyXml(commandVideoFile);
                    break;
                    }
                case 4: // make the video louder
                    {
                    upVolumeVideo();
                    modifyXml(commandVideoFile);
                    break;
                    }
                case 5: // make the video quieter
                    {
                    downVolumeVideo();
                    modifyXml(commandVideoFile);
                    break;
                    }
            }

        }
        if(playingAlarm==1) // check if an alarm is ringing
        {
            readXmlFile(commandAlarmFile,commandAlarm);
            actionAlarm=returnAlarmAction(commandAlarm);
            switch(actionAlarm)
            {
                case 1: // stop the alarm
                    {
                    FMOD_Sound_Release(music);
                    displayMagic();
                    modifyXml(commandAlarmFile);
                    playingAlarm=0;
                    break;
                    }

                case 2: // snooze the alarm
                    {
                    FMOD_Sound_Release(music);
                    modifyXml(commandAlarmFile);
                    playingAlarm=0;
                    break;
                    }
            }
        }
        if(showingMagic==1) // check if an magic is ringing
        {
            readXmlFile(commandMagicFile,commandMagic);
            if (strcmp(commandMagic[0], "quit") == 0)
                {
                closeMagic();
                modifyXml(commandMagicFile);
                }
        }
    }
    FMOD_Sound_Release(music);
    FMOD_System_Close(syst);
    FMOD_System_Release(syst);
    return EXIT_SUCCESS;
}



void getFolderFiles(char *folderName, char *musicName[20])
{
    int i=0;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (folderName)) != NULL)
    {
    /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
            {
            // printf ("%s\n", ent->d_name);
            musicName[i]=ent->d_name;
            i++;
            }
        closedir (dir);
    }
    else
    {
  /* could not open directory */
        perror ("");
    }
}





int getPositionMusic(char name[],char *musicName[20])
{
    int i=0;
    for (i=0;i<=20;i++)
    {
        if(strcmp(name,musicName[i])==0)
            return i;
    }
    printf("Coulnd't find the music");
}


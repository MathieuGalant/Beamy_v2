#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

void getAlarmServer(int ID, char *alarmFile, char *token);
void getMusicFilesServer(int ID, char *musicFile, char *token);
void getVideoFilesServer(int ID, char *videoFile, char *token);
void getTokenServer(char *tokenFile);

#endif // SERVER_H_INCLUDED

#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <stdlib.h>
#include <stdio.h>


void getTokenServer(char *tokenFile)
{
    char tokenServer[100];
    printf("ok");
    sprintf(tokenServer,"curl -o %s -X GET \"localhost:8000/api/auth/?username=pi&password=raspberry&imei=1234\"",tokenFile);
    printf("%s\n",tokenServer);
    pid_t pid=fork();
    if (pid==0)
    { /* child process */
        system(tokenServer);
        exit(127); /* only if execv fails */
    }
}
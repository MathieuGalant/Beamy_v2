#include <stdio.h>
#include <string.h>

char changeBool(char aBool[20])
{
    int action;

    if (strcmp(aBool, "false") == 0)
        {
            action = 0;
        }
    else if (strcmp(aBool, "true") == 0)
        {
            action = 1;
        }
    return action;
}
#include <stdio.h>
#include <string.h>

int changeDay(char day[20])
{
    int action;

    if (strcmp(day, "monday") == 0)
        {
            action = 1;
        }
    else if (strcmp(day, "tuesday") == 0)
        {
            action = 2;
        }
    else if (strcmp(day, "wednesday") == 0)
        {
            action = 3;
        }
    else if (strcmp(day, "thursday") == 0)
        {
            action = 4;
        }
    else if (strcmp(day, "friday") == 0)
        {
            action = 5;
        }
    else if (strcmp(day, "saturday") == 0)
        {
            action = 6;
        }
    else if (strcmp(day, "sunday") == 0)
        {
            action = 0;
        }
    return action;
}

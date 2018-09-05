#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

typedef int bool;
#define true 1
#define false 0

typedef enum {SUNDAY,MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY} weekday;
typedef struct Alarm Alarm;
typedef struct List List;


struct Alarm
{
    char alarmName[30];
    weekday day;
    int hour;
    int min;
    char musicName[30];
    bool running;
    bool enabled;
    int beamy_id;
    int alarm_id;
    Alarm *next;
};

struct List
{
    Alarm *first;
};


#endif // DEFINITION_H_INCLUDED

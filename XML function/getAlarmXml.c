#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include "xml.h"

void getAlarmXml(xmlNode * node, Alarm *anAlarm)
{
    char *ptr;
    int ret;
    char day[20];
    int i=1;

    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
            if (is_leaf(node))
            {
                switch(i)
                {
                    case 1:
                        printf("%d!",i);
                        strcpy(anAlarm->alarmName,xmlNodeGetContent(node));
                        i++;
                        break;
                    case 2:
                        printf("%d!",i);
                        ret = strtol(xmlNodeGetContent(node), &ptr, 10);
                        anAlarm->alarm_id=ret;
                        i++;
                        break;
                    case 3:
                        ret = strtol(xmlNodeGetContent(node), &ptr, 10);
                        anAlarm->beamy_id=ret;
                        i++;
                        break;
                    case 4:
                        ret=changeDay(xmlNodeGetContent(node));
                        anAlarm->day=ret;
                        i++;
                        break;
                    case 5:
                        ret = strtol(xmlNodeGetContent(node), &ptr, 10);
                        anAlarm->hour=ret;
                        i++;
                        break;
                    case 6:
                        ret = strtol(xmlNodeGetContent(node), &ptr, 10);
                        anAlarm->min=ret;
                        node = node->parent;
                        i++;
                        break;
                    case 7:
                        ret = changeBool(xmlNodeGetContent(node));
                        anAlarm->enabled=ret;
                        i++;
                        break;
                    case 8:
                        ret = changeBool(xmlNodeGetContent(node));
                        anAlarm->running=ret;
                        i++;
                        break;
                    case 9:
                        strcpy(anAlarm->musicName,xmlNodeGetContent(node));
                        break;
                }
                node = node->next;
            }
            else
            {
                node=node->children;
            }
        node = node->next;
        }
    }
}
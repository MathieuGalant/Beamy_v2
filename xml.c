#include <time.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <dirent.h>
#include "definition.h"
#include <stdlib.h>


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

int is_leaf(xmlNode * node)
{
    xmlNode * child = node->children;
    while(child)
    {
        if(child->type == XML_ELEMENT_NODE) return 0;
        child = child->next;
    }
    return 1;
}


void getXml(xmlNode * node,int i,  char *attribut[])
{
    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
      //    printf("%c%s:%s\n", '-', node->name, is_leaf(node)?xmlNodeGetContent(node):xmlGetProp(node, "id"));
            if (is_leaf(node))
            {
                attribut[i]=xmlNodeGetContent(node);
                i++;
            }
        }
        getXml(node->children,i, attribut);
        node = node->next;
    }
}

void readXmlFile(char *filename,  char * attribut[])
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;


    doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL)
    {
        printf("Could not parse the XML file");
    }

    root_element = xmlDocGetRootElement(doc);

    getXml(root_element,0,attribut);

    xmlFreeDoc(doc);

    xmlCleanupParser();


}







void modifyXml(char * filename)
{
    xmlDoc *doc = xmlParseFile(filename);
    xmlNode *root_element = NULL;
    xmlNode * node=NULL;
    root_element = xmlDocGetRootElement(doc);
    node=root_element->children;
    node=node->next;
  //  printf("%s",xmlNodeGetContent(node));
    xmlNodeSetContent(node, (xmlChar*)"0");
    xmlSaveFileEnc(filename, doc, "UTF-8");
}

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
           // printf("%c%s:%s\n", '-', node->name, is_leaf(node)?xmlNodeGetContent(node):xmlGetProp(node, "id"));

            if (is_leaf(node))
            {

                printf("%d:",i);
                printf("%s\n",xmlNodeGetContent(node));

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




void readAlarmXmlFile(char *filename, Alarm *anAlarm)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL)
    {
        printf("Could not parse the XML file");
    }

    root_element = xmlDocGetRootElement(doc);

    getAlarmXml(root_element,anAlarm);

    xmlFreeDoc(doc);

    xmlCleanupParser();

}




char *getTokenXml(xmlNode * node, char *token)
{

    char ret[50];
    int i=1;

    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
           // printf("%c%s:%s\n", '-', node->name, is_leaf(node)?xmlNodeGetContent(node):xmlGetProp(node, "id"));

            if (is_leaf(node))
            {
                printf("%d:",i);
                printf("%s\n",xmlNodeGetContent(node));

                if(i==5)
                {
                    strcpy(token,xmlNodeGetContent(node));
                    return token;
                }
                else
                {
                    i++;
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

char *readTokenXmlFile(char *filename,char *token)
{

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL)
    {
        printf("Could not parse the XML file");
    }

    root_element = xmlDocGetRootElement(doc);

    getTokenXml(root_element,token);

    xmlFreeDoc(doc);

    xmlCleanupParser();

    return token;

}

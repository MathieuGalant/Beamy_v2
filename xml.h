#ifndef XML_H_INCLUDED
#define XML_H_INCLUDED

#include "definition.h"
int changeDay(char day[20]);
void readXmlFile(char *filename,char *attribut[]);
void getXml(xmlNode * node, int i,char *attribut[]);
int is_leaf(xmlNode * node);

void modifyXml(char * filename);

void readAlarmXmlFile(char *filename, struct Alarm *anAlarm);
void getAlarmXml(xmlNode * node,  struct Alarm *anAlarm);


char *getTokenXml(xmlNode * node, char *token);
char *readTokenXmlFile(char *filename,char *token);
#endif // XML_H_INCLUDED

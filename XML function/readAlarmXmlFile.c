#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include "xml.h"

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
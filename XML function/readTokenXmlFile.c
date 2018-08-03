#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include "xml.h"

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
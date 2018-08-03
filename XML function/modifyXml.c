#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include "xml.h"

void modifyXml(char * filename)
{
    xmlDoc *doc = xmlParseFile(filename);
    xmlNode *root_element = NULL;
    xmlNode * node=NULL;
    root_element = xmlDocGetRootElement(doc);
    node=root_element->children;
    node=node->next;
    xmlNodeSetContent(node, (xmlChar*)"0");
    xmlSaveFileEnc(filename, doc, "UTF-8");
}
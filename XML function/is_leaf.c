#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include "xml.h"

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

#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include "xml.h"

void getXml(xmlNode * node,int i,  char *attribut[])
{
    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
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
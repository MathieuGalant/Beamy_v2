#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include "xml.h"

char *getTokenXml(xmlNode * node, char *token)
{
    char ret[50];
    int i=1;
    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
            if (is_leaf(node))
            {
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
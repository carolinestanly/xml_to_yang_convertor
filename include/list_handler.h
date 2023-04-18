#ifndef LIST_HANDLER_H
#define LIST_HANDLER_H

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <utilities.h>

// Serialize the list node and its children recursively
void serializeContainer(xmlNode *node, int depth, FILE *yang_file, GHashTable *printed_elements);

#endif // LIST_HANDLER_H
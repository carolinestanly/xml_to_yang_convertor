#ifndef CONTAINER_HANDLER_H
#define CONTAINER_HANDLER_H

#include <libxml/parser.h>
#include <libxml/tree.h>

// Serialize the container node and its children recursively
void serializeContainer(xmlNode *node, int depth, FILE *yang_file, GHashTable *printed_elements);

#endif // CONTAINER_HANDLER_H
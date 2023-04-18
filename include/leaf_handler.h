#ifndef LEAF_HANDLER_H
#define LEAF_HANDLER_H

#include <libxml/parser.h>
#include <libxml/tree.h>

// Serialize the leaf node and its children recursively 
void serializeLeaf(xmlNode *node, int depth, FILE *yang_file);

#endif // ATTRS_HANDLER_H
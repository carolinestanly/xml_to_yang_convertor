#ifndef ATTRS_HANDLER_H
#define ATTRS_HANDLER_H

#include <libxml/parser.h>
#include <libxml/tree.h>

// serializes the attributes of a node
void serializeAttrs(xmlAttr *attributes, int depth, FILE *yang_file);

//serializes the name of an attribute
void serializeAttrName(xmlAttr *attr, int depth, FILE *yang_file);

// serializes the type of an attribute
void serializeAttrType(xmlAttr *attr, int depth, FILE *yang_file);

#endif // ATTRS_HANDLER_H
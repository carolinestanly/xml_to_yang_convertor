#include "attrs_handler.h"

/*********************************************************************************************
 * @function serializeAttrs                                                                  *
 * @description Serializes a list of XML attributes in YANG format and writes it to a file.  *
 * @param attributes Pointer to an xmlAttr structure representing a list of XML attributes.  *
 * @param depth The depth of the current XML element in the hierarchy.                       *
 * @param yang_file Pointer to the FILE structure where the output will be written.          *
 * @output None (The serialized YANG format will be written to the provided file.)           *
 ********************************************************************************************/

void serializeAttrs(xmlAttr *attributes, int depth, FILE *yang_file)
{
  for (xmlAttr *attr = attributes; attr; attr = attr->next)
  {
    //Serialize the attribute's name and type in YANG format and write it to the file. 
    serializeAttrName(attr, depth, yang_file);
    serializeAttrType(attr, depth, yang_file);
  }
}

/***********************************************************************************************
 * @function serializeAttrName                                                                 *
 * @description Writes the attribute's name in YANG format with proper indentation to a file.  *
 * @param attr Pointer to an xmlAttr structure representing an XML attribute.                  *
 * @param depth The depth of the current XML element in the hierarchy.                         *
 * @param yang_file Pointer to the FILE structure where the output will be written.            *
 * @output None (The attribute's name in YANG format will be written to the provided file.)    *
 ***********************************************************************************************/

void serializeAttrName(xmlAttr *attr, int depth, FILE *yang_file)
{
  for (int i = 0; i < depth + 1; ++i)
  {
    fprintf(yang_file, " ");
  }
  fprintf(yang_file, "attribute %s {\n", attr->name);
}

/**************************************************************************************************************************************
 * @function serializeAttrType                                                                                                        *
 * @description Writes the attribute's type in YANG format with proper indentation to a file and closes the attribute's block.        *
 * @param attr Pointer to an xmlAttr structure representing an XML attribute.                                                         *
 * @param depth The depth of the current XML element in the hierarchy.                                                                *
 * @param yang_file Pointer to the FILE structure where the output will be written.                                                   *
 * @output None (The attribute's type in YANG format will be written to the provided file and the attribute's block will be closed.)  *
 **************************************************************************************************************************************/

void serializeAttrType(xmlAttr *attr, int depth, FILE *yang_file)
{
  for (int i = 0; i < depth + 2; ++i)
  {
    fprintf(yang_file, " ");
  }
  fprintf(yang_file, "type %s;\n", attr->children->content);
  for (int i = 0; i < depth + 1; ++i)
  {
    fprintf(yang_file, " ");
  }
  fprintf(yang_file, "}\n");
}
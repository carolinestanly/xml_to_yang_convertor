#include "utilities.h"



/****************************************************************************************
 * Function Name: get_number_type                                                       *
 * Description: Determine the data type and range of a given XML content string.        *
 *                                                                                      *
 * This function takes an XML content string and returns a TypeRange structure          *
 * containing the appropriate data type, range, and length. It analyzes the string      *
 * to identify whether it represents a signed or unsigned integer, a floating-point     *
 * number, or a string.                                                                 *
 *                                                                                      *
 * @param content A pointer to the xmlChar content of the XML node.                     *
 * @return A TypeRange structure containing the determined type, range, and length.     *
 *                                                                                      *
 ***************************************************************************************/
TypeRange get_number_type(const xmlChar *content)
{
  bool is_signed = false;
  bool is_float = false;
  int decimal_places = 0;
  int digits = 0;
  int length = 0;

  const xmlChar *p = content;

  while (*p)
  {
    switch (*p)
    {
    case PLUS_SIGN:
    case MINUS_SIGN:
      is_signed = true;
      break;
    case DOT:
      is_float = true;
      decimal_places = -1;
      break;
    default:
      if (isdigit(*p))
      {
        digits++;
        decimal_places++;
      }
      else
      {
        length++;
      }
      break;
    }
    p++;
  }

  TypeRange result;

  if (length > 0)
  {
    result.type = STRING_TYPE;
    char length_str[STRING_LENGTH];
    snprintf(length_str, sizeof(length_str), "length 1..%d", length);
    result.length = strdup(length_str);
    result.range = EMPTY_STRING;
  }
  else if (is_float)
  {
    if (decimal_places <= FLT_DECIMAL_DIG)
    {
      result.type = FLOAT_TYPE;
      result.range = FLOAT_RANGE;
      result.length = EMPTY_STRING;
    }
    else if (decimal_places <= DECIMAL_DIG_7)
    {
      result.type = DECIMAL32;
      result.range = EMPTY_STRING;
      result.length = EMPTY_STRING;
    }
    else if (decimal_places <= DECIMAL_DIG_16)
    {
      result.type = DECIMAL64;
      result.range = EMPTY_STRING;
      result.length = EMPTY_STRING;
    }
    else
    {
      result.type = DECIMAL128;
      result.range = EMPTY_STRING;
      result.length = EMPTY_STRING;
    }
  }
  else
  {
    if (is_signed)
    {
      if (digits <= DECIMAL_DIG_2)
      {
        result.type = INT8;
        result.range = INT8_RANGE;
      }
      else if (digits <= DECIMAL_DIG_4)
      {
        result.type = INT16;
        result.range = INT16_RANGE;
      }
      else if (digits <= DECIMAL_DIG_9)
      {
        result.type = INT32;
        result.range = INT32_RANGE;
      }
      else
      {
        result.type = INT64;
        result.range = INT64_RANGE;
      }
    }
    else
    {
      if (digits <= DECIMAL_DIG_2)
      {
        result.type = UINT8;
        result.range = UINT8_RANGE;
      }
      else if (digits <= DECIMAL_DIG_4)
      {
        result.type = UINT16;
        result.range = UINT16_RANGE;
      }
      else if (digits <= DECIMAL_DIG_9)
      {
        result.type = UINT32;
        result.range = UINT32_RANGE;
      }
      else
      {
        result.type = UINT64;
        result.range = UINT64_RANGE;
      }
      result.length = EMPTY_STRING;
    }
  }

  return result;
}

/******************************************************************************************
 * Function Name: is_list_element                                                         *
 * Description: Check if the given XML node represents a list element.                    *
 *                                                                                        *
 * This function checks if the given XML node is a list element by looking at             *
 * the node's siblings. If the node has a sibling with the same name, it is               *
 * considered a list element.                                                             *
 *                                                                                        *
 * @param node A pointer to the XML node to be checked.                                   *
 * @return A boolean value indicating whether the given node represents a list element.   *
 *                                                                                        *
 *****************************************************************************************/

bool is_list_element(xmlNode *node)
{
  if (node == NULL)
    return false;

  xmlNode *sibling = node->next;
  while (sibling != NULL)
  {
    if (sibling->type == XML_ELEMENT_NODE)
    {
      if (xmlStrEqual(node->name, sibling->name))
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    sibling = sibling->next;
  }

  return false;
}
/*******************************************************************************************
 * Function Name: find_first_child_element                                                 *
 * Description: Find the first child element of the given XML node.                        *
 *                                                                                         *
 * This function takes an XML node and returns the first child element node.               *
 * If no child element is found, NULL is returned.                                         *
 *                                                                                         *
 * @param node A pointer to the XML node whose first child element is to be found.         *
 * @return A pointer to the first child element node, or NULL if not found.                *
 *                                                                                         *
 * Sample Input: Pointer to an XML node with child elements                                *
 * Sample Output: Pointer to the first child element node                                  *
 ******************************************************************************************/

xmlNode *find_first_child_element(xmlNode *node)
{
  xmlNode *child = node->children;
  while (child != NULL)
  {
    if (child->type == XML_ELEMENT_NODE)
    {
      return child;
    }
    child = child->next;
  }

  /* if we reach this point, we did not find a child element */
  return NULL;
}

/*****************************************************************************************************************
 * Function Name: exportXmlToYang                                                                                *
 * Description: Print the XML element names in the YANG format.                                                  *
 *                                                                                                               *
 * This function takes an XML node, a depth, a GHashTable, and a yang_file pointer                               *
 * as arguments. It iterates through the XML elements and prints them in the YANG                                *
 * format with the specified indentation depth. The printed_elements GHashTable is                               *
 * used to track the elements that have already been printed to avoid duplication.                               *
 *                                                                                                               *
 * @param node A pointer to the XML node to start printing from.                                                 *
 * @param depth The indentation depth                                                                            *
 * @param depth The indentation depth for the element printing.                                                  *
 * @param printed_elements A pointer to a GHashTable containing the elements that have already been printed.     *
 * @param yang_file A pointer to the output FILE.                                                                *
 ****************************************************************************************************************/

void exportXmlToYang(xmlNode *node, int depth, GHashTable *printed_elements, FILE *yang_file)
{
  for (xmlNode *cur_node = node; cur_node; cur_node = cur_node->next)
  {
    if (cur_node->type == XML_ELEMENT_NODE)
    {
      gchar *element_name = (gchar *)cur_node->name;
      if (g_hash_table_contains(printed_elements, element_name))
      {
        continue;
      }
      bool is_list = is_list_element(cur_node);

      if (xmlChildElementCount(cur_node) > 0)
      {
        if (is_list)
        {
          serializeList(cur_node, depth, yang_file, printed_elements);
        }
        else
        {
          serializeContainer(cur_node, depth, yang_file, printed_elements);
        }

        serializeAttrs(cur_node->properties, depth, yang_file);

        exportXmlToYang(cur_node->children, depth + 1, printed_elements, yang_file);

        for (int i = 0; i < depth; ++i)
        {
          fprintf(yang_file, " ");
        }
        fprintf(yang_file, "}\n");

        g_hash_table_add(printed_elements, g_strdup(element_name));
      }
      else
      {
        serializeLeaf(cur_node, depth, yang_file);
        serializeAttrs(cur_node->properties, depth, yang_file);
        for (int i = 0; i < depth; ++i)
        {
          fprintf(yang_file, " ");
        }
        fprintf(yang_file, "}\n");
      }
    }
  }
}

/****************************************************************
 * @function read_config                                        *
 * @description A function to read the configuration file.      *
 *                                                              *
 * @param config_filename The name of the configuration file.   *
 * @param module_name The name of the module.                   *
 * @param namespace The namespace of the module.                *
 * @param prefix The prefix of the module.                      *
 * @param revision The revision of the module.                  *
 ***************************************************************/

void read_config(const char *config_filename, char *module_name, char *namespace, char *prefix, char *revision)
{
  FILE *fp = fopen(config_filename, "r");

  if (fp == NULL)
  {
    fprintf(stderr, "Failed to open the config file: %s\n", config_filename);
    exit(1);
  }

  fscanf(fp, "name = %s\n", module_name);
  fscanf(fp, "namespace = %[^\n]\n", namespace);
  fscanf(fp, "prefix = %s\n", prefix);
  fscanf(fp, "revision = %s", revision);

  fclose(fp);
}
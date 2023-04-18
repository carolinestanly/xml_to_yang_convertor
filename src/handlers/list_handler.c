#include "list_handler.h"

/**************************************************************************************************************
 * @function serializeList                                                                                    *
 * @description Serializes an XML list node in YANG format and writes it to a file.                           *
 * @param node Pointer to an xmlNode structure representing the XML list node.                                *
 * @param depth The depth of the current XML element in the hierarchy.                                        *
 * @param yang_file Pointer to the FILE structure where the output will be written.                           *
 * @param printed_elements A GHashTable containing the names of the elements that have already been printed.  *
 * @return void This function does not return a value.                                                        *
 **************************************************************************************************************/
void serializeList(xmlNode *node, int depth, FILE *yang_file, GHashTable *printed_elements)
{
  // Check if the element has already been printed
  gchar *element_name = (gchar *)node->name;
  if (g_hash_table_contains(printed_elements, element_name))
  {
    return;
  }
  g_hash_table_add(printed_elements, g_strdup(element_name));

  // Print the list name
  for (int i = 0; i < depth; ++i)
  {
    fprintf(yang_file, " ");
  }
  fprintf(yang_file, "list %s {\n", node->name);

  // Print the key for the list
  xmlNode *first_child_element = find_first_child_element(node);
  if (first_child_element != NULL)
  {
    for (int i = 0; i < depth + 1; ++i)
    {
      fprintf(yang_file, " ");
    }
    fprintf(yang_file, "key \"%s\";\n", first_child_element->name);
  }
}
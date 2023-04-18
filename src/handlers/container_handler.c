#include "utilities.h"
#include "container_handler.h"

/**************************************************************************************************
 * @function serializeContainer                                                                   *
 * @description Serializes an XML container node in YANG format and writes it to a file.          *
 *                                                                                                *
 * @param node Pointer to an xmlNode structure representing the XML container node.               *
 * @param depth The depth of the current XML element in the hierarchy.                            *
 * @param yang_file Pointer to the FILE structure where the output will be written.               *
 * @param printed_elements A GHashTable of element names that have already been serialized.       *
 * @output None (The serialized container in YANG format will be written to the provided file.)   *
 *************************************************************************************************/

void serializeContainer(xmlNode *node, int depth, FILE *yang_file, GHashTable *printed_elements)
{
  gchar *element_name = (gchar *)node->name;
  // Check if the container has already been encountered
  if (g_hash_table_contains(printed_elements, element_name))
  {
    return;
  }
  // Add the container to the list of encountered containers
  g_hash_table_add(printed_elements, g_strdup(element_name));

  // Indent the container definition
  for (int i = 0; i < depth; ++i)
  {
    fprintf(yang_file, " ");
  }
  // Write the container definition
  fprintf(yang_file, "container %s {\n", node->name);
}
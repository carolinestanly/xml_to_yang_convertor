#include "../include/hash_table.h"

#include "../include/utilities.h"

/*******************************************************************************************
 * @function main                                                                          *
 * @description The main function of the XML to YANG converter program.                    *
 *                                                                                         *
 * This main function takes command line arguments for the input XML file and the output   *
 * YANG file. It reads the XML file, converts it to a YANG format, and writes the          *
 * result to the output file. The function returns an integer exit code (0 for success,    *
 * non-zero for failure).                                                                  *
 *                                                                                         *
 * @param argc The number of command line arguments.                                       *
 * @param argv An array of pointers to the command line argument strings.                  *
 * @return An integer exit code (0 for success, non-zero for failure).                     *
 *******************************************************************************************/
int main(int argc, char **argv)
{

  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <XML file> <YANG file>\n", argv[0]);
    return 1;
  }

  const char *xml_filename = argv[1];
  const char *yang_filename = argv[2];

  xmlDocPtr doc = xmlReadFile(xml_filename, NULL, 0);
  if (!doc)
  {
    fprintf(stderr, "Failed to parse the XML file: %s\n", xml_filename);
    return 1;
  }

  FILE *yang_file = fopen(yang_filename, "w");
  if (!yang_file)
  {
    fprintf(stderr, "Failed to open the YANG file for writing: %s\n", yang_filename);
    return 1;
  }

  xmlNode *root_element = xmlDocGetRootElement(doc);

  char module_name[256], namespace[256], prefix[256], revision[256];
  read_config("config.cfg", module_name, namespace, prefix, revision);

  // Print the header of the YANG file
  fprintf(yang_file, "module %s {\n", module_name);
  fprintf(yang_file, "  namespace \"%s\";\n", namespace);
  fprintf(yang_file, "  prefix %s;\n", prefix);
  fprintf(yang_file, "\trevision %s {\n    description \"Added a new feature to the module.\";\n\t}\n", revision);

  // We keep a hash table of all the elements that have already been printed.
  // This is so that we don't print the same element more than once.
  GHashTable *printed_elements = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
  exportXmlToYang(root_element, 1, printed_elements, yang_file);

  fprintf(yang_file, "}\n");
  fclose(yang_file);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  g_hash_table_destroy(printed_elements);

  return 0;
}
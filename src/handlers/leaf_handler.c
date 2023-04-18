#include "leaf_handler.h"
#include "utilities.h"

/***************************************************************************************
 * @function serializeLeaf                                                             *
 * @description Serializes an XML leaf node in YANG format and writes it to a file.    *
 *                                                                                     *
 * @param node Pointer to an xmlNode structure representing the XML leaf node.         *
 * @param depth The depth of the current XML element in the hierarchy.                 *
 * @param yang_file Pointer to the FILE structure where the output will be written.    *
 * @return void This function does not return a value.                                 *
 **************************************************************************************/

void serializeLeaf(xmlNode *node, int depth, FILE *yang_file)
{
    for (int i = 0; i < depth; ++i)
    {
        fprintf(yang_file, " ");
    }

    // print the name of the node
    fprintf(yang_file, "leaf %s {\n", node->name);

    // get the content of the node
    xmlChar *content = xmlNodeGetContent(node);
    if (content)
    {
        // check the type of the node
        TypeRange tr = get_number_type(content);

        for (int i = 0; i < depth + 1; ++i)
        {
            fprintf(yang_file, " ");
        }

        // print the type of the node
        fprintf(yang_file, "type %s {\n", tr.type);

        // print the range of the node
        if (strlen(tr.range) > 0)
        {
            for (int i = 0; i < depth + 1; ++i)
            {
                fprintf(yang_file, " ");
            }
            fprintf(yang_file, "%s;\n", tr.range);
        }

        // print the length of the node
        if (strlen(tr.length) > 0)
        {
            for (int i = 0; i < depth + 1; ++i)
            {
                fprintf(yang_file, " ");
            }
            fprintf(yang_file, "%s;\n", tr.length);
            free((void *)tr.length);
        }

        for (int i = 0; i < depth + 1; ++i)
        {
            fprintf(yang_file, " ");
        }

        fprintf(yang_file, "}\n");
        for (int i = 0; i < depth + 1; ++i)
        {
            fprintf(yang_file, " ");
        }
        fprintf(yang_file, "description \"This object belongs to %s\";\n", node->name);
    }
}

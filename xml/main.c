#include <stdio.h>
#include <stdbool.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void parseTree(xmlNodePtr, int);
void formatLevel(int, bool);

// struct tree {

// }

int main(int argc, char *argv[])
{
    LIBXML_TEST_VERSION

    if (argc >= 2)
    {
        char *filename = argv[1]; // The file to be parsed will be passed as the first parameter to the program call

        xmlDocPtr doc; // An XML document
        doc = xmlReadFile(filename, NULL, 0);

        // Error Handling
        if (doc == NULL) // If I don't have a file at this point, and error occured
        {
            fprintf(stderr, "Failed to load/parse %s\n", filename);
            return -1; // Exit code: -1 (Error: Failed to load/parse the file)
        }

        // The document is ready to be used
        xmlNodePtr root = xmlDocGetRootElement(doc); // Get the root element
        parseTree(root, 0);                          // Recursively traverses the tree, printing out node names and attributes along the way

        // Frees memory used by library while loading an XML document
        xmlFreeDoc(doc);
    }

    // Cleanup function for the XML library.
    xmlCleanupParser();

    return 0; // Exit code 0 (No Errors)
}

void parseTree(xmlNodePtr root, int level)
{
    for (xmlNodePtr n = root; n; n = n->next) // Iterate through all the children nodes
    {
        if (n->type == XML_ELEMENT_NODE) // Parse a node only if it is an elemet node
        {
            formatLevel(level, false);
            printf("%s\n", n->name);
            // if (n->properties) // If the node has any properties
            // {
            //     for (xmlAttrPtr attr = n->properties; attr; attr = attr->next) // Iterate through all the node's attributes (properties)
            //     {
            //         printf("  %s = %s\n", attr->name, attr->children->content);
            //     }
            // }
            if (n->children)
                parseTree(n->children, level + 1); // Recursion
        }
        // if (n->type == XML_TEXT_NODE)
        // {
        //     printf("  %s", n->content);
        // }
    }
}

void formatLevel(int level, bool lastChild)
{
    if (level == 0)
        printf("/--");
    else
    {
        for (int i = 0; i < level; i++)
        {
            printf("   %c", lastChild == true ? '\\' : '|');
        }

        printf("---");
    }
}
#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_12(char* data, int size) {
  xmlInitParser();
  xmlDoc* null79 = NULL;
  xmlFreeDoc(null79);
  traffic_assert(true);
  xmlNode* null182 = NULL;
  char* var229 = xmlNodeGetContent(null182);
  traffic_assert(true);
  xmlParserInputBuffer* null292 = NULL;
  xmlTextReader* var307 = xmlNewTextReader(null292, var229);
  traffic_assert(true);
  traffic_assert(true);
}
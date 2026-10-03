#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_10(char* data, int size) {
  xmlInitParser();
  xmlDoc* null79 = NULL;
  xmlFreeDoc(null79);
  traffic_assert(true);
  xmlTextReader* null218 = NULL;
  xmlFreeTextReader(null218);
  traffic_assert(true);
  xmlTextReader* null303 = NULL;
  int var306 = xmlTextReaderIsEmptyElement(null303);
  traffic_assert(true);
  xmlNode* var384 = xmlDocGetRootElement(null79);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_2(char* data, int size) {
  int const25 = 1;
  xmlParserInputBuffer* var35 = xmlParserInputBufferCreateStatic(data, size, const25);
  traffic_assert(true);
  char* null39 = NULL;
  xmlDoc* var68 = xmlNewDoc(null39);
  traffic_assert(true);
  if (!((var68 == NULL))) {
    traffic_assert(true);
    xmlFreeDoc(var68);
  }
}
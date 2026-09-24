#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  int const25 = 1;
  xmlParserInputBuffer* var35 = xmlParserInputBufferCreateStatic(data, size, const25);
  traffic_assert(true);
  xmlInitParser();
  traffic_assert(true);
  if (!((var35 == NULL))) {
    traffic_assert(true);
    char* null97 = NULL;
    xmlTextReader* var105 = xmlNewTextReader(var35, null97);
  }
}
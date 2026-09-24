#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  int const61 = 1;
  xmlParserInputBuffer* var71 = xmlParserInputBufferCreateStatic(data, size, const61);
  traffic_assert(true);
  char* null75 = NULL;
  xmlDoc* var104 = xmlNewDoc(null75);
  traffic_assert(true);
}
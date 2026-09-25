#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  char* null1 = NULL;
  xmlDoc* var34 = xmlNewDoc(null1);
  traffic_assert(true);
  int const60 = 1;
  xmlParserInputBuffer* var70 = xmlParserInputBufferCreateStatic(data, size, const60);
  traffic_assert(true);
  xmlInitParser();
  traffic_assert(true);
  xmlParserCtxt* var133 = xmlNewParserCtxt();
}
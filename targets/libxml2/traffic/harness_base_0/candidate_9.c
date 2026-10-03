#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_9(char* data, int size) {
  xmlInitParser();
  char* null129 = NULL;
  int const132 = 0;
  xmlParserInputBuffer* var152 = xmlParserInputBufferCreateStatic(null129, size, const132);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
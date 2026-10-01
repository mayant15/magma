#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_5(char* data, int size) {
  xmlTextReader* null65 = NULL;
  xmlFreeTextReader(null65);
  traffic_assert(true);
  int const133 = 0;
  xmlParserInputBuffer* var153 = xmlParserInputBufferCreateStatic(data, size, const133);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var233 = xmlTextReaderNodeType(null65);
  traffic_assert(true);
}
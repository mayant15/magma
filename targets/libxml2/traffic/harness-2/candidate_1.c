#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  int const24 = 1;
  xmlParserInputBuffer* var34 = xmlParserInputBufferCreateStatic(data, size, const24);
  traffic_assert(true);
  char* null37 = NULL;
  xmlDoc* var66 = xmlNewDoc(null37);
  traffic_assert(true);
}
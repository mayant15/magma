#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlDoc* null21 = NULL;
  xmlNode* var76 = xmlDocGetRootElement(null21);
  traffic_assert(true);
  xmlNode* null101 = NULL;
  int var154 = xmlChildElementCount(null101);
  traffic_assert(true);
  bool var232 = xmlNodeIsText(null101);
  traffic_assert(true);
  xmlParserInputBuffer* var310 = xmlParserInputBufferCreateStatic(data, var154, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
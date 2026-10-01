#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_4(char* data, int size) {
  xmlParserCtxt* null39 = NULL;
  xmlFreeParserCtxt(null39);
  traffic_assert(true);
  xmlParserInputBuffer* null136 = NULL;
  xmlFreeParserInputBuffer(null136);
  traffic_assert(true);
  xmlNode* null167 = NULL;
  xmlNode* null169 = NULL;
  xmlNode* var230 = xmlAddChild(null167, null169);
  traffic_assert(true);
  traffic_assert(true);
  int const289 = -1;
  xmlParserInputBuffer* var309 = xmlParserInputBufferCreateStatic(data, size, const289);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserInputBuffer* var389 = xmlParserInputBufferCreateStatic(data, const289, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
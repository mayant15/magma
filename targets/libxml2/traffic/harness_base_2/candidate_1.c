#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlUnlinkNode(null19);
  traffic_assert(true);
  xmlParserCtxt* null116 = NULL;
  xmlFreeParserCtxt(null116);
  traffic_assert(true);
  xmlTextReader* null229 = NULL;
  char* var230 = xmlTextReaderConstName(null229);
  traffic_assert(true);
  bool var308 = xmlIsBlankNode(null19);
  traffic_assert(true);
  xmlParserInputBuffer* null369 = NULL;
  xmlFreeParserInputBuffer(null369);
  traffic_assert(true);
  int const443 = 1;
  xmlParserInputBuffer* var463 = xmlParserInputBufferCreateStatic(data, size, const443);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
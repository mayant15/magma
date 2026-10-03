#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_3(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlUnlinkNode(null19);
  traffic_assert(true);
  xmlParserCtxt* var153 = xmlNewParserCtxt();
  int const210 = -1;
  xmlParserInputBuffer* var230 = xmlParserInputBufferCreateStatic(data, size, const210);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlFreeParserInputBuffer(var230);
  traffic_assert(true);
  char out353_slot; char* out353 = &out353_slot;
  char out359_slot; char* out359 = &out359_slot;
  xmlDoc* var387 = xmlCtxtReadMemory(var153, out353, const210, data, out359, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
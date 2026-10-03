#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_4(char* data, int size) {
  xmlInitParser();
  xmlDoc* null79 = NULL;
  xmlFreeDoc(null79);
  traffic_assert(true);
  xmlTextReader* null218 = NULL;
  xmlFreeTextReader(null218);
  traffic_assert(true);
  xmlNode* null247 = NULL;
  xmlFreeNode(null247);
  traffic_assert(true);
  xmlNode out333_slot; xmlNode* out333 = &out333_slot;
  bool var383 = xmlIsBlankNode(out333);
  traffic_assert(true);
  xmlParserInputBuffer* null444 = NULL;
  xmlFreeParserInputBuffer(null444);
  traffic_assert(true);
  int const516 = 0;
  xmlParserInputBuffer* var538 = xmlParserInputBufferCreateStatic(data, const516, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserCtxt* null581 = NULL;
  xmlFreeParserCtxt(null581);
  traffic_assert(true);
  xmlUnlinkNode(null247);
  traffic_assert(true);
  int const752 = 0;
  xmlParserInputBuffer* var772 = xmlParserInputBufferCreateStatic(data, size, const752);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlFreeParserInputBuffer(var538);
  traffic_assert(true);
}
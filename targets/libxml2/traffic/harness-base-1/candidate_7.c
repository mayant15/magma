#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_7(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlFreeNode(null19);
  traffic_assert(true);
  xmlNode out95_slot; xmlNode* out95 = &out95_slot;
  xmlNode* var157 = xmlAddChild(null19, out95);
  traffic_assert(true);
  traffic_assert(true);
  char* null215 = NULL;
  int const218 = 0;
  xmlParserInputBuffer* var238 = xmlParserInputBufferCreateStatic(null215, size, const218);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  bool var320 = xmlIsBlankNode(null19);
  traffic_assert(true);
}
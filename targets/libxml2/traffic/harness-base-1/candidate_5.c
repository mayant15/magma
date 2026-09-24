#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_5(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlFreeNode(null19);
  traffic_assert(true);
  xmlParserCtxt* null120 = NULL;
  xmlFreeParserCtxt(null120);
  traffic_assert(true);
  bool var236 = xmlNodeIsText(null19);
  traffic_assert(true);
  xmlNode out268_slot; xmlNode* out268 = &out268_slot;
  char* var316 = xmlNodeGetContent(out268);
  traffic_assert(true);
  xmlNode* var396 = xmlAddChild(out268, null19);
  traffic_assert(true);
  traffic_assert(true);
  xmlNode* null430 = NULL;
  char* var477 = xmlNodeGetContent(null430);
  traffic_assert(true);
}
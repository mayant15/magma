#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_2(char* data, int size) {
  xmlInitParser();
  xmlTextReader* null141 = NULL;
  xmlFreeTextReader(null141);
  traffic_assert(true);
  int var229 = xmlTextReaderRead(null141);
  traffic_assert(true);
  xmlParserInputBuffer* null290 = NULL;
  xmlFreeParserInputBuffer(null290);
  traffic_assert(true);
  xmlDoc* null329 = NULL;
  xmlNode* var384 = xmlDocGetRootElement(null329);
  traffic_assert(true);
  xmlNode* null405 = NULL;
  xmlUnlinkNode(null405);
  traffic_assert(true);
  xmlNode out487_slot; xmlNode* out487 = &out487_slot;
  bool var539 = xmlNodeIsText(out487);
  traffic_assert(true);
  xmlTextReader* null612 = NULL;
  int var617 = xmlTextReaderDepth(null612);
  traffic_assert(true);
}
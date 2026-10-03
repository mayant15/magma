#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_11(char* data, int size) {
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
  xmlNode* null408 = NULL;
  int var461 = xmlChildElementCount(null408);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_6(char* data, int size) {
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
  xmlNode out342_slot; xmlNode* out342 = &out342_slot;
  int var396 = xmlChildElementCount(out342);
  traffic_assert(true);
  xmlTextReader* null471 = NULL;
  int var476 = xmlTextReaderDepth(null471);
  traffic_assert(true);
}
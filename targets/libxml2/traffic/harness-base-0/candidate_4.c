#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_4(char* data, int size) {
  xmlInitParser();
  xmlTextReader* null141 = NULL;
  xmlFreeTextReader(null141);
  traffic_assert(true);
  int var229 = xmlTextReaderRead(null141);
  traffic_assert(true);
  xmlNode out259_slot; xmlNode* out259 = &out259_slot;
  char* var307 = xmlNodeGetContent(out259);
  traffic_assert(true);
  char* var385 = xmlTextReaderConstName(null141);
  traffic_assert(true);
  xmlNode out413_slot; xmlNode* out413 = &out413_slot;
  bool var463 = xmlIsBlankNode(out413);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlParserCtxt* var76 = xmlNewParserCtxt();
  xmlNode out89_slot; xmlNode* out89 = &out89_slot;
  xmlNode* null92 = NULL;
  xmlNode* var153 = xmlAddChild(out89, null92);
  traffic_assert(true);
  traffic_assert(true);
  xmlTextReader* null221 = NULL;
  xmlFreeTextReader(null221);
  traffic_assert(true);
  xmlNode* null260 = NULL;
  bool var309 = xmlIsBlankNode(null260);
  traffic_assert(true);
}
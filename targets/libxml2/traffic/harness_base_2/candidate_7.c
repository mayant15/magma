#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_7(char* data, int size) {
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
  xmlNode out334_slot; xmlNode* out334 = &out334_slot;
  bool var386 = xmlNodeIsText(out334);
  traffic_assert(true);
  xmlTextReader* null459 = NULL;
  int var464 = xmlTextReaderDepth(null459);
  traffic_assert(true);
}
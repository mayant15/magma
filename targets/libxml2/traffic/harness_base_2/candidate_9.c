#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_9(char* data, int size) {
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
  xmlNode out336_slot; xmlNode* out336 = &out336_slot;
  bool var386 = xmlIsBlankNode(out336);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_5(char* data, int size) {
  xmlParserCtxt* null43 = NULL;
  char out48_slot; char* out48 = &out48_slot;
  char* null51 = NULL;
  int const52 = 1;
  xmlDoc* var78 = xmlCtxtReadMemory(null43, data, size, out48, null51, const52);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlDoc* null108 = NULL;
  xmlNode* var163 = xmlDocGetRootElement(null108);
  traffic_assert(true);
  xmlParserCtxt* null206 = NULL;
  xmlFreeParserCtxt(null206);
  traffic_assert(true);
  xmlNode* null265 = NULL;
  xmlUnlinkNode(null265);
  traffic_assert(true);
  xmlInitParser();
  xmlNode out415_slot; xmlNode* out415 = &out415_slot;
  xmlNode* var479 = xmlAddChild(out415, var163);
  traffic_assert(true);
  traffic_assert(true);
}
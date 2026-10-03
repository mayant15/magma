#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_11(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlUnlinkNode(null19);
  traffic_assert(true);
  xmlParserCtxt* null116 = NULL;
  xmlFreeParserCtxt(null116);
  traffic_assert(true);
  xmlNode out176_slot; xmlNode* out176 = &out176_slot;
  int var230 = xmlChildElementCount(out176);
  traffic_assert(true);
  xmlParserCtxt* null273 = NULL;
  char out274_slot; char* out274 = &out274_slot;
  int const276 = 0;
  char out278_slot; char* out278 = &out278_slot;
  char out280_slot; char* out280 = &out280_slot;
  int const282 = 1;
  xmlDoc* var308 = xmlCtxtReadMemory(null273, out274, const276, out278, out280, const282);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
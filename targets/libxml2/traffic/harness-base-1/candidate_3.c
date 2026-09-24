#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_3(char* data, int size) {
  xmlParserCtxt* var78 = xmlNewParserCtxt();
  char* null124 = NULL;
  char out129_slot; char* out129 = &out129_slot;
  int const131 = -1;
  xmlDoc* var157 = xmlCtxtReadMemory(var78, null124, size, data, out129, const131);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
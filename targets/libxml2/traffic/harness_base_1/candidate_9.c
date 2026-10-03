#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_9(char* data, int size) {
  xmlTextReader* null67 = NULL;
  int var76 = xmlTextReaderRead(null67);
  traffic_assert(true);
  xmlNode* null107 = NULL;
  char* var154 = xmlNodeGetContent(null107);
  traffic_assert(true);
  char out208_slot; char* out208 = &out208_slot;
  xmlParserInputBuffer* var232 = xmlParserInputBufferCreateStatic(out208, size, var76);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlFreeParserInputBuffer(var232);
  traffic_assert(true);
  xmlInitParser();
}
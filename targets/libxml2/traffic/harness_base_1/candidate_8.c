#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_8(char* data, int size) {
  xmlTextReader* null67 = NULL;
  int var76 = xmlTextReaderRead(null67);
  traffic_assert(true);
  xmlNode out104_slot; xmlNode* out104 = &out104_slot;
  bool var154 = xmlIsBlankNode(out104);
  traffic_assert(true);
  xmlInitParser();
  xmlNode out260_slot; xmlNode* out260 = &out260_slot;
  char* var308 = xmlNodeGetContent(out260);
  traffic_assert(true);
  xmlParserCtxt* null351 = NULL;
  char out352_slot; char* out352 = &out352_slot;
  int const354 = 0;
  xmlDoc* var386 = xmlCtxtReadMemory(null351, out352, const354, data, var308, var76);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserCtxt* var469 = xmlNewParserCtxt();
  xmlParserInputBuffer* null531 = NULL;
  char* null533 = NULL;
  xmlTextReader* var546 = xmlNewTextReader(null531, null533);
  traffic_assert(true);
  traffic_assert(true);
}
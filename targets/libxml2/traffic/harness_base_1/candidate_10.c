#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_10(char* data, int size) {
  xmlTextReader* null67 = NULL;
  int var76 = xmlTextReaderRead(null67);
  traffic_assert(true);
  xmlNode out104_slot; xmlNode* out104 = &out104_slot;
  bool var154 = xmlIsBlankNode(out104);
  traffic_assert(true);
  xmlInitParser();
  char* null233 = NULL;
  xmlDoc* var308 = xmlNewDoc(null233);
  traffic_assert(true);
  xmlFreeDoc(var308);
  traffic_assert(true);
}
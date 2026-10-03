#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_3(char* data, int size) {
  xmlTextReader* null67 = NULL;
  int var76 = xmlTextReaderRead(null67);
  traffic_assert(true);
  xmlNode out104_slot; xmlNode* out104 = &out104_slot;
  bool var154 = xmlIsBlankNode(out104);
  traffic_assert(true);
  xmlInitParser();
  char* var308 = xmlTextReaderConstName(null67);
  traffic_assert(true);
  int var386 = xmlChildElementCount(out104);
  traffic_assert(true);
}
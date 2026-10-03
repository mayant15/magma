#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_0(char* data, int size) {
  xmlTextReader* null67 = NULL;
  int var76 = xmlTextReaderRead(null67);
  traffic_assert(true);
  xmlNode* null91 = NULL;
  xmlNode* null93 = NULL;
  xmlNode* var154 = xmlAddChild(null91, null93);
  traffic_assert(true);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_0(char* data, int size) {
  xmlNode* null25 = NULL;
  bool var76 = xmlNodeIsText(null25);
  traffic_assert(true);
}
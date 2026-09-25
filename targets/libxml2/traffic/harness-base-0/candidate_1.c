#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlInitParser();
  xmlNode out98_slot; xmlNode* out98 = &out98_slot;
  int var152 = xmlChildElementCount(out98);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_0(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlUnlinkNode(null19);
  traffic_assert(true);
  xmlTextReader* null142 = NULL;
  xmlFreeTextReader(null142);
  traffic_assert(true);
  xmlNode* null167 = NULL;
  xmlNode* var230 = xmlAddChild(null167, null19);
  traffic_assert(true);
  traffic_assert(true);
}
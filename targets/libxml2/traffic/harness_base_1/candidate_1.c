#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlNode* null13 = NULL;
  xmlNode* null15 = NULL;
  xmlNode* var76 = xmlAddChild(null13, null15);
  traffic_assert(true);
  traffic_assert(true);
  xmlDoc* null100 = NULL;
  xmlNode* var155 = xmlDocGetRootElement(null100);
  traffic_assert(true);
}
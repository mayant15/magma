#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_2(char* data, int size) {
  xmlNs* null9 = NULL;
  TF_String const10 = "HfTgrKZsb";
  xmlNode* var76 = xmlNewNode(null9, const10);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserInputBuffer* null140 = NULL;
  xmlTextReader* var155 = xmlNewTextReader(null140, data);
  traffic_assert(true);
  traffic_assert(true);
  xmlUnlinkNode(var76);
  traffic_assert(true);
  xmlNode* null264 = NULL;
  char* var311 = xmlNodeGetContent(null264);
  traffic_assert(true);
  xmlAttr* var389 = xmlHasProp(var76, const10);
  traffic_assert(true);
  traffic_assert(true);
  xmlNode* null415 = NULL;
  int var468 = xmlChildElementCount(null415);
  traffic_assert(true);
  xmlFreeNode(var76);
  traffic_assert(true);
}
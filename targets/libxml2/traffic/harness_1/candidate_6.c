#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_6(char* data, int size) {
  char* null1 = NULL;
  xmlDoc* var34 = xmlNewDoc(null1);
  traffic_assert(true);
  if (!((var34 == NULL))) {
    traffic_assert(true);
    xmlNode* var75 = xmlDocGetRootElement(var34);
  }
}
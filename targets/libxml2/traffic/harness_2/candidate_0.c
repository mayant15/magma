#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_0(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  xmlNs* null40 = NULL;
  TF_String const41 = "emOlU!w)";
  xmlNode* var69 = xmlNewNode(null40, const41);
  traffic_assert(true);
  if (!((var69 == NULL))) {
    traffic_assert(true);
    xmlFreeNode(var69);
    traffic_assert(true);
  }
}
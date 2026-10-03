#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_6(char* data, int size) {
  xmlNs* null5 = NULL;
  TF_String const6 = "1w!ETSZ%Z";
  xmlNode* var34 = xmlNewNode(null5, const6);
  traffic_assert(true);
  if (!((var34 == NULL))) {
    traffic_assert(true);
    bool var77 = xmlIsBlankNode(var34);
    traffic_assert(true);
    char* var119 = xmlNodeGetContent(var34);
    traffic_assert(true);
    xmlFreeNode(var34);
    traffic_assert(true);
  }
}
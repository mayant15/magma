#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_2(char* data, int size) {
  xmlNs* null5 = NULL;
  TF_String const6 = "1w!ETSZ%Z";
  xmlNode* var34 = xmlNewNode(null5, const6);
  traffic_assert(true);
  if (!((var34 == NULL))) {
    traffic_assert(true);
    TF_String const56 = "aXUZ5wK6&aLU138R52&";
    char* var77 = xmlGetProp(var34, const56);
    traffic_assert(true);
    int var119 = xmlChildElementCount(var34);
    traffic_assert(true);
  }
}
#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  xmlNs* null40 = NULL;
  TF_String const41 = "emOlU!w)";
  xmlNode* var69 = xmlNewNode(null40, const41);
  traffic_assert(true);
  if (!((var69 == NULL))) {
    traffic_assert(true);
    xmlUnlinkNode(var69);
    traffic_assert(true);
    TF_String const135 = "OTWZc#0";
    xmlAttr* var153 = xmlHasProp(var69, const135);
    traffic_assert(true);
    char* var195 = xmlNodeGetContent(var69);
    traffic_assert(true);
    if (!((var195 == NULL))) {
      traffic_assert(true);
      bool var238 = xmlIsBlankNode(var69);
      traffic_assert(true);
      int var280 = xmlChildElementCount(var69);
      traffic_assert(true);
    }
  }
}
#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_6(char* data, int size) {
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
    TF_String const174 = "lH4Xi9buv1#l^jzLNHwC";
    char* var195 = xmlGetProp(var69, const174);
    traffic_assert(true);
  }
}
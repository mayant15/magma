#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_5(char* data, int size) {
  xmlNs out8_slot; xmlNs* out8 = &out8_slot;
  TF_String const10 = "x1[dup";
  xmlNode* var76 = xmlNewNode(out8, const10);
  traffic_assert(true);
  traffic_assert(true);
  int var155 = xmlChildElementCount(var76);
  traffic_assert(true);
  TF_String const193 = "Tn$[cYC";
  xmlAttr* var233 = xmlHasProp(var76, const193);
  traffic_assert(true);
  traffic_assert(true);
}
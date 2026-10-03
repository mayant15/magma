#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_3(char* data, int size) {
  xmlNs* null5 = NULL;
  TF_String const6 = "m5JleO0SF]9ZE$4Jn1rR";
  xmlNode* var34 = xmlNewNode(null5, const6);
  traffic_assert(true);
  if (!((var34 == NULL))) {
    traffic_assert(true);
    char* var77 = xmlNodeGetContent(var34);
    traffic_assert(true);
    bool var119 = xmlNodeIsText(var34);
    traffic_assert(true);
    if (!((var77 == NULL))) {
      traffic_assert(true);
      xmlUnlinkNode(var34);
      traffic_assert(true);
      bool var203 = xmlIsBlankNode(var34);
      traffic_assert(true);
    }
  }
}
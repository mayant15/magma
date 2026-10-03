#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_8(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  xmlParserCtxt* var69 = xmlNewParserCtxt();
  if (!((var69 == NULL))) {
    traffic_assert(true);
    char* null96 = NULL;
    char* null98 = NULL;
    int const99 = 0;
    xmlDoc* var114 = xmlCtxtReadMemory(var69, data, size, null96, null98, const99);
    traffic_assert(true);
    traffic_assert(true);
    xmlFreeParserCtxt(var69);
    if (!((var114 == NULL))) {
      traffic_assert(true);
      xmlNode* var183 = xmlDocGetRootElement(var114);
      if (!((var183 == NULL))) {
        traffic_assert(true);
        traffic_assert(true);
        traffic_assert(true);
        TF_String const214 = "rExB$!0X(";
        xmlAttr* var228 = xmlHasProp(var183, const214);
        traffic_assert(true);
        int var269 = xmlChildElementCount(var183);
        traffic_assert(true);
      } else if ((var183 == NULL)) {
        traffic_assert(true);
        traffic_assert(true);
      }
    }
  }
}
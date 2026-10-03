#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_8(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  int const59 = 1;
  xmlParserInputBuffer* var69 = xmlParserInputBufferCreateStatic(data, size, const59);
  traffic_assert(true);
  if (!((var69 == NULL))) {
    traffic_assert(true);
    char* null73 = NULL;
    xmlDoc* var106 = xmlNewDoc(null73);
    traffic_assert(true);
    if (!((var106 == NULL))) {
      traffic_assert(true);
      xmlNode* var147 = xmlDocGetRootElement(var106);
    }
  }
}
#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_4(char* data, int size) {
  int const24 = 1;
  xmlParserInputBuffer* var34 = xmlParserInputBufferCreateStatic(data, size, const24);
  traffic_assert(true);
  if (!((var34 == NULL))) {
    traffic_assert(true);
    char* null38 = NULL;
    xmlDoc* var71 = xmlNewDoc(null38);
    traffic_assert(true);
    if (!((var71 == NULL))) {
      traffic_assert(true);
      xmlNode* var112 = xmlDocGetRootElement(var71);
    }
  }
}
#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  xmlParserCtxt* var71 = xmlNewParserCtxt();
  char* null74 = NULL;
  xmlDoc* var107 = xmlNewDoc(null74);
  traffic_assert(true);
}
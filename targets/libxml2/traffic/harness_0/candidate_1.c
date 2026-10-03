#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  xmlParserCtxt* var69 = xmlNewParserCtxt();
  if (!((var69 == NULL))) {
    traffic_assert(true);
    xmlFreeParserCtxt(var69);
  }
}
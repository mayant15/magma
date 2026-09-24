#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_0(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  xmlParserCtxt* var71 = xmlNewParserCtxt();
}
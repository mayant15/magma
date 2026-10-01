#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_0(char* data, int size) {
  xmlParserCtxt* null39 = NULL;
  xmlFreeParserCtxt(null39);
  traffic_assert(true);
}
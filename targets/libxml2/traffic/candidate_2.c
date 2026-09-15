#include <traffic.h>

#include <libxml/parser.h>

#include <libxml/tree.h>

#include <libxml/xmlreader.h>

#include <libxml/xpath.h>

int LLVMFuzzerTestOneInput(char* data, int size) {
  int options = 0;
  char* encoding = NULL;
  char* url = NULL;
  xmlDoc* doc = xmlReadMemory(data, size, url, encoding, options);
  xmlRelaxNGParserCtxtPtr var1606 = xmlRelaxNGNewDocParserCtxt(doc);
  traffic_assert(true);
}
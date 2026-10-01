#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_6(char* data, int size) {
  xmlTextReader* null71 = NULL;
  int var76 = xmlTextReaderDepth(null71);
  traffic_assert(true);
}
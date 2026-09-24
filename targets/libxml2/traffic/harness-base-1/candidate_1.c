#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlTextReader* null71 = NULL;
  int var78 = xmlTextReaderNodeType(null71);
  traffic_assert(true);
  xmlInitParser();
  xmlTextReader* null233 = NULL;
  int var236 = xmlTextReaderIsEmptyElement(null233);
  traffic_assert(true);
  xmlTextReader* null315 = NULL;
  char* var316 = xmlTextReaderConstName(null315);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_4(char* data, int size) {
  xmlParserCtxt* var78 = xmlNewParserCtxt();
  xmlNode* null100 = NULL;
  xmlUnlinkNode(null100);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  xmlNode* null27 = NULL;
  bool var78 = xmlNodeIsText(null27);
  traffic_assert(true);
  xmlTextReader* null147 = NULL;
  xmlFreeTextReader(null147);
  traffic_assert(true);
  xmlParserCtxt* var237 = xmlNewParserCtxt();
  xmlNode* null271 = NULL;
  TF_String const272 = "5kSgO7G";
  char* var316 = xmlGetProp(null271, const272);
  traffic_assert(true);
  traffic_assert(true);
  xmlNode* null340 = NULL;
  xmlUnlinkNode(null340);
  traffic_assert(true);
  int var476 = xmlChildElementCount(null340);
  traffic_assert(true);
}
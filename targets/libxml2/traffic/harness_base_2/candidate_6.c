#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_6(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlUnlinkNode(null19);
  traffic_assert(true);
  xmlTextReader* null144 = NULL;
  int var153 = xmlTextReaderRead(null144);
  traffic_assert(true);
  int var231 = xmlTextReaderNodeType(null144);
  traffic_assert(true);
  char* var309 = xmlNodeGetContent(null19);
  traffic_assert(true);
}
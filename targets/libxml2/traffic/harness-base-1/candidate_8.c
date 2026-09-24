#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_8(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlFreeNode(null19);
  traffic_assert(true);
  xmlTextReader* null148 = NULL;
  int var157 = xmlTextReaderRead(null148);
  traffic_assert(true);
  xmlParserInputBuffer* null222 = NULL;
  xmlTextReader* var237 = xmlNewTextReader(null222, data);
  traffic_assert(true);
  traffic_assert(true);
  xmlNs* null251 = NULL;
  TF_String const252 = "GG6PzRrx(p";
  xmlNode* var318 = xmlNewNode(null251, const252);
  traffic_assert(true);
  traffic_assert(true);
}
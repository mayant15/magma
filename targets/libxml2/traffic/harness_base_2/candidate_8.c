#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_8(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlUnlinkNode(null19);
  traffic_assert(true);
  xmlTextReader* null144 = NULL;
  int var153 = xmlTextReaderRead(null144);
  traffic_assert(true);
  xmlParserCtxt* null196 = NULL;
  char out201_slot; char* out201 = &out201_slot;
  char out203_slot; char* out203 = &out203_slot;
  xmlDoc* var231 = xmlCtxtReadMemory(null196, data, size, out201, out203, var153);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlFreeNode(null19);
  traffic_assert(true);
  xmlInitParser();
  xmlFreeDoc(var231);
  traffic_assert(true);
  xmlParserInputBuffer* null529 = NULL;
  char out530_slot; char* out530 = &out530_slot;
  xmlTextReader* var544 = xmlNewTextReader(null529, out530);
  traffic_assert(true);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_7(char* data, int size) {
  xmlInitParser();
  xmlTextReader* null141 = NULL;
  xmlFreeTextReader(null141);
  traffic_assert(true);
  int var229 = xmlTextReaderRead(null141);
  traffic_assert(true);
  xmlTextReader* null300 = NULL;
  int var307 = xmlTextReaderNodeType(null300);
  traffic_assert(true);
  xmlNode out339_slot; xmlNode* out339 = &out339_slot;
  TF_String const341 = "luj]T3";
  char* var385 = xmlGetProp(out339, const341);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserCtxt* null427 = NULL;
  xmlFreeParserCtxt(null427);
  traffic_assert(true);
  int var541 = xmlTextReaderIsEmptyElement(null141);
  traffic_assert(true);
  char out585_slot; char* out585 = &out585_slot;
  xmlDoc* var619 = xmlCtxtReadMemory(null427, out585, var229, var385, data, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserInputBuffer* null687 = NULL;
  xmlTextReader* var702 = xmlNewTextReader(null687, data);
  traffic_assert(true);
  traffic_assert(true);
}
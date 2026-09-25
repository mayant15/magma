#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_8(char* data, int size) {
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
  xmlNode* null570 = NULL;
  bool var619 = xmlIsBlankNode(null570);
  traffic_assert(true);
  char* null622 = NULL;
  xmlDoc* var697 = xmlNewDoc(null622);
  traffic_assert(true);
}
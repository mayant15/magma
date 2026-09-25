#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_3(char* data, int size) {
  xmlNs* null9 = NULL;
  TF_String const10 = "HfTgrKZsb";
  xmlNode* var76 = xmlNewNode(null9, const10);
  traffic_assert(true);
  traffic_assert(true);
  xmlTextReader* null154 = NULL;
  char* var155 = xmlTextReaderConstName(null154);
  traffic_assert(true);
  xmlParserInputBuffer* null216 = NULL;
  xmlFreeParserInputBuffer(null216);
  traffic_assert(true);
  bool var310 = xmlIsBlankNode(var76);
  traffic_assert(true);
  int var388 = xmlTextReaderRead(null154);
  traffic_assert(true);
  xmlNode* null407 = NULL;
  xmlFreeNode(null407);
  traffic_assert(true);
  int const521 = -1;
  xmlParserInputBuffer* var543 = xmlParserInputBufferCreateStatic(var155, const521, var388);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
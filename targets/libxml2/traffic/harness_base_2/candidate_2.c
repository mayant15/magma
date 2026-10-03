#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_2(char* data, int size) {
  xmlNode* null19 = NULL;
  xmlUnlinkNode(null19);
  traffic_assert(true);
  xmlParserCtxt* null116 = NULL;
  xmlFreeParserCtxt(null116);
  traffic_assert(true);
  xmlTextReader* null229 = NULL;
  char* var230 = xmlTextReaderConstName(null229);
  traffic_assert(true);
  bool var308 = xmlIsBlankNode(null19);
  traffic_assert(true);
  xmlNs out318_slot; xmlNs* out318 = &out318_slot;
  TF_String const320 = "ujFeJEQN";
  xmlNode* var386 = xmlNewNode(out318, const320);
  traffic_assert(true);
  traffic_assert(true);
  int var465 = xmlTextReaderIsEmptyElement(null229);
  traffic_assert(true);
  xmlNode* null490 = NULL;
  int var543 = xmlChildElementCount(null490);
  traffic_assert(true);
  char* var621 = xmlGetProp(var386, const320);
  traffic_assert(true);
  traffic_assert(true);
  xmlNode* null639 = NULL;
  xmlNode* var700 = xmlAddChild(var386, null639);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserInputBuffer* var779 = xmlParserInputBufferCreateStatic(data, var543, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
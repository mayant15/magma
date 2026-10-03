#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_13(char* data, int size) {
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
  char* null468 = NULL;
  xmlDoc* var543 = xmlNewDoc(null468);
  traffic_assert(true);
  xmlUnlinkNode(var386);
  traffic_assert(true);
  xmlFreeDoc(var543);
  traffic_assert(true);
  xmlFreeNode(var386);
  traffic_assert(true);
}
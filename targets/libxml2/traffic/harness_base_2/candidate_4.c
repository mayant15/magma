#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_4(char* data, int size) {
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
  char* var465 = xmlNodeGetContent(var386);
  traffic_assert(true);
  xmlDoc* var543 = xmlNewDoc(var465);
  traffic_assert(true);
  int const551 = 1;
  xmlDoc* var621 = xmlCopyDoc(var543, const551);
  traffic_assert(true);
  traffic_assert(true);
  xmlNode* var700 = xmlDocGetRootElement(var621);
  traffic_assert(true);
  int const708 = 0;
  xmlDoc* var778 = xmlCopyDoc(var543, const708);
  traffic_assert(true);
  traffic_assert(true);
}
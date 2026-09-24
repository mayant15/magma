#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_0(char* data, int size) {
  xmlInitParser();
  xmlParserCtxt* null119 = NULL;
  xmlFreeParserCtxt(null119);
  traffic_assert(true);
  xmlNode out189_slot; xmlNode* out189 = &out189_slot;
  TF_String const191 = "kG(uV9%zjR1qGeeVZ";
  char* var235 = xmlGetProp(out189, const191);
  traffic_assert(true);
  traffic_assert(true);
  xmlDoc* null243 = NULL;
  xmlFreeDoc(null243);
  traffic_assert(true);
  xmlParserInputBuffer* null378 = NULL;
  xmlFreeParserInputBuffer(null378);
  traffic_assert(true);
  xmlNode* var474 = xmlDocGetRootElement(null243);
  traffic_assert(true);
  xmlTextReader* var554 = xmlNewTextReader(null378, var235);
  traffic_assert(true);
  traffic_assert(true);
  int const615 = 1;
  xmlParserInputBuffer* var635 = xmlParserInputBufferCreateStatic(data, size, const615);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var717 = xmlTextReaderIsEmptyElement(var554);
  traffic_assert(true);
  xmlDoc* var797 = xmlCopyDoc(null243, size);
  traffic_assert(true);
  traffic_assert(true);
  int var878 = xmlTextReaderRead(var554);
  traffic_assert(true);
  int var958 = xmlTextReaderNodeType(var554);
  traffic_assert(true);
}
#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_2(char* data, int size) {
  xmlNs* null6 = NULL;
  TF_String const7 = "^*tln0xjfR";
  xmlNode* var35 = xmlNewNode(null6, const7);
  traffic_assert(true);
  int const62 = 1;
  xmlParserInputBuffer* var72 = xmlParserInputBufferCreateStatic(data, size, const62);
  traffic_assert(true);
  xmlInitParser();
  traffic_assert(true);
}
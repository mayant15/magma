#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_0(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  int const61 = 1;
  xmlParserInputBuffer* var71 = xmlParserInputBufferCreateStatic(data, size, const61);
  traffic_assert(true);
  xmlNs* null79 = NULL;
  TF_String const80 = "GutBIvZH#x1e(Y^V%";
  xmlNode* var104 = xmlNewNode(null79, const80);
  traffic_assert(true);
}
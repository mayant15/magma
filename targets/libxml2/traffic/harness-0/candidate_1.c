#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_1(char* data, int size) {
  int const24 = 1;
  xmlParserInputBuffer* var33 = xmlParserInputBufferCreateStatic(data, size, const24);
  xmlInitParser();
  traffic_assert(true);
  xmlParserCtxt* var93 = xmlNewParserCtxt();
  xmlNs* null100 = NULL;
  TF_String const101 = "]uCMsxv44)v#TTh&Cc";
  xmlNode* var123 = xmlNewNode(null100, const101);
}
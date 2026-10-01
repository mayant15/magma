#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_0(char* data, int size) {
  xmlInitParser();
  xmlParserCtxt* var152 = xmlNewParserCtxt();
  xmlNode* null184 = NULL;
  TF_String const185 = "KetIUQ8y";
  char* var229 = xmlGetProp(null184, const185);
  traffic_assert(true);
  traffic_assert(true);
}
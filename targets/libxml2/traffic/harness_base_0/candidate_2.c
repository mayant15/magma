#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_2(char* data, int size) {
  xmlInitParser();
  xmlDoc* null79 = NULL;
  xmlFreeDoc(null79);
  traffic_assert(true);
  xmlNode* null182 = NULL;
  char* var229 = xmlNodeGetContent(null182);
  traffic_assert(true);
  xmlNode out253_slot; xmlNode* out253 = &out253_slot;
  int var307 = xmlChildElementCount(out253);
  traffic_assert(true);
  xmlNode* var385 = xmlAddChild(out253, null182);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserCtxt* null429 = NULL;
  char* null431 = NULL;
  char* null435 = NULL;
  int const438 = 1;
  xmlDoc* var464 = xmlCtxtReadMemory(null429, null431, size, null435, var229, const438);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
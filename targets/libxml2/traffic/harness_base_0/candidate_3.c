#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_3(char* data, int size) {
  xmlInitParser();
  xmlDoc* null79 = NULL;
  xmlFreeDoc(null79);
  traffic_assert(true);
  xmlTextReader* null218 = NULL;
  xmlFreeTextReader(null218);
  traffic_assert(true);
  xmlNode* null247 = NULL;
  xmlFreeNode(null247);
  traffic_assert(true);
  xmlNode out333_slot; xmlNode* out333 = &out333_slot;
  bool var383 = xmlIsBlankNode(out333);
  traffic_assert(true);
  xmlParserInputBuffer* null444 = NULL;
  xmlFreeParserInputBuffer(null444);
  traffic_assert(true);
  int const516 = 0;
  xmlParserInputBuffer* var538 = xmlParserInputBufferCreateStatic(data, const516, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserCtxt* null581 = NULL;
  xmlFreeParserCtxt(null581);
  traffic_assert(true);
  xmlUnlinkNode(null247);
  traffic_assert(true);
  char* var772 = xmlTextReaderConstName(null218);
  traffic_assert(true);
  xmlDoc* null779 = NULL;
  int const780 = -1;
  xmlDoc* var850 = xmlCopyDoc(null779, const780);
  traffic_assert(true);
  traffic_assert(true);
  xmlNode out881_slot; xmlNode* out881 = &out881_slot;
  char* var929 = xmlNodeGetContent(out881);
  traffic_assert(true);
  xmlNs* null940 = NULL;
  TF_String const941 = "@aVwZRhI";
  xmlNode* var1007 = xmlNewNode(null940, const941);
  traffic_assert(true);
  traffic_assert(true);
}
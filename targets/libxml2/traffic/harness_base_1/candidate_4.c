#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_4(char* data, int size) {
  xmlNs* null9 = NULL;
  TF_String const10 = "HfTgrKZsb";
  xmlNode* var76 = xmlNewNode(null9, const10);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserInputBuffer* null140 = NULL;
  xmlTextReader* var155 = xmlNewTextReader(null140, data);
  traffic_assert(true);
  traffic_assert(true);
  xmlUnlinkNode(var76);
  traffic_assert(true);
  xmlNode* null264 = NULL;
  char* var311 = xmlNodeGetContent(null264);
  traffic_assert(true);
  xmlParserCtxt* var389 = xmlNewParserCtxt();
  xmlDoc* var466 = xmlNewDoc(var311);
  traffic_assert(true);
  xmlNode out502_slot; xmlNode* out502 = &out502_slot;
  xmlAttr* var544 = xmlHasProp(out502, const10);
  traffic_assert(true);
  traffic_assert(true);
  xmlNode* null578 = NULL;
  char* var623 = xmlGetProp(null578, const10);
  traffic_assert(true);
  traffic_assert(true);
  char* var702 = xmlNodeGetContent(var76);
  traffic_assert(true);
}
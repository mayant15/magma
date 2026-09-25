#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_3(char* data, int size) {
  xmlNode* null23 = NULL;
  int var76 = xmlChildElementCount(null23);
  traffic_assert(true);
  xmlNs out86_slot; xmlNs* out86 = &out86_slot;
  TF_String const88 = "eizq)YFP5jTa7sE[";
  xmlNode* var154 = xmlNewNode(out86, const88);
  traffic_assert(true);
  traffic_assert(true);
  xmlUnlinkNode(null23);
  traffic_assert(true);
  xmlDoc* null237 = NULL;
  xmlFreeDoc(null237);
  traffic_assert(true);
  xmlAttr* var387 = xmlHasProp(null23, const88);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserInputBuffer* null451 = NULL;
  char out452_slot; char* out452 = &out452_slot;
  xmlTextReader* var466 = xmlNewTextReader(null451, out452);
  traffic_assert(true);
  traffic_assert(true);
  xmlParserCtxt* null510 = NULL;
  int const513 = 1;
  char out515_slot; char* out515 = &out515_slot;
  char* null518 = NULL;
  int const519 = -1;
  xmlDoc* var545 = xmlCtxtReadMemory(null510, data, const513, out515, null518, const519);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlDoc* var628 = xmlCopyDoc(null237, const519);
  traffic_assert(true);
  traffic_assert(true);
  xmlAttr* var707 = xmlHasProp(var154, const88);
  traffic_assert(true);
  traffic_assert(true);
}
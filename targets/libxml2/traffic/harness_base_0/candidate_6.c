#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_6(char* data, int size) {
  xmlInitParser();
  xmlTextReader* null141 = NULL;
  xmlFreeTextReader(null141);
  traffic_assert(true);
  int var229 = xmlTextReaderRead(null141);
  traffic_assert(true);
  xmlParserInputBuffer* null290 = NULL;
  xmlFreeParserInputBuffer(null290);
  traffic_assert(true);
  xmlDoc* null329 = NULL;
  xmlNode* var384 = xmlDocGetRootElement(null329);
  traffic_assert(true);
  xmlNode* null405 = NULL;
  xmlUnlinkNode(null405);
  traffic_assert(true);
  xmlNode* null480 = NULL;
  xmlFreeNode(null480);
  traffic_assert(true);
  xmlDoc* null543 = NULL;
  xmlFreeDoc(null543);
  traffic_assert(true);
  xmlNs out625_slot; xmlNs* out625 = &out625_slot;
  TF_String const627 = "uM1APi";
  xmlNode* var693 = xmlNewNode(out625, const627);
  traffic_assert(true);
  traffic_assert(true);
}
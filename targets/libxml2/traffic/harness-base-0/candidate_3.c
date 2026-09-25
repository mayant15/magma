#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_3(char* data, int size) {
  xmlInitParser();
  xmlParserCtxt* var152 = xmlNewParserCtxt();
  xmlNode out165_slot; xmlNode* out165 = &out165_slot;
  xmlNode* null168 = NULL;
  xmlNode* var229 = xmlAddChild(out165, null168);
  traffic_assert(true);
  traffic_assert(true);
  xmlDoc* null237 = NULL;
  xmlDoc* var308 = xmlCopyDoc(null237, size);
  traffic_assert(true);
  traffic_assert(true);
}
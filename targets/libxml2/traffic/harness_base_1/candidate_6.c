#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_6(char* data, int size) {
  xmlTextReader* null67 = NULL;
  int var76 = xmlTextReaderRead(null67);
  traffic_assert(true);
  xmlNode out104_slot; xmlNode* out104 = &out104_slot;
  bool var154 = xmlIsBlankNode(out104);
  traffic_assert(true);
  xmlParserInputBuffer* null217 = NULL;
  char out218_slot; char* out218 = &out218_slot;
  xmlTextReader* var232 = xmlNewTextReader(null217, out218);
  traffic_assert(true);
  traffic_assert(true);
  xmlNs out243_slot; xmlNs* out243 = &out243_slot;
  TF_String const245 = "d2RnqFmXxjK5@tDA";
  xmlNode* var311 = xmlNewNode(out243, const245);
  traffic_assert(true);
  traffic_assert(true);
  int var390 = xmlChildElementCount(var311);
  traffic_assert(true);
  xmlParserInputBuffer* var468 = xmlParserInputBufferCreateStatic(out218, var76, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}
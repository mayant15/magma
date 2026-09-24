#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_4(char* data, int size) {
  xmlParserCtxt* null43 = NULL;
  char out48_slot; char* out48 = &out48_slot;
  char* null51 = NULL;
  int const52 = 1;
  xmlDoc* var78 = xmlCtxtReadMemory(null43, data, size, out48, null51, const52);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlDoc* null108 = NULL;
  xmlNode* var163 = xmlDocGetRootElement(null108);
  traffic_assert(true);
  xmlParserCtxt* null206 = NULL;
  xmlFreeParserCtxt(null206);
  traffic_assert(true);
  xmlNode* null265 = NULL;
  xmlUnlinkNode(null265);
  traffic_assert(true);
  xmlTextReader* null400 = NULL;
  char* var401 = xmlTextReaderConstName(null400);
  traffic_assert(true);
  xmlNode* null436 = NULL;
  TF_String const437 = "cK#SO[@6O";
  char* var481 = xmlGetProp(null436, const437);
  traffic_assert(true);
  traffic_assert(true);
  char* null539 = NULL;
  int const542 = -1;
  xmlParserInputBuffer* var562 = xmlParserInputBufferCreateStatic(null539, size, const542);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var644 = xmlTextReaderRead(null400);
  traffic_assert(true);
  char* var724 = xmlNodeGetContent(var163);
  traffic_assert(true);
}
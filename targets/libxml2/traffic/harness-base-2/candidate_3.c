#include <traffic.h>

#include <libxml/globals.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_3(char* data, int size) {
  xmlInitParser();
  xmlParserCtxt* null119 = NULL;
  xmlFreeParserCtxt(null119);
  traffic_assert(true);
  int const203 = 1;
  char* null206 = NULL;
  char out207_slot; char* out207 = &out207_slot;
  xmlDoc* var235 = xmlCtxtReadMemory(null119, data, const203, null206, out207, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  xmlNode* null271 = NULL;
  bool var320 = xmlIsBlankNode(null271);
  traffic_assert(true);
  xmlNs* null333 = NULL;
  TF_String const334 = "YjkEy8dB@Oy%VDKk)4";
  xmlNode* var400 = xmlNewNode(null333, const334);
  traffic_assert(true);
  traffic_assert(true);
  xmlTextReader* null476 = NULL;
  int var481 = xmlTextReaderDepth(null476);
  traffic_assert(true);
}
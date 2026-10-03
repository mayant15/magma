#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_4(char* data, int size) {
  xmlTextReader* null67 = NULL;
  int var76 = xmlTextReaderRead(null67);
  traffic_assert(true);
  xmlNode out104_slot; xmlNode* out104 = &out104_slot;
  bool var154 = xmlIsBlankNode(out104);
  traffic_assert(true);
  xmlInitParser();
  xmlNode out260_slot; xmlNode* out260 = &out260_slot;
  char* var308 = xmlNodeGetContent(out260);
  traffic_assert(true);
  xmlNode* null341 = NULL;
  TF_String const342 = "EZ10O";
  char* var386 = xmlGetProp(null341, const342);
  traffic_assert(true);
  traffic_assert(true);
  xmlTextReader* null454 = NULL;
  xmlFreeTextReader(null454);
  traffic_assert(true);
}
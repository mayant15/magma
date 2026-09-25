#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_2(char* data, int size) {
  xmlInitParser();
  xmlTextReader* null147 = NULL;
  int var152 = xmlTextReaderDepth(null147);
  traffic_assert(true);
  int var230 = xmlTextReaderIsEmptyElement(null147);
  traffic_assert(true);
  xmlNode out256_slot; xmlNode* out256 = &out256_slot;
  bool var308 = xmlNodeIsText(out256);
  traffic_assert(true);
  TF_String const342 = "YlCc5XCjW%";
  char* var386 = xmlGetProp(out256, const342);
  traffic_assert(true);
  traffic_assert(true);
}
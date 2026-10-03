#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_8(char* data, int size) {
  int const24 = 1;
  xmlParserInputBuffer* var34 = xmlParserInputBufferCreateStatic(data, size, const24);
  traffic_assert(true);
  if (!((var34 == NULL))) {
    traffic_assert(true);
    char* null38 = NULL;
    xmlDoc* var71 = xmlNewDoc(null38);
    traffic_assert(true);
    if (!((var71 == NULL))) {
      traffic_assert(true);
      char* null104 = NULL;
      xmlTextReader* var112 = xmlNewTextReader(var34, null104);
      if (!((var112 == NULL))) {
        traffic_assert(true);
        traffic_assert(true);
        traffic_assert(true);
        int const123 = 0;
        xmlDoc* var157 = xmlCopyDoc(var71, const123);
        traffic_assert(true);
        traffic_assert(true);
        xmlFreeDoc(var71);
        if (!((var157 == NULL))) {
          traffic_assert(true);
          int var239 = xmlTextReaderNodeType(var112);
          if ((var239 == -1)) {
            traffic_assert(true);
          } else if (true) {
            traffic_assert(true);
            traffic_assert(true);
            int var282 = xmlTextReaderRead(var112);
            if ((var282 == 1)) {
              traffic_assert(true);
              int var325 = xmlTextReaderRead(var112);
              if ((var325 == 1)) {
                traffic_assert(true);
                int var408 = xmlTextReaderDepth(var112);
              } else if ((var325 == 0)) {
                traffic_assert(true);
              } else if (true) {
                traffic_assert(true);
              }
            } else if ((var282 == 0)) {
              traffic_assert(true);
            } else if (true) {
              traffic_assert(true);
              xmlFreeTextReader(var112);
              traffic_assert(true);
            }
          }
        }
      } else if ((var112 == NULL)) {
        traffic_assert(true);
        traffic_assert(true);
      }
    }
  }
}
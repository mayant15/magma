#include <traffic.h>

#include <libxml/tree.h>

#include <libxml/parser.h>

#include <libxml/xmlIO.h>

#include <libxml/xmlreader.h>

int fuzz_12(char* data, int size) {
  xmlInitParser();
  traffic_assert(true);
  int const59 = 1;
  xmlParserInputBuffer* var69 = xmlParserInputBufferCreateStatic(data, size, const59);
  traffic_assert(true);
  if (!((var69 == NULL))) {
    traffic_assert(true);
    char* null98 = NULL;
    xmlTextReader* var106 = xmlNewTextReader(var69, null98);
    if (!((var106 == NULL))) {
      traffic_assert(true);
      traffic_assert(true);
      traffic_assert(true);
      int var147 = xmlTextReaderRead(var106);
      if ((var147 == 1)) {
        traffic_assert(true);
        int var225 = xmlTextReaderRead(var106);
      } else if ((var147 == 0)) {
        traffic_assert(true);
      } else if (true) {
        traffic_assert(true);
        int var186 = xmlTextReaderDepth(var106);
        if ((var186 == -1)) {
          traffic_assert(true);
        } else if (true) {
          traffic_assert(true);
          traffic_assert(true);
        }
      }
    } else if ((var106 == NULL)) {
      traffic_assert(true);
      traffic_assert(true);
    }
  }
}
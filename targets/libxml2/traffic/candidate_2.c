#include <traffic.h>

#include <xml2-support.h>

int LLVMFuzzerTestOneInput(uint8_t* data, int size) {
  xmlDoc* out3_slot; xmlDoc** out3 = &out3_slot; 
  int var15 = xml2_read_memory(data, size, out3);
  if ((var15 == 0)) {
    traffic_assert(true);
    xmlNode* var20 = xmlDocGetRootElement((*out3));
    traffic_assert(true);
    int var26 = xmlChildElementCount(var20);
    traffic_assert(true);
    int var39 = xmlNodeIsText(var20);
    traffic_assert(true);
    char* var58 = xmlNodeGetContent(var20);
    traffic_assert(true);
    int var77 = xmlIsBlankNode(var20);
    traffic_assert(true);
  } else if (!((var15 == 0))) {
  }
}
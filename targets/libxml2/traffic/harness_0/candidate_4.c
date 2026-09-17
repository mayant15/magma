#include <traffic.h>

#include <libxml/parser.h>

#include <libxml/tree.h>

#include <libxml/xmlreader.h>

#include <libxml/xpath.h>

int fuzz_4(char* data, int size) {
  int options = 0;
  char* encoding = NULL;
  char* url = NULL;
  xmlDoc* doc = xmlReadMemory(data, size, url, encoding, options);
  int const1160 = 0;
  int var1606 = xmlThrDefLoadExtDtdDefaultValue(const1160);
  traffic_assert(true);
  int var3214 = xmlPopOutputCallbacks();
  char out3339_slot; char* out3339 = &out3339_slot;
  char out3341_slot; char* out3341 = &out3341_slot;
  int var4821 = xmlUTF8Charcmp(out3339, out3341);
  traffic_assert(true);
  traffic_assert(true);
}

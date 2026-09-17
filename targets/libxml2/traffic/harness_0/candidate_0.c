#include <traffic.h>

#include <libxml/parser.h>

#include <libxml/tree.h>

#include <libxml/xmlreader.h>

#include <libxml/xpath.h>

int fuzz_0(char* data, int size) {
  int options = 0;
  char* encoding = NULL;
  char* url = NULL;
  xmlDoc* doc = xmlReadMemory(data, size, url, encoding, options);
  int const1160 = 0;
  int var1606 = xmlThrDefLoadExtDtdDefaultValue(const1160);
  traffic_assert(true);
  int var3214 = xmlPopOutputCallbacks();
  char* null3230 = NULL;
  char* var4821 = xmlStrsub(null3230, var1606, const1160);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}

#include <traffic.h>

#include <libxml/parser.h>

#include <libxml/tree.h>

#include <libxml/xmlreader.h>

#include <libxml/xpath.h>

int LLVMFuzzerTestOneInput(char* data, int size) {
  int options = 0;
  char* encoding = NULL;
  char* url = NULL;
  xmlDoc* doc = xmlReadMemory(data, size, url, encoding, options);
  int const1160 = 0;
  int var1606 = xmlThrDefLoadExtDtdDefaultValue(const1160);
  traffic_assert(true);
  int var3214 = xmlPopOutputCallbacks();
  int const3763 = 0;
  xmlHashTablePtr var4821 = xmlHashCreate(const3763);
  traffic_assert(true);
}
#include <traffic.h>

#include <xml2-support.h>

int LLVMFuzzerTestOneInput(uint8_t* data, int size) {
  xmlXPathObject** null14 = NULL;
  int var15 = xml2_xpath_eval(data, size, null14);
}
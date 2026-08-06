#include <traffic.h>

#include <tiff-support.h>

int LLVMFuzzerTestOneInput(uint8_t* data, int size) {
  int var14 = TIFFIsCODECConfigured(size);
}
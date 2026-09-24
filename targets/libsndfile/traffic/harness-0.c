#include "harness-0/candidate_0.c"

#define INT_SIZE 4
#define NUM_CANDIDATES 1

int LLVMFuzzerTestOneInput(char* data, int size) {
  if (size < INT_SIZE) return -1;

  uint32_t index = *((uint32_t*)data);

  char* rest_ptr = data + INT_SIZE;
  int rest_len = size - INT_SIZE;

  switch (index % NUM_CANDIDATES) {
    case 0: return fuzz_0(rest_ptr, rest_len);
  }
}

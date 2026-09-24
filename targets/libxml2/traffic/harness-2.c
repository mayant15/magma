#include "harness-2/candidate_0.c"
#include "harness-2/candidate_1.c"
#include "harness-2/candidate_2.c"

#define INT_SIZE 4
#define NUM_CANDIDATES 3

int LLVMFuzzerTestOneInput(char* data, int size) {
  if (size < INT_SIZE) return -1;

  uint32_t index = *((uint32_t*)data);

  char* rest_ptr = data + INT_SIZE;
  int rest_len = size - INT_SIZE;

  switch (index % NUM_CANDIDATES) {
    case 0: return fuzz_0(rest_ptr, rest_len);
    case 1: return fuzz_1(rest_ptr, rest_len);
    case 2: return fuzz_2(rest_ptr, rest_len);
  }
}

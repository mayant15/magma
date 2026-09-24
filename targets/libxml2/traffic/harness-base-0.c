#include "harness-base-0/candidate_0.c"
#include "harness-base-0/candidate_1.c"
#include "harness-base-0/candidate_2.c"
#include "harness-base-0/candidate_3.c"
#include "harness-base-0/candidate_4.c"
#include "harness-base-0/candidate_5.c"
#include "harness-base-0/candidate_6.c"

#define INT_SIZE 4
#define NUM_CANDIDATES 7

int LLVMFuzzerTestOneInput(char* data, int size) {
  if (size < INT_SIZE) return -1;

  uint32_t index = *((uint32_t*)data);

  char* rest_ptr = data + INT_SIZE;
  int rest_len = size - INT_SIZE;

  switch (index % NUM_CANDIDATES) {
    case 0: return fuzz_0(rest_ptr, rest_len);
    case 1: return fuzz_1(rest_ptr, rest_len);
    case 2: return fuzz_2(rest_ptr, rest_len);
    case 3: return fuzz_3(rest_ptr, rest_len);
    case 4: return fuzz_4(rest_ptr, rest_len);
    case 5: return fuzz_5(rest_ptr, rest_len);
    case 6: return fuzz_6(rest_ptr, rest_len);
  }
}

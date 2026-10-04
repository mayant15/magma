#include <stdint.h>
#include <stdio.h>

#include "harness_0/candidate_0.c"
#include "harness_0/candidate_1.c"
#include "harness_0/candidate_2.c"
#include "harness_0/candidate_3.c"
#include "harness_0/candidate_4.c"
#include "harness_0/candidate_5.c"
#include "harness_0/candidate_6.c"
#include "harness_0/candidate_7.c"
#include "harness_0/candidate_8.c"
#include "harness_0/candidate_9.c"
#include "harness_0/candidate_10.c"
#include "harness_0/candidate_11.c"
#include "harness_0/candidate_12.c"
#include "harness_0/candidate_13.c"
#include "harness_0/candidate_14.c"
#include "harness_0/candidate_15.c"
#include "harness_0/candidate_16.c"
#include "harness_0/candidate_17.c"
#include "harness_0/candidate_18.c"
#include "harness_0/candidate_19.c"
#include "harness_0/candidate_20.c"
#include "harness_0/candidate_21.c"
#include "harness_0/candidate_22.c"
#include "harness_0/candidate_23.c"
#include "harness_0/candidate_24.c"
#include "harness_0/candidate_25.c"
#include "harness_0/candidate_26.c"
#include "harness_0/candidate_27.c"
#include "harness_0/candidate_28.c"

#define INT_SIZE 4
#define NUM_CANDIDATES 29

int main(int argc, char *argv[])
{
    FILE *f;
    char *fuzzData = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1)
        exit(0);

    fuzzData = (char*)malloc((size_t)size+1);
    if(fuzzData == NULL)
        exit(0);

    if(fread(fuzzData, (size_t)size, 1, f) != 1)
        exit(0);
    fuzzData[size] = '\0';

    if (size < INT_SIZE) return 0;

    uint32_t index = *((uint32_t*)fuzzData);

    char* rest_ptr = fuzzData + INT_SIZE;
    long rest_len = size - INT_SIZE;

    switch (index % NUM_CANDIDATES) {
      case 0: return fuzz_0(rest_ptr, rest_len);
      case 1: return fuzz_1(rest_ptr, rest_len);
      case 2: return fuzz_2(rest_ptr, rest_len);
      case 3: return fuzz_3(rest_ptr, rest_len);
      case 4: return fuzz_4(rest_ptr, rest_len);
      case 5: return fuzz_5(rest_ptr, rest_len);
      case 6: return fuzz_6(rest_ptr, rest_len);
      case 7: return fuzz_7(rest_ptr, rest_len);
      case 8: return fuzz_8(rest_ptr, rest_len);
      case 9: return fuzz_9(rest_ptr, rest_len);
      case 10: return fuzz_10(rest_ptr, rest_len);
      case 11: return fuzz_11(rest_ptr, rest_len);
      case 12: return fuzz_12(rest_ptr, rest_len);
      case 13: return fuzz_13(rest_ptr, rest_len);
      case 14: return fuzz_14(rest_ptr, rest_len);
      case 15: return fuzz_15(rest_ptr, rest_len);
      case 16: return fuzz_16(rest_ptr, rest_len);
      case 17: return fuzz_17(rest_ptr, rest_len);
      case 18: return fuzz_18(rest_ptr, rest_len);
      case 19: return fuzz_19(rest_ptr, rest_len);
      case 20: return fuzz_20(rest_ptr, rest_len);
      case 21: return fuzz_21(rest_ptr, rest_len);
      case 22: return fuzz_22(rest_ptr, rest_len);
      case 23: return fuzz_23(rest_ptr, rest_len);
      case 24: return fuzz_24(rest_ptr, rest_len);
      case 25: return fuzz_25(rest_ptr, rest_len);
      case 26: return fuzz_26(rest_ptr, rest_len);
      case 27: return fuzz_27(rest_ptr, rest_len);
      case 28: return fuzz_28(rest_ptr, rest_len);
    }
}

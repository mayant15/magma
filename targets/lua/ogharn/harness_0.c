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
#include "harness_0/candidate_29.c"
#include "harness_0/candidate_30.c"
#include "harness_0/candidate_31.c"
#include "harness_0/candidate_32.c"
#include "harness_0/candidate_33.c"
#include "harness_0/candidate_34.c"
#include "harness_0/candidate_35.c"
#include "harness_0/candidate_36.c"
#include "harness_0/candidate_37.c"
#include "harness_0/candidate_38.c"
#include "harness_0/candidate_39.c"
#include "harness_0/candidate_40.c"
#include "harness_0/candidate_41.c"
#include "harness_0/candidate_42.c"
#include "harness_0/candidate_43.c"
#include "harness_0/candidate_44.c"
#include "harness_0/candidate_45.c"
#include "harness_0/candidate_46.c"
#include "harness_0/candidate_47.c"
#include "harness_0/candidate_48.c"
#include "harness_0/candidate_49.c"
#include "harness_0/candidate_50.c"
#include "harness_0/candidate_51.c"
#include "harness_0/candidate_52.c"
#include "harness_0/candidate_53.c"
#include "harness_0/candidate_54.c"

#define INT_SIZE 4
#define NUM_CANDIDATES 55

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
      case 29: return fuzz_29(rest_ptr, rest_len);
      case 30: return fuzz_30(rest_ptr, rest_len);
      case 31: return fuzz_31(rest_ptr, rest_len);
      case 32: return fuzz_32(rest_ptr, rest_len);
      case 33: return fuzz_33(rest_ptr, rest_len);
      case 34: return fuzz_34(rest_ptr, rest_len);
      case 35: return fuzz_35(rest_ptr, rest_len);
      case 36: return fuzz_36(rest_ptr, rest_len);
      case 37: return fuzz_37(rest_ptr, rest_len);
      case 38: return fuzz_38(rest_ptr, rest_len);
      case 39: return fuzz_39(rest_ptr, rest_len);
      case 40: return fuzz_40(rest_ptr, rest_len);
      case 41: return fuzz_41(rest_ptr, rest_len);
      case 42: return fuzz_42(rest_ptr, rest_len);
      case 43: return fuzz_43(rest_ptr, rest_len);
      case 44: return fuzz_44(rest_ptr, rest_len);
      case 45: return fuzz_45(rest_ptr, rest_len);
      case 46: return fuzz_46(rest_ptr, rest_len);
      case 47: return fuzz_47(rest_ptr, rest_len);
      case 48: return fuzz_48(rest_ptr, rest_len);
      case 49: return fuzz_49(rest_ptr, rest_len);
      case 50: return fuzz_50(rest_ptr, rest_len);
      case 51: return fuzz_51(rest_ptr, rest_len);
      case 52: return fuzz_52(rest_ptr, rest_len);
      case 53: return fuzz_53(rest_ptr, rest_len);
      case 54: return fuzz_54(rest_ptr, rest_len);
    }
}

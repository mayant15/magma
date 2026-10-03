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

#define INT_SIZE 4
#define NUM_CANDIDATES 10

int main(int argc, char* argv[]) {
    FILE *f;
    uint8_t *fuzzData = NULL;
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

    fuzzData = (uint8_t*)malloc((size_t)size+1);
    if(fuzzData == NULL)
        exit(0);

    if(fread(fuzzData, (size_t)size, 1, f) != 1)
        exit(0);
    fuzzData[size] = '\\0';

    if (size < INT_SIZE) return 0;

    uint32_t index = *((uint32_t*)fuzzData);

    uint8_t* rest_ptr = fuzzData + INT_SIZE;
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
  }
}

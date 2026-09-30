#include <stdint.h>

#include "harness_0/candidate_0.c"

#define INT_SIZE 4
#define NUM_CANDIDATES 1

int fuzz_0(int argc, char *argv[])
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

    if (size < INT_SIZE) return 0

    uint32_t index = *((uint32_t*)data);

    char* rest_ptr = data + INT_SIZE;
    long rest_len = size - INT_SIZE;

    switch (index % NUM_CANDIDATES) {
      case 0: return fuzz_0(rest_ptr, rest_len);
    }
}

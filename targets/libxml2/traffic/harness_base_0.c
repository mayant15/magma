#include <stdint.h>
#include <stdio.h>

#include "harness_base_0/candidate_0.c"
#include "harness_base_0/candidate_1.c"
#include "harness_base_0/candidate_2.c"
#include "harness_base_0/candidate_3.c"
#include "harness_base_0/candidate_4.c"
#include "harness_base_0/candidate_5.c"
#include "harness_base_0/candidate_6.c"
#include "harness_base_0/candidate_7.c"
#include "harness_base_0/candidate_8.c"
#include "harness_base_0/candidate_9.c"
#include "harness_base_0/candidate_10.c"
#include "harness_base_0/candidate_11.c"
#include "harness_base_0/candidate_12.c"
#include "harness_base_0/candidate_13.c"
#include "harness_base_0/candidate_14.c"
#include "harness_base_0/candidate_15.c"

#define INT_SIZE 4
#define NUM_CANDIDATES 16

/* Prefix-distribution tracking: when $SHARED is set, bump a per-candidate
 * counter in $SHARED/prefix_counts (64 x uint64). Slot i counts executions
 * dispatched to candidate i; slot 63 counts executions with a non-zero prefix. */
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

static void log_prefix(uint32_t index, unsigned n) {
    const char *dir = getenv("SHARED");
    if (!dir) return;
    char path[4096];
    snprintf(path, sizeof(path), "%s/prefix_counts", dir);
    int fd = open(path, O_RDWR | O_CREAT, 0644);
    if (fd < 0) return;
    size_t len = 64 * sizeof(uint64_t);
    if (ftruncate(fd, len) == 0) {
        uint64_t *c = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (c != MAP_FAILED) {
            __atomic_fetch_add(&c[index % n], 1, __ATOMIC_RELAXED);
            if (index != 0) __atomic_fetch_add(&c[63], 1, __ATOMIC_RELAXED);
            munmap(c, len);
        }
    }
    close(fd);
}

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
    log_prefix(index, NUM_CANDIDATES);

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
    case 10: return fuzz_10(rest_ptr, rest_len);
    case 11: return fuzz_11(rest_ptr, rest_len);
    case 12: return fuzz_12(rest_ptr, rest_len);
    case 13: return fuzz_13(rest_ptr, rest_len);
    case 14: return fuzz_14(rest_ptr, rest_len);
    case 15: return fuzz_15(rest_ptr, rest_len);
  }
}

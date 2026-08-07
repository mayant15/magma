/*
 * Traffic Runtime Library
 * Support functions used by Traffic-generated fuzz drivers.
 * Provider is roughly a port of LLVM's FuzzedDataProvider.
 *
 * Translated from Zig by Amp.
 * https://ampcode.com/threads/T-019e9eff-3cae-772a-a302-f5b26a5e6844
 */

#include "traffic.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

struct FuzzedDataProvider {
    const uint8_t *buf;
    size_t len;
};

static void noop(void) {}

/* Consume `nr` bytes from the front of the buffer and return a pointer to
 * them. Exits the process if there are not enough bytes left. */
static const uint8_t *prov_advance(FuzzedDataProvider *self, size_t nr) {
    if (self->len < nr) {
        exit(1);
    }
    const uint8_t *res = self->buf;
    self->buf += nr;
    self->len -= nr;
    return res;
}

/* Return a string of random length.
 *
 * Defines the first occurrence of '\\' as the end of the string, like LLVM's
 * FuzzedDataProvider. Unlike LLVM's implementation, does not map '\\\\' to
 * '\\'. The returned slice is written to *out_ptr / *out_len. */
static void prov_random_length_string(FuzzedDataProvider *self,
                                      const uint8_t **out_ptr,
                                      size_t *out_len) {
    for (size_t i = 0; i < self->len; i++) {
        if (self->buf[i] == '\\') {
            const uint8_t *slice = prov_advance(self, i);
            prov_advance(self, 1); /* also consume the terminal '\\' */
            *out_ptr = slice;
            *out_len = i;
            return;
        }
    }
    size_t len = self->len;
    *out_ptr = prov_advance(self, len);
    *out_len = len;
}

/* Returns an int in [min, max]. If no bytes left, return `min`.
 *
 * Uses scaling logic similar to LLVM's FuzzedDataProvider. `type_size` is the
 * number of bytes consumed from the buffer (the size of the source type). */
static uint64_t prov_int_in_range(FuzzedDataProvider *self, size_t type_size,
                                  uint64_t min, uint64_t max) {
    traffic_assert(min <= max);

    if (type_size > self->len) {
        return min;
    }

    uint64_t result = 0;
    const uint8_t *bytes = prov_advance(self, type_size);
    /* bytesToValue: little-endian reinterpretation of the consumed bytes. */
    memcpy(&result, bytes, type_size);

    uint64_t range = max - min;
    if (range != UINT64_MAX) {
        result = result % (range + 1);
    }

    return min + result;
}

FuzzedDataProvider *traffic_provider_init(const uint8_t *buf, size_t size) {
    FuzzedDataProvider *provider = malloc(sizeof(FuzzedDataProvider));
    if (provider == NULL) {
        abort();
    }
    provider->buf = buf;
    provider->len = size;
    return provider;
}

void traffic_provider_destroy(FuzzedDataProvider *fdp) {
    free(fdp);
}

void traffic_check_error(int err) {
    if (err < 0) {
        exit(1);
    }
}

void *traffic_check_pointer(void *ptr) {
    if (ptr == NULL) {
        exit(1);
    }
    return ptr;
}

void (*traffic_const_fn(void))(void) {
    return noop;
}

bool traffic_const_bool(FuzzedDataProvider *fdp) {
    const uint8_t byte = prov_advance(fdp, 1)[0];
    return (byte & 1) == 1;
}

int traffic_const_int(FuzzedDataProvider *fdp) {
    int result;
    const uint8_t *bytes = prov_advance(fdp, sizeof(int));
    memcpy(&result, bytes, sizeof(int));
    return result;
}

int traffic_const_int_in_range(FuzzedDataProvider *fdp, int min, int max) {
    return (int)prov_int_in_range(fdp, sizeof(int), (uint64_t)min,
                                  (uint64_t)max);
}

size_t traffic_const_size_t(FuzzedDataProvider *fdp) {
    return (size_t)prov_int_in_range(fdp, sizeof(size_t), 0, MAX_SIZE);
}

int traffic_const_enum(FuzzedDataProvider *fdp, int max) {
    return (int)prov_int_in_range(fdp, sizeof(int), 0, (uint64_t)max);
}

/* A null-terminated string of random length. */
char *traffic_const_string(FuzzedDataProvider *fdp) {
    const uint8_t *bytes;
    size_t len;
    prov_random_length_string(fdp, &bytes, &len);

    char *buf = malloc(len + 1);
    if (buf == NULL) {
        abort();
    }
    memcpy(buf, bytes, len);
    buf[len] = '\0';

    return buf;
}

void traffic_delete_string(char *string) {
    free(string);
}

#ifndef TRAFFIC_RUNTIME_H
#define TRAFFIC_RUNTIME_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define traffic_assert assert

typedef long long traffic_long_long;
typedef void (*TF_Noop)();
typedef char* TF_String;

typedef struct FuzzedDataProvider FuzzedDataProvider;

FuzzedDataProvider* traffic_provider_init(const uint8_t* buf, size_t size);
void traffic_provider_destroy(FuzzedDataProvider* fdp);

void traffic_check_error(int err);
void* traffic_check_pointer(void* ptr);

void (*traffic_const_fn(void))(void);

bool traffic_const_bool(FuzzedDataProvider* fdp);
int traffic_const_int(FuzzedDataProvider* fdp);
int traffic_const_int_in_range(FuzzedDataProvider* fdp, int min, int max);
size_t traffic_const_size_t(FuzzedDataProvider* fdp);
int traffic_const_enum(FuzzedDataProvider* fdp, int max);

char* traffic_const_string(FuzzedDataProvider* fdp);
void traffic_delete_string(char* string);

#endif // TRAFFIC_RUNTIME_H

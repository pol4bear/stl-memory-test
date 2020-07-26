#ifndef MEMORY_MEMORYFUNC_H_
#define MEMORY_MEMORYFUNC_H_

#include <stdio.h>
#include "memoryhook.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void *my_malloc(size_t size, const char *file, const int line);
void my_free(void *ptr, const char *file, const int line);
void *my_calloc(size_t nmemb, size_t size, const char *file, const int line);
void *my_realloc(void *ptr, size_t size, const char *file, const int line);

#ifdef __cplusplus
}

#include <new>

void *operator new(size_t size, const char *file, const int line);
void *operator new[](size_t size, const char *file, const int line);

void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *ptr);
void operator delete[](void *ptr);

#endif // __cplusplus

#endif // MEMORY_MEMORYFUNC_H_

#include <cstdio>
#include "memoryfunc.h"

void *my_malloc(size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._malloc(size);
    fprintf(stdout, "[memory] %zu bytes allocated in %0X using malloc(%d) by %s:%d\n",
            size, res, size, file, line);
    return res;
}

void my_free(void *ptr, const char *file, const int line) {
    MemoryHook::instance()._free(ptr);
    fprintf(stdout, "[memory] free(%0X) by %s:%d\n", ptr, file, line);
}

void *my_calloc(size_t nmemb, size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._calloc(nmemb, size);
    fprintf(stdout, "[memory] %zu bytes allocated in %0X using malloc(%zu, %zu) by %s:%d:\n",
        nmemb * size, res, nmemb, size, file, line);
    return res;
}

void *my_realloc(void *ptr, size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._realloc(ptr, size);
    fprintf(stdout, "[memory] %zu bytes allocated in %0X using realloc(%0X, %zu) by %s:%d\n",
            size, res, ptr, size, file, line);
    return res;
}

#ifdef __cplusplus

void *operator new (size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._malloc(size);
    fprintf(stdout, "[memory] %zu bytes allocated in %0x using new by %s:%d\n", size, res, file, line);
    return res;
}

void *operator new[](size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._malloc(size);
    fprintf(stdout, "[memory] %zu bytes allocated in %0x using new[] by %s:%d\n", size, res, file, line);
    return res;
}

void operator delete(void *ptr, const char *file, const int line) {
  MemoryHook::instance()._free(ptr);
  fprintf(stdout, "[memory] delete %0X by %s:%d\n", ptr, file, line);
}

void operator delete[](void *ptr, const char *file, const int line) {
  MemoryHook::instance()._free(ptr);
  fprintf(stdout, "[memory] delete %0X by %s:%d\n", ptr, file, line);
}

#endif

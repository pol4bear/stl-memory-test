#include <cstdio>
#include "memoryfunc.h"

void *my_malloc(size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._malloc(size);
    fprintf(stdout, "[memory] malloc(%zu) → %p from %s:%d",
            size, res, file, line);
    return res;
}

void my_free(void *ptr, const char *file, const int line) {
    MemoryHook::instance()._free(ptr);
    fprintf(stdout, "[memory] free(%p) from %s:%d\n", ptr, file, line);
}

void *my_calloc(size_t nmemb, size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._calloc(nmemb, size);
    fprintf(stdout, "[memory] calloc(%zu, %zu) → %p from %s:%d\n",
            nmemb, size, res, file, line);
    return res;
}

void *my_realloc(void *ptr, size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._realloc(ptr, size);
    fprintf(stdout, "[memory] realloc(%p, %zu) → %p from %s:%d\n",
            ptr, size, res, file, line);
    return res;
}

#ifdef __cplusplus

void *operator new (size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._malloc(size);
    fprintf(stdout, "[memory] new(%zu) → %p from %s:%d\n", size, res, file, line);
    return res;
}

void *operator new[](size_t size, const char *file, const int line) {
    void *res = MemoryHook::instance()._malloc(size);
    fprintf(stdout, "[memory] new[](%zu) → %p from %s:%d\n", size, res, file, line);
    return res;
}

void *operator new(size_t size) {
  void *res = MemoryHook::instance()._malloc(size);
  fprintf(stdout, "[memory] new(%zu) → %p\n", size, res);
  return res;
}

void *operator new[](size_t size) {
  void *res = MemoryHook::instance()._malloc(size);
  fprintf(stdout, "[memory] new[](%zu) → %p\n", size, res);
  return res;
}

void operator delete(void *ptr) {
  MemoryHook::instance()._free(ptr);
  fprintf(stdout, "[memory] delete(%p)\n", ptr);
}

void operator delete[](void *ptr) {
  MemoryHook::instance()._free(ptr);
  fprintf(stdout, "[memory] delete(%p)\n", ptr);
}

#endif // __cplusplus

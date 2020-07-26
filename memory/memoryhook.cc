#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include "memoryhook.h"

MemoryHook::MemoryHook() {
  printf("MemoryHook()\n");
  _malloc_orig = _malloc = reinterpret_cast<MallocFunc>(dlsym(RTLD_NEXT, "malloc"));
  if (_malloc_orig == nullptr) {
    fprintf(stderr, "[mem] dlsym(\"malloc\") returned nullptr. dlerror = %s\n", dlerror());
    goto _fail;
  }
  _free_orig = _free = reinterpret_cast<FreeFunc>(dlsym(RTLD_NEXT, "free"));
  if (_free_orig == nullptr) {
    fprintf(stderr, "[mem] dlsym(\"free\") returned nullptr. dlerror = %s\n", dlerror());
    goto _fail;
  }
  _calloc_orig = _calloc = reinterpret_cast<CallocFunc>(dlsym(RTLD_NEXT, "calloc"));
  if (_calloc_orig == nullptr) {
    fprintf(stderr, "[mem] dlsym(\"calloc\") returned nullptr. dlerror = %s\n", dlerror());
    goto _fail;
  }
  _realloc_orig = _realloc = reinterpret_cast<ReallocFunc>(dlsym(RTLD_NEXT, "realloc"));
  if (_realloc_orig == nullptr) {
    fprintf(stderr, "[mem] dlsym(\"realloc\") returned nullptr. dlerror = %s\n", dlerror());
    goto _fail;
  }
  return;
 _fail:
  abort();
}

MemoryHook::~MemoryHook() {
}

void MemoryHook::hook(
    MallocFunc malloc_func,
    FreeFunc free_func,
    CallocFunc calloc_func,
    ReallocFunc realloc_func) {
  if (malloc_func != nullptr) _malloc = malloc_func;
  if (free_func != nullptr) _free = free_func;
  if (calloc_func != nullptr) _calloc = calloc_func;
  if (realloc_func != nullptr) _realloc = realloc_func;
}

void MemoryHook::unhook() {
  _malloc  = _malloc_orig;
  _free    = _free_orig;
  _calloc  = _calloc_orig;
  _realloc = _realloc_orig;
}

MemoryHook &MemoryHook::instance() {
  static MemoryHook instance_;
  return instance_;
}

#ifdef MEMORY_GLOBAL_HOOK

void *malloc(size) {
  return MemoryHook::instance().malloc_(size);
}

void free(void *ptr) {
  MemoryHook::instance().free_(ptr);
}

void *calloc(size_t nmemb, size_t size) {
  return MemoryHook::instance().calloc_(nmemb, size);
}

void *realloc(void *ptr, sizee_t size) {
  return MemoryHook::instance().realloc_(ptr, size);
}

#endif

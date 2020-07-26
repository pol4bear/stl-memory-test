#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include "memoryhook.h"

MemoryHook::MemoryHook() {
  malloc_orig_ = malloc_ = reinterpret_cast<MallocFunc>(dlsym(RTLD_NEXT, "malloc"));
  if (malloc_orig_ == nullptr) {
    fprintf(stderr, "[mem] dlsym(\"malloc\") returned nullptr. dlerror = %s\n", dlerror());
    goto _fail;
  }
  free_orig_ = free_ = reinterpret_cast<FreeFunc>(dlsym(RTLD_NEXT, "free"));
  if (free_orig_ == nullptr) {
    fprintf(stderr, "[mem] dlsym(\"free\") returned nullptr. dlerror = %s\n", dlerror());
    goto _fail;
  }
  calloc_orig_ = calloc_ = reinterpret_cast<CallocFunc>(dlsym(RTLD_NEXT, "calloc"));
  if (calloc_orig_ == nullptr) {
    fprintf(stderr, "[mem] dlsym(\"calloc\") returned nullptr. dlerror = %s\n", dlerror());
    goto _fail;
  }
  realloc_orig_ = realloc_ = reinterpret_cast<ReallocFunc>(dlsym(RTLD_NEXT, "realloc"));
  if (realloc_orig_ == nullptr) {
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
  if (malloc_func != nullptr) malloc_ = malloc_func;
  if (free_func != nullptr) free_ = free_func;
  if (calloc_func != nullptr) calloc_ = calloc_func;
  if (realloc_func != nullptr) realloc_ = realloc_func;
}

void MemoryHook::unhook() {
  malloc_  = malloc_orig_;
  free_    = free_orig_;
  calloc_  = calloc_orig_;
  realloc_ = realloc_orig_;
}

MemoryHook &MemoryHook::instance() {
  static MemoryHook instance_;
  return instance_;
}

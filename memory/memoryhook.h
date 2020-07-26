#ifndef MEMORYHOOK_H
#define MEMORYHOOK_H

#include <cstddef>

class MemoryHook {
 protected:
  MemoryHook();
  virtual ~MemoryHook();

 public:
  typedef void *(*MallocFunc) (size_t size);
  typedef void  (*FreeFunc)   (void  *ptr);
  typedef void *(*CallocFunc) (size_t nmemb, size_t size);
  typedef void *(*ReallocFunc)(void  *ptr,   size_t size);

  MallocFunc  malloc_orig_  = nullptr, malloc_  = nullptr;
  FreeFunc    free_orig_    = nullptr, free_    = nullptr;
  CallocFunc  calloc_orig_  = nullptr, calloc_  = nullptr;
  ReallocFunc realloc_orig_ = nullptr, realloc_ = nullptr;

 public:
  void hook(
    MallocFunc malloc_func = nullptr,
    FreeFunc   free_func = nullptr,
    CallocFunc calloc_func = nullptr,
    ReallocFunc realloc_func = nullptr);
  void unhook();

 public:
  static MemoryHook &instance();
};

#endif // MEMORYHOOK_H

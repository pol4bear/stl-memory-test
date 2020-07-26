#ifndef MEMORY_MEMORYHOOK_H
#define MEMORY_MEMORYHOOK_H

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

  MallocFunc  _malloc_orig  = nullptr, _malloc  = nullptr;
  FreeFunc    _free_orig    = nullptr, _free    = nullptr;
  CallocFunc  _calloc_orig  = nullptr, _calloc  = nullptr;
  ReallocFunc _realloc_orig = nullptr, _realloc = nullptr;

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

#endif // MEMORY_MEMORYHOOK_H

#ifndef MEMORY_MEMORY_H_
#define MEMORY_MEMORY_H_

#include "memoryfunc.h"

#undef malloc
#define malloc(SIZE) my_malloc((SIZE), __FILE__, __LINE__)
#undef free
#define free(PTR) my_free((PTR), __FILE__, __LINE__)
#undef calloc
#define calloc(NMEMB, SIZE) my_calloc((NMEMB), (SIZE), __FILE__, __LINE__)
#undef realloc
#define realloc(PTR, SIZE) my_realloc((PTR), (SIZE), __FILE__, __LINE__)

#ifdef __cplusplus

#undef my_new
#define my_new new(__FILE__, __LINE__)
#undef new
#define new my_new

#undef my_delete
#define my_delete delete(__FILE__, __LINE__)
#undef delete
#define delete my_delete

#endif // __cplusplus

#endif // MEMORY_MEMORY_H_

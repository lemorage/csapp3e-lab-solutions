// mymemory.h

#ifndef MYMEMORY_H
#define MYMEMORY_H

#include <stddef.h>

// Initializes the custom memory manager
int mm_init(void);

// Custom malloc function
void *mymalloc(size_t size);

// Custom free function
void myfree(void *bp);

#endif // MYMEMORY_H

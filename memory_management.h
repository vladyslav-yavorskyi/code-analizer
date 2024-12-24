#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdlib.h>
#include "free_analizer.h"

void* increase_memory(void *memory, int *capacity, size_t element_size);

#endif

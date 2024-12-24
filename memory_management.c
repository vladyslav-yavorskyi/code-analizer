#include <stdio.h>
#include "memory_management.h"

void* increase_memory(void *memory, int *capacity, size_t element_size) {
  *capacity *= 2;
  void *temp = realloc(memory, (*capacity) * element_size);

  if (temp == NULL) {
    fprintf(stderr, "Error: Unable to allocate memory\n");
    free(memory);
    exit(EXIT_FAILURE);
  }
  return temp;
}

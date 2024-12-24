#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <stdbool.h>
#include <string.h>
#include "free_analizer.h"
#include "threads_functions.h"



void* analyze_allocation(void *arg) {
  FILE *file = (FILE *)arg;
  int capacity = 4;
  int count_free_errors = 0;

  FreeEntry *free_status_memory = malloc(capacity * sizeof(FreeEntry));
  char line[256];
  int line_number = 0;

  while (fgets(line, sizeof(line), file)) {
    analyze_alloc_free_usage(line, &free_status_memory, &count_free_errors, &capacity, line_number);
    line_number++;
  }

  print_free_errors(free_status_memory, count_free_errors);

  free(free_status_memory);

  return NULL;
}

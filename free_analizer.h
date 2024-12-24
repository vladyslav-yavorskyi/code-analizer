#ifndef ANALIZER_H
#define ANALIZER_H

#include <stdbool.h>

typedef struct free_stuct {
  int line;
  char name[256];
  bool is_free;
} FreeEntry;

bool find_pattern(const char *line, const char *pattern);
void extract_pointer_name(const char *line, const char *pattern, char *pointer_name);
void analyze_alloc_free_usage(char *line, FreeEntry **memory, int *count, int *capacity, int line_number);
bool pointer_name_exists(char name[], FreeEntry *memory, int size);
void print_free_errors(FreeEntry *memory, int size);

#endif

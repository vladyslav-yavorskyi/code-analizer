#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "memory_management.h"
#include "free_analizer.h"

bool pointer_name_exists(char name[], FreeEntry *memory, int size) {
  for (int i = 0; i < size; i++) {
    if (strcmp(memory[i].name, name) == 0) {
      return true;
    }
  }

  return false;
}

bool find_pattern(const char *line, const char *pattern) {
  regex_t regex;
  int reti;

  reti = regcomp(&regex, pattern, REG_EXTENDED);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return false;
  }

  reti = regexec(&regex, line, 0, NULL, 0);
  regfree(&regex);

  return (reti == 0);
}

void extract_pointer_name(const char *line, const char *pattern, char *pointer_name) {
  regex_t regex;
  regmatch_t match[2];


  if (regcomp(&regex, pattern, REG_EXTENDED)) {
    fprintf(stderr, "Could not compile regex\n");
    return;
  }

  if (regexec(&regex, line, 2, match, 0) == 0) {
    int start = match[1].rm_so;
    int end = match[1].rm_eo;
    int len = end - start;

    strncpy(pointer_name, line + start, len);
    pointer_name[len] = '\0';
  } else {
    fprintf(stderr, "Could not extract pointer name\n");
  }

  regfree(&regex);
}

void analyze_alloc_free_usage(char *line, FreeEntry **memory, int *count, int *capacity, int line_number) {
  char *pointer_name = malloc(256 * sizeof(char));  
  
  if (pointer_name == NULL) {
    fprintf(stderr, "Error: Unable to allocate memory\n");
    return;
  }

  if (find_pattern(line, "malloc\\s*\\(.*\\);")) {

    extract_pointer_name(line, "int\\s*\\*?\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*malloc\\s*\\(" , pointer_name); 

    if (pointer_name_exists(pointer_name, *memory, *count)) {
      fprintf(stderr, "Error: Double allocation of memory -> line number: %d\n", line_number);
      return;
    }

    if (*count >= *capacity) {
      *memory = increase_memory(*memory, capacity, sizeof(FreeEntry));
    }


    (*memory)[*count].line = line_number;
    strcpy((*memory)[*count].name, pointer_name);
    (*memory)[*count].is_free = false;
    *count += 1;

  } else if (find_pattern(line, "free\\s*\\(.*\\);")) {
    if (pointer_name == NULL) {
      fprintf(stderr, "Error: Unable to allocate memory\n");
      return;
    }
    extract_pointer_name(line, "free\\s*\\(\\s*([^\\s)]+)\\s*\\)\\s*;" , pointer_name);

    for (int i = 0; i < *count; i++) {
      if (strcmp((*memory)[i].name, pointer_name) == 0) {
        (*memory)[i].is_free = true;
        break;
      }
    }
  }
  free(pointer_name);
  return;
}

void print_free_errors(FreeEntry *memory, int size) {
  for (int i = 0; i < size; i++) {
      fprintf(stderr, "Error %d:\n", i + 1);
      fprintf(stderr, "   Name of pointer: %s\n", memory[i].name);
      fprintf(stderr, "   Memory leak at line %d\n", memory[i].line);
      if (memory[i].is_free == false) {
        fprintf(stderr, "   Memory was NOT freed\n");
      } else {
        fprintf(stderr, "   Memory was freed\n");
      }
    }
}


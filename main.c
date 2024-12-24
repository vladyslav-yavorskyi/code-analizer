#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <stdbool.h>
#include <string.h>
#include "threads_functions.h"



int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
   
  FILE *file = fopen(argv[1], "r");

  if (file == NULL) {
    fprintf(stderr, "Error: Unable to open file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  pthread_t alloc_thread;

  if (pthread_create(&alloc_thread, NULL, analyze_allocation, file)) {
    fprintf(stderr, "Error: Unable to create thread\n");
    return EXIT_FAILURE;
  }
  
  if (pthread_join(alloc_thread, NULL)) {
    fprintf(stderr, "Error: Unable to join thread\n");
    return EXIT_FAILURE;
  }
 
  fclose(file);

  return EXIT_SUCCESS;
}

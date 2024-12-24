#include <stdlib.h>

int main(int argc, char *argv[])
{
  int *ptr = malloc(sizeof(int));
  int *ptr1 = malloc(sizeof(int));
  int *ptr2 = malloc(sizeof(int));
  free(ptr);
  free(ptr1);
  int *ptr3 = malloc(sizeof(int));
  int *ptr4 = malloc(sizeof(int));
  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void)
{
  struct vector v = {
    .data = (int *) malloc(sizeof(int)),
    .sz = 1,
    .cap = 1
  };

  v.data[0] = 0;

  // Insert data
  vector_insert(&v, 1);
  vector_insert(&v, 2);
  vector_insert(&v, 3);

  // Delete data
  vector_delete(&v);

  // Print data (for check valid implement)
  printf("v.data[0] = %d\n", v.data[0]);
  printf("v.data[1] = %d\n", v.data[1]);
  printf("v.data[2] = %d\n", v.data[2]);
  printf("vector size = %d\n", v.sz);
  printf("vector capacity = %d\n", v.cap);

  // Free vector
  vector_free(&v);

  return 0;
}
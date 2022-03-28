#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int *data = (int *) malloc(sizeof(int) * 100);
  data[0] = 0;
  free(data[77]);
  printf("%d\n", data[0]);
  return 0;
}
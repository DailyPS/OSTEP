#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int *tmp = (int *) calloc(1, sizeof(int));
  tmp = NULL;
  printf("%d\n", *tmp);
  free(tmp);
  return 0;
}
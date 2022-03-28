#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
  long PAGESIZE = sysconf(_SC_PAGESIZE); // 4096
  long jump = PAGESIZE / sizeof(int);
  int NUMPAGES = atoi(argv[1]);
  int trial = atoi(argv[2]);

  printf("%ld", PAGESIZE);
  printf("\n");

  int *a = calloc(NUMPAGES, PAGESIZE);
  struct timespec s, e;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &s);

  for (int t = 0; t < trial; t++)
  {
    for (int i = 0; i < NUMPAGES * jump; i += jump)
      a[i] += 1;
  }

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &e);

  printf("%lf\n", ((e.tv_sec - s.tv_sec) * 1e9 + (e.tv_nsec - s.tv_nsec)) / (trial * NUMPAGES));

  free(a);

  return 0;
}
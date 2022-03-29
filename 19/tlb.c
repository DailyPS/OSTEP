#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
  long PAGESIZE = sysconf(_SC_PAGESIZE); // 4096
  long jump = PAGESIZE / sizeof(int); // 1024
  int NUMPAGES = atoi(argv[1]);
  int trial = atoi(argv[2]);

  int *a = calloc(NUMPAGES, PAGESIZE); // Initialize
  struct timespec s, e;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &s); // strat check running time

  for (int t = 0; t < trial; t++)
  {
    for (int i = 0; i < NUMPAGES * jump; i += jump)
      a[i] += 1;
  }

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &e); // end check running time

  printf("%lf\n", ((e.tv_sec - s.tv_sec) * 1e9 + (e.tv_nsec - s.tv_nsec)) / (trial * NUMPAGES));

  free(a);

  return 0;
}
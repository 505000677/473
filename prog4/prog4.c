#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include "check.h"

int x[5] = {1,2,3,4,5};

void allocate()
{
    int i;
    int *p;
    for(i =1 ; i<1000000 ; i++)
    {
      p = malloc(500 * sizeof(int));
      if(func(i)) { free (p);}
    }
}

void allocate1()
{
  int i;
  int *p;
  for (i=1 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    if(i & 1)
      free (p);
  }
}

void allocate2()
{
  int i;
  int *p;
  for (i=1 ; i<300000 ; i++)
  {
    p = malloc(10000 * sizeof(int));
    free (p);
  }
}


int main(int argc, char const *argv[]) {
  int i;
  int *p;
  struct timeval ru_stime, ru_utime;
  struct rusage u;
  getrusage(RUSAGE_SELF, &u);
  ru_stime = u.ru_stime;
  ru_utime = u.ru_utime;
  
  printf("Executing the code ......\n");
  allocate();

  for (i=0 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    free (p);
  }
  getrusage(RUSAGE_SELF, &u);
  ru_stime.tv_sec -= u.ru_stime.tv_sec;
  ru_utime.tv_sec -= u.ru_utime.tv_sec;
  ru_stime.tv_usec -= u.ru_stime.tv_usec;
  ru_utime.tv_usec -= u.ru_utime.tv_usec;
  printf("i. Sys time: %li.%06li\n", -ru_stime.tv_sec, -ru_stime.tv_usec);
  printf("ii. Usr time: %li.%06li\n", -ru_utime.tv_sec, -ru_utime.tv_usec);
  printf("iii. Max resident set size: %li\n", u.ru_maxrss);
  printf("iii. Signals received: %li\n", u.ru_nsignals);
  printf("iv, v. Context switches (voluntary and involuntary): %li, %li\n",
	 u.ru_nvcsw, u.ru_nivcsw);
  printf("Program execution successfull\n");
  return 0;
}

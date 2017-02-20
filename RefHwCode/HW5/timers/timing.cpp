// A reference code for including timers in code.
// Based on timing code from Martin Herbordt's class, EC527.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define GIG 1000000000

timespec diff(timespec start, timespec end)
{
  timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0)
  {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}

double dot(double* v1, double* v2, long size)
{
  double retval = 0.0;
  for (int i = 0; i < size; i++)
  {
    retval += v1[i]*v2[i];
  }
  return retval;
}

int main(int argc, char** argv)
{
  // Iterators.
  int i;
  long j;

  // Timing structures.
  timespec time1, time2, timediff; 

  // Try array sizes from 32 to 1024*1024*128 in factors of 4 steps.
  const long maxelem = 1024*1024*128;
  const long startelem = 32;
  const long step = 4;

  // Timing storage.
  std::vector<double> timing_list;

  // Data vectors.
  double* v1 = new double[maxelem];
  double* v2 = new double[maxelem];

  // Initialize in some uninteresting way.
  for (i = 0; i < maxelem; i++)
  {
    v1[i] = i;
    v2[i] = i;
  }

  // Begin testing.
  for (j = startelem; j <= maxelem; j *= step)
  {
    // Start timer.
    clock_gettime(CLOCK_REALTIME, &time1);

    // Do operation.
    double soln = dot(v1, v2, j);

    // End timer.
    clock_gettime(CLOCK_REALTIME, &time2);

    // Get difference.
    timediff = diff(time1, time2);

    // Save time in seconds to vector.
    timing_list.push_back(((double)GIG * (double)timediff.tv_sec + (double)timediff.tv_nsec)/((double)GIG));

    // Print.
    printf("Size %ld is done. The result was %.15e\n", j, soln);
  }

  // Print timings.
  int counter = 0;
  for (j = startelem; j <= maxelem; j*=step)
  {
    printf("%ld %.8e\n", j, timing_list[counter]);
    counter++;
  }

  // Clean up.
  delete[] v1;
  delete[] v2;
}



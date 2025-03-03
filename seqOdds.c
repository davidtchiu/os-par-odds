#include "rtclock.h"
#include <stdlib.h>
#include <stdio.h>

const long N = 100000000;
int *array; // points to the array of ints on the heap

/**
 * Main function
 */
int main() {

  srand(0);    // "seed" the random number generator
  array = (int*) malloc(sizeof(int)*N);
  for (int i = 0; i < N; i++) {
      array[i] = rand();
  }

  double start = rtclock(); // start stopwatch

  int count = 0;
  for (int i = 0; i < N; i++) {
      if (array[i] % 2 == 1) {
          count++;
      }
  }
  
  double end = rtclock(); // stop stopwatch

  printf("Total count: %d\n", count);
  printf("Time: %.6f sec\n", ((end - start)));

  return 0;
}
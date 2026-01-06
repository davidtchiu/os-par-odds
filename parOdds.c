#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "parOdds.h"
#include "rtclock.h"

/**
 * Global (shared) variables
 */
const long N = 100000000;
int *array; // points to the array of ints on the heap
int *results; 

/**
 * Worker threads do this function
 */
void* worker(void *param) {
    int *whoAmI = param; // either thread 0 or 1

    int begin = (*whoAmI % 2 == 0) ? 0 : N/2;
    int end =   (*whoAmI % 2 == 0) ? N/2 : N;
    printf("thread %d start at [%d] and end at [%d]\n", *whoAmI, begin, end-1);

    int count = 0;
    for (int i = begin; i < end; i++) {
        if (array[i] % 2 == 1) {
            count++;
        }
    }
    results[*whoAmI] = count;
    return NULL;
}

/**
 * Main thread
 */
int main(int argc, char *argv[]) {
    srand(0);    // "seed" the random number generator
    array = (int*) malloc(sizeof(int)*N);
    for (int i = 0; i < N; i++) {
        array[i] = rand();
    }
    
    double start = rtclock(); // start stopwatch

    // malloc an array for threads to deposit their results
    results = (int*) malloc(sizeof(int) * 2);

    // spawn 2 worker threads
    pthread_t myThreads[2];
    int tid[2];
    for (int i = 0; i < 2; i++) {
        tid[i] = i;
       pthread_create(&myThreads[i], NULL, worker, &tid[i]);
    }

    // wait for all the threads to finish
    int sum = 0;
    for (int i = 0; i < 2; i++) {
        pthread_join(myThreads[i], NULL);
        sum += results[i];
    }
    printf("Total count: %d\n", sum);
    free(results);
    free(array);

    double end = rtclock(); // start stopwatch
    printf("Time: %.6f sec\n", ((end - start)));

    return 0;
}

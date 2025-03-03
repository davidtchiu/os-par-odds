#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "parOdds.h"
#include "rtclock.h"
const long N = 100000000;
int *array; // points to the array of ints on the heap
int *results; 

void* worker(void *param) {
    int *whoAmI = (int*) param; // either thread 0 or 1

    int begin = (*whoAmI % 2 == 0) ? 0 : N/2;
    int end =   (*whoAmI % 2 == 0) ? N/2 : N;
    //printf("thread %d start at [%d] and end at [%d]\n", *whoAmI, begin, end);

    int count = 0;
    for (int i = begin; i < end; i++) {
        if (array[i] % 2 == 1) {
            count++;
        }
    }
    results[*whoAmI] = count;
    free(param);
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

    // spin up the two worker threads!
    pthread_t tid[2];
    for (int i = 0; i < 2; i++) {
        int *threadID = (int*) malloc(sizeof(int));
        *threadID = i;
        pthread_create(&tid[i], NULL, worker, threadID);
    }

    // wait for all the threads to finish
    int sum = 0;
    for (int i = 0; i < 2; i++) {
        pthread_join(tid[i], NULL);
        sum += results[i];
    }
    printf("Total count: %d\n", sum);
    free(results);
    free(array);

    double end = rtclock(); // start stopwatch
    printf("Time: %.6f sec\n", ((end - start)));

    return 0;
}

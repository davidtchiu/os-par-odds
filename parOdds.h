/** struct to hold parameters to partialSum() **/
typedef struct thread_args {
  int tid;    // the given thread id (0, 1, ...)
  long begin; // where to begin summation
  long end;   // where to end summation
} thread_args;

/** Function delcarations */
void *partialOddsCount(void *args);

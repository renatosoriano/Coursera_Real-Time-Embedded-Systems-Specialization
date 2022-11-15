#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
/* Including syslog.h in order to be able to call openlog and syslog
 * functions */
#include <syslog.h>

// Specified number of threads for this assignment: 1
#define NUM_THREADS 1

// Structure required by pthread_create
typedef struct
{
    int threadIdx;
} threadParams_t;

// POSIX thread declarations and scheduling attributes
pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];

// Entry point function for the thread execution
void *pthread(void *threadp) 
{

    /* In this particular exercise, the information provided by the 
    * argument threadp is not useful, as the only action to be taken
    * is to print a statement in the syslog without any relevant
    * thread information*/
    
    // string to log in the syslog file from the created thread
    syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:1] Hello World from Thread!\n");
}

int main (int argc, char *argv[])
{
   // The index of our for loop
   int i = 0;

   // string to log in the syslog file from the main thread
   syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:1] Hello World from Main!\n");

   /* The for loop is a bit useless in this excercise, as we are going
   * to spawn only a single thread (NUM_THREADS is equal to 1). However, 
   * the code from the example will still work, so i decided to leave 
   * the for loop*/
   for(i=0; i < NUM_THREADS; i++)
   {
       // Initialize the threadParams structure with the index of the current thread
       threadParams[i].threadIdx=i;

       // Creates the thread
       pthread_create(&threads[i],   // pointer to thread descriptor
                      (void *)0,     // use default attributes
                      pthread, // thread function entry point
                      (void *)&(threadParams[i]) // parameters to pass in
                     );
   }

   for(i=0;i<NUM_THREADS;i++)
       pthread_join(threads[i], NULL);

   printf("TEST COMPLETE\n");

   closelog();

}

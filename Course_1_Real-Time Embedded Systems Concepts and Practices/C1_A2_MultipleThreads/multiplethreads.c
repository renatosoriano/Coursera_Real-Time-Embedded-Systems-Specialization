#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
/* Including syslog.h in order to be able to call openlog and syslog
 * functions */
#include <syslog.h>

// Specified number of threads for this assignment: 128
#define THREAD_COUNT 128

// Structure required by pthread_create
typedef struct
{
	int threadIdx;
} threadParams_t;

// POSIX thread declarations and scheduling attributes
pthread_t threads[THREAD_COUNT];
threadParams_t threadParams[THREAD_COUNT];

/* Entry point function for the spawned thread. Will sum the information carried
 * by the threadp structure to provide information about the thread
 * being executed */
void* counterThread(void* threadp)
{
	int i;
    int gsum = 0;
	threadParams_t* threadParams = (threadParams_t*)threadp;

   /* Performs sum calculation based on the parameter carried by the
    * input structure threadParams */
	for (i = 0; i <= threadParams->threadIdx; i++)
	{
		gsum += i;
	}
 
    // Provides syslog message as requested by the assignment
    syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:2]: Thread idx=%d, sum[1...%d]=%d\n", threadParams->threadIdx, threadParams->threadIdx, gsum);
}

int main(int argc, char* argv[])
{
	// The index of our for loop
	int i;
 
    /* Loop over the 128 items of the threadParams array to spawn the
    * respective thread and associate to it the entry point function
    * counterThread */
    for (i = 0; i < THREAD_COUNT; i++)
    {

	  // Initialize the threadParams structure with the index of the current thread
      threadParams[i].threadIdx = i;
	  // Creates the thread
  	  pthread_create(&threads[i],			// pointer to thread descriptor
  	    	(void*)0,						// use default attributes
  		    counterThread,					// thread function entry point
  		    (void*)&(threadParams[i]));		// parameters to pass in
    }

    // Join all the NUM_THREAD (128 in this case) before exiting the program
	for (i = 0; i < THREAD_COUNT; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("TEST COMPLETE\n");
	closelog();
}
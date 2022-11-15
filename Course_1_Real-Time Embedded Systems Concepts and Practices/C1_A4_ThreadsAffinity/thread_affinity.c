#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>
/* Including syslog.h in order to be able to call openlog and syslog
 * functions */
#include <syslog.h>

// Specified number of threads for this assignment: 128
#define NUM_THREADS 128
// Specified CPU affinity: 3
#define CPU_AFFINITY 3

// Structure required by pthread_create
typedef struct
{
	int threadIdx;
} threadParams_t;

// POSIX thread declarations and scheduling attributes
pthread_t threads[NUM_THREADS];
pthread_t startthread;
threadParams_t threadParams[NUM_THREADS];

// Thread attribute variable, such as scheduling policy or thread stack-size
pthread_attr_t fifo_sched_attr; 
// Only one parameter is supported in 'struct sched_param' : int sched_priority
struct sched_param fifo_param;

#define SCHED_POLICY SCHED_FIFO

void print_scheduling_policy(void){

  int schedType = sched_getscheduler(getpid());
  switch(schedType){
    case SCHED_FIFO:
      printf("Pthread policy is SCHED_FIFO\n");
      break;
    case SCHED_OTHER:
      printf("Pthread policy is SCHED_OTHER\n");
      break;
    case SCHED_RR:
      printf("Pthread policy is SCHED_RR\n");
      break;
    default:
      printf("Pthread policy is UNKNOWN (%d)\n", schedType);
      break;
  }

}

void set_scheduler(void){

  int max_prio, cpuidx;
  cpu_set_t cpuset;
  
  printf("INIITAL ");
  print_scheduling_policy();

  // Initialises the fifo_sched_attr variable to default settings
  pthread_attr_init(&fifo_sched_attr);
  
  /* The inherit-scheduler attribute determines whether a thread created using the
   * thread attributes object attr will inherit its scheduling
   * attributes from the calling thread or whether it will take them
   * from attr.
   * 
   * When using PTHREAD_EXPLICIT_SCHED, threads that are created using 
   * attr take their scheduling attributes from the values specified 
   * by the attributes object */
  pthread_attr_setinheritsched(&fifo_sched_attr, PTHREAD_EXPLICIT_SCHED);
  
  // Sets the scheduling policy to SCHED_FIFO
  pthread_attr_setschedpolicy(&fifo_sched_attr, SCHED_POLICY);
  
  CPU_ZERO(&cpuset); // Clears the cpuset variables, so that it contains no CPU
  cpuidx=(CPU_AFFINITY);  // add CPU number 3 (CPU affinity) to CPU set
  CPU_SET(cpuidx, &cpuset); // Set the CPU set to the indicated cpuidx
  
  // Uses the cpuset to set the thread affinity attribute to the predefined core
  pthread_attr_setaffinity_np(&fifo_sched_attr, sizeof(cpu_set_t), &cpuset);
  
  // Returns  the  maximum  priority value that can be used with the scheduling algorithm
  max_prio = sched_get_priority_max(SCHED_POLICY);
  
  // Sets the priority to the max_prio value got at the line before
  fifo_param.sched_priority = max_prio;
  
  /*  Sets both the scheduling policy and parameters for the thread whose
   *  ID is specified in pid */ 
  if(sched_setscheduler(getpid(), SCHED_POLICY, &fifo_param) < 0){
    perror("sched_setscheduler");
  }
  
  /* Sets the scheduling  parameter  attributes  of  the  thread  attributes  
   * object referred to by attr to the values specified in the buffer pointed to by param */
  pthread_attr_setschedparam(&fifo_sched_attr, &fifo_param);
  
  printf("ADJUSTED ");
  print_scheduling_policy();
  
}

/* Entry point function for the spawned thread. Will sum the information carried
 * by the threadp structure to provide information about the thread
 * being executed */
void* counterThread(void* threadp)
{
	int i;
  int gsum = 0;
	threadParams_t* threadParams = (threadParams_t*)threadp;
  struct sched_param schedParam;

   /* Performs sum calculation based on the parameter carried by the
    * input structure threadParams */
	for (i = 1; i <= threadParams->threadIdx+1; i++)
	{
		gsum += i;
	}

  sched_getparam(0, &schedParam);

  printf("Thread idx=%d, sum[0...%d]=%d, Running on core : %d Priority: %d\n", 
     threadParams->threadIdx,
     threadParams->threadIdx,
     gsum,
     sched_getcpu(),
     schedParam.sched_priority
    );

  // Provides syslog message as requested by the assignment
  syslog(LOG_DEBUG, "Thread idx=%d, sum[0...%d]=%d Running on core : %d\n", 
     threadParams->threadIdx, 
     threadParams->threadIdx, 
     gsum, 
     sched_getcpu()
    );
}

/* Entry point for the start thread that will create the remaining threads */
void starterThread(void *threadp)
{
   int i;
   printf("Starter thread running on CPU = %d\n", sched_getcpu());

   for(i=0; i < NUM_THREADS; i++)
   {
       threadParams[i].threadIdx=i;

       pthread_create(&threads[i],   				// pointer to thread descriptor
                      &fifo_sched_attr,     		// use FIFO RT max priority attributes
                      (void *)&counterThread, 		// thread function entry point
                      (void *)&(threadParams[i]) 	// parameters to pass in
                     );
   }

   for(i=0;i<NUM_THREADS;i++)
   {
		pthread_join(threads[i], NULL);
   }
       
}


int main(int argc, char* argv[])
{
    // Sets the scheduler according to configuraiton
    set_scheduler();

    openlog ("[COURSE:1][ASSIGNMENT:4]", LOG_NDELAY, LOG_USER);

	// Creates the thread
    pthread_create(&startthread,   			// pointer to thread descriptor
                  &fifo_sched_attr,     	// use FIFO RT max priority attributes
                  (void *)&starterThread, 	// thread function entry point
                  (void *)0 				// parameters to pass in
                 );

    pthread_join(startthread, NULL);
    printf("\nTEST COMPLETE\n");

	closelog();
}
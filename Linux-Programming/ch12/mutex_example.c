/*
This file is a mutex demo using pthread library in Linux.
@author   曾健平
@time	  2015-9-22
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

static void *thread_function(void *arg);

/* global mutex. */
pthread_mutex_t work_mutex;

#define WORK_SIZE    1024
/* global shared data area */
char workArea[WORK_SIZE];

static int time_to_exit = 0;

void mainThread();


int main(int argc, char* argv[])
{
	
	int res = pthread_mutex_init(&work_mutex, NULL);
	if (res != 0)
	{
		printf("Mutex initilization failed.\n");
		exit(EXIT_FAILURE);
	}
	
	// enter main thread
	mainThread();
	return 0;
}

void* thread_function(void* arg)
{
	sleep(1);
	pthread_mutex_lock(&work_mutex);

	/* get string deriving from stdin, the loop will finished until occur 'end' */
	while (strncmp("end", workArea, 3) != 0)
	{
		printf("The length of inputed character is: \n", strlen(workArea) - 1);
		printf("The inputed character is: %s\n", workArea);
		// tell main thread that the character is inputed.	
		workArea[0] = '\0';
		pthread_mutex_unlock(&work_mutex);
		sleep(1);
		
		pthread_mutex_lock(&work_mutex);
		while(workArea[0] == '\0')
		{
			pthread_mutex_unlock(&work_mutex);
			sleep(1);
			pthread_mutex_lock(&work_mutex);
		}
		
	}

	time_to_exit = 1;
	workArea[0] = '\0';
	pthread_mutex_unlock(&work_mutex);
	pthread_exit(0);
}


/*A function executed at Main thread. */
void mainThread()
{
	pthread_t thd;
	int res = pthread_create(&thd, NULL, thread_function, NULL);
	if (res != 0)
	{
		printf("Thread ceate failed.\n");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_lock(&work_mutex);
	printf("Input any text. Enter 'end' to finish.\n");
	while (!time_to_exit)
	{
		fgets(workArea, WORK_SIZE, stdin);
		pthread_mutex_lock(&work_mutex);
		if (workArea[0] != '\0')
		{
			pthread_mutex_unlock(&work_mutex);	
			sleep(1);

		}		
		else 
			break;
	}
	
	//unlock
	pthread_mutex_unlock(&work_mutex);
	
	printf("\nWaiting for sub thread to finish.\n");
	void** result;
	res = pthread_join(thd, result);
	if (res != 0)
	{
		printf("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}
	
	printf("thread join finished.\n");

	/* destroy mutex lock. */
	pthread_mutex_destroy(&work_mutex);
	exit(EXIT_SUCCESS);
}

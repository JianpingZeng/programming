#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

#define OVER	-1

/* define buffer size */
#define BUFFER_SIZE		2

typedef struct producons
{
	// A buffer where data storage
	int buffer[BUFFER_SIZE];
	// a mutex lock
	pthread_mutex_t lock;
	// a position to read and write respectively.
	int readpos, writepos;
	// conditional variable.
	pthread_cond_t notempty;
	pthread_cond_t notfull;
}producons;


/* A buffer where data storages.*/
static producons buffer;

/*Initialize a buffer.*/
void init(producons *prod)
{
	/* initialize the mutex lock and conditional varibal with default setting.*/
	pthread_mutex_init(&prod->lock, NULL);
	pthread_cond_init(&prod->notempty, NULL);
	pthread_cond_init(&prod->notfull, NULL);

	prod->readpos = 0;
	prod->writepos = 0;
}

/* Puts an integer into buffer.*/
void put(producons *prod, int data)
{
	
	while (prod->readpos == (prod->writepos + 1) % BUFFER_SIZE)
	{
		printf("Producer is waiting for buffer not full.\n");
		pthread_cond_wait(&prod->notfull, &prod->lock);
	}

	pthread_mutex_lock(&prod->lock);

	// write data into buffer.
	prod->buffer[prod->writepos++] = data;
	// reset wirting position if writepos reach the end of buffer.
	if (prod->writepos >= BUFFER_SIZE)
	{
		prod->writepos = 0;
	}

	pthread_cond_signal(&prod->notempty);
	pthread_mutex_unlock(&prod->lock);
}

/* Reads and remove an integer from the buffer.*/
int get(producons *prod)
{
	int data;
	while (prod->writepos == prod->readpos)
	{
		printf("Consumer is waiting for buffer not empty.\n");
		pthread_cond_wait(&prod->notempty, &prod->lock);
	}
	pthread_mutex_lock(&prod->lock);
	/* Reads data from buffer.*/
	data = prod->buffer[prod->readpos++];
	
	// reset read position if it reachs the end of buffer.
	if (prod->readpos >= BUFFER_SIZE)
		prod->readpos = 0;

	pthread_cond_signal(&prod->notfull);
	pthread_mutex_unlock(&prod->lock);
	return data;
}

/* Writing -1 into buffer which stops consumer.*/
void sig_alarm(int arg)
{
	put(&buffer, -1);
}


/**    Producer thread       *****/
void* producer(void* data)
{
	int n = 1;
	signal(SIGALRM, sig_alarm);	
	// set a timer with 120 second, when it time out, 
	// sending a signal to producer that producing a data '-1'.
	alarm(120);
	while (1)
	{
		// produce a product per 1s.
		printf("Producer sleep 1 second......\n");
		sleep(1);
		printf("Put the %d-th product\n", n++);
		put(&buffer, n);
	}
}

/**    Producer thread       *****/
void* consumer(void* data)
{
	int n = 1;
	while (1)
	{
		// produce a product per 1s.
		printf("Consumer sleep 2 second......\n");
		sleep(2);
		int data = get(&buffer);
		printf("Get the %d product\n", data);
		if (data == OVER)
			break;
	}
	printf("Consumer finished.\n");
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t thdA, thdB;
	init(&buffer);

	//Creates a thread as producer.
	pthread_create(&thdA, NULL, producer, 0);

	//Creates a thread as consumer.
	pthread_create(&thdB, NULL, consumer, 0);

	/* main thread waits until all of sub thread finished. */
	pthread_join(thdA, NULL);
	pthread_join(thdB, NULL);

	// destroy all of conditional varible
	pthread_cond_destroy(&buffer.notfull);

	pthread_cond_destroy(&buffer.notempty);
	return 0;
}

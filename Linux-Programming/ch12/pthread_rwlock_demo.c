#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/pthreadtypes.h>

/* defines the size of global buffer*/
#define WORK_SIZE	1024

/* A read write lock object. */
static pthread_rwlock_t rwlock;
/* a work buffer. */
char workBuffer[WORK_SIZE];
/* time to exit. */
int timeToExit;

/* the first reader thread.*/
void* firstReaderThread(void* arg);
/* the second reader thread.*/
void* secondReaderThread(void* arg);
/* the first writer thread.*/
void* firstWriterThread(void* arg);
/* the second writer thread.*/
void* secondWriterThread(void* arg);


/* main function. */
void main()
{
	pthread_t firstReader, secondReader, firstWriter, secondWriter;
	void* threadResult;
	// initialize the reading writing lock.
	int res = pthread_rwlock_init(&rwlock, NULL);
	if (res != 0)
	{
		perror("读写锁初始化失败。");
		exit(EXIT_FAILURE);
	}
	
	// creates a reader thread
	res = pthread_create(&firstReader, NULL, firstReaderThread, NULL);

	if (res != 0)
	{
		perror("创建一个读线程失败。");
		exit(EXIT_FAILURE);
	}

	
	// creates a reader thread
	res = pthread_create(&secondReader, NULL, secondReaderThread, NULL);

	if (res != 0)
	{
		perror("创建第二个读线程失败。");
		exit(EXIT_FAILURE);
	}

 	res = pthread_create(&firstWriter, NULL, firstWriterThread, NULL);	
	if (res != 0)
	{
		perror("创建第一个写线程失败。");
		exit(EXIT_FAILURE);
	}
	
	
 	res = pthread_create(&secondWriter, NULL, secondWriterThread, NULL);	
	if (res != 0)
	{
		perror("创建第二个写线程失败。");
		exit(EXIT_FAILURE);
	}

	// 得到所有的线程都结束
	res = pthread_join(firstReader, &threadResult);
	if (res != 0)
	{
		perror("线程同步失败。");
		exit(EXIT_FAILURE);
	}
	
	
	res = pthread_join(secondReader, &threadResult);
	if (res != 0)
	{
		perror("线程同步失败。");
		exit(EXIT_FAILURE);
	}

	
	res = pthread_join(firstWriter, &threadResult);
	if (res != 0)
	{
		perror("线程同步失败。");
		exit(EXIT_FAILURE);
	}

	
	res = pthread_join(secondWriter, &threadResult);
	if (res != 0)
	{
		perror("线程同步失败。");
		exit(EXIT_FAILURE);
	}

	// 销毁读写锁	
	pthread_rwlock_destroy(&rwlock);
	exit(EXIT_FAILURE);
}

/* the first reader thread.*/
void* firstReaderThread(void* arg)
{
	printf("第一个试图去获取锁的读线程。\n");
	// 获取读锁
	pthread_rwlock_rdlock(&rwlock);	
	// 输入end，则该线程停止运行
	while (strncmp("end", workBuffer, 3) != 0)
	{
		printf("1号读线程进入时，读取到的数据。");
		printf("从缓冲区读取到的数据为：%s\n", workBuffer);
		// 释放锁
		pthread_rwlock_unlock(&rwlock);
		sleep(2);
		
		pthread_rwlock_rdlock(&rwlock);
		// 当缓冲区不为空，则循环读取缓冲区中的数据
		while (workBuffer[0] != '\0')
		{
			pthread_rwlock_unlock(&rwlock);			
			sleep(2);
			
			pthread_rwlock_rdlock(&rwlock);
		}
	}
	
	pthread_rwlock_unlock(&rwlock);
	timeToExit = 1;
	pthread_exit(0);
}
/* the second reader thread.*/
void* secondReaderThread(void* arg)
{
	
	printf("第二个试图去获取锁的读线程。\n");
	// 获取读锁
	pthread_rwlock_rdlock(&rwlock);	
	// 输入end，则该线程停止运行
	while (strncmp("end", workBuffer, 3) != 0)
	{
		printf("2号读线程进入时，读取到的数据。");
		printf("从缓冲区读取到的数据为：%s\n", workBuffer);
		// 释放锁
		pthread_rwlock_unlock(&rwlock);
		sleep(2);
		
		pthread_rwlock_rdlock(&rwlock);
		// 当缓冲区不为空，则循环读取缓冲区中的数据
		while (workBuffer[0] != '\0')
		{
			pthread_rwlock_unlock(&rwlock);			
			sleep(5);
			
			pthread_rwlock_rdlock(&rwlock);
		}
	}
	pthread_rwlock_unlock(&rwlock);
	timeToExit = 1;
	pthread_exit(0);
}
/* the first writer thread.*/
void* firstWriterThread(void* arg)
{
	printf("这是第一个试图获取写锁的1号写线程。\n");	
	while(!timeToExit)
	{
		// 获取写锁
		pthread_rwlock_wrlock(&rwlock);
		printf("这是1号写线程。\n请输入一串字符。以end结束。\n");
		// 得到输入的字符串
		fgets(workBuffer, WORK_SIZE, stdin);
		pthread_rwlock_unlock(&rwlock);
		sleep(15);
	}
	pthread_exit(0);
}
/* the second writer thread.*/
void* secondWriterThread(void* arg)
{
	
	printf("这是第二个试图获取写锁的2号写线程。\n");	
	while(!timeToExit)
	{
		// 获取写锁
		pthread_rwlock_wrlock(&rwlock);
		printf("这是2号写线程。\n请输入一串字符。以end结束。\n");
		// 得到输入的字符串
		fgets(workBuffer, WORK_SIZE, stdin);
		pthread_rwlock_unlock(&rwlock);
		sleep(20);
	}
	pthread_exit(0);
}


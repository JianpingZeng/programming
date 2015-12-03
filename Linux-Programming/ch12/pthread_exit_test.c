#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *hello(char* argv)
{
	int *p;
	p = (int*)malloc(sizeof(int) * 10);
	printf("The message is '%s'\n", argv);
	printf("The child id is %u\n", pthread_self());
	memset(p, 'c', 10);
	
	/* Print the address of p, in order to test equlaity in main thread. */
	printf("p = %x\n", p);
	
	/*pointer to int array must be freed before exit. */
	// free statement be commented, to be returned.
	//free(p);

	pthread_exit(p);

}
int main(int argc, char* argv[])
{
	int error;
	int *temptr;
	pthread_t thd;
	pthread_create(&thd, NULL, (void*) *hello, "This is a pthread demo.");
	
	if ((error = pthread_join(thd, (void **)&temptr)) < 0 )
	{
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
	
	/*Generally, the address of temptr is equal to pointer p in hello thread.*/
	printf("temptr = %x, *temptr = %c\n", temptr, *temptr);	
	*temptr = 'd';
	printf("%c\n", temptr);
	free(temptr);
	
	return 0;
}

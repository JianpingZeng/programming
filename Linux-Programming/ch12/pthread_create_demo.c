#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
 
struct message
{ int i; int j; };

void* hello(struct message* msg)
{
	printf("This is child thread, tid = %lu, pid = %ld\n", pthread_self(), syscall(SYS_gettid));
	printf("The arg.i is %d, arg.j is %d\n", msg->i, msg->j);
	while(1);
}

int main(int argc, char* argv[])
{
	struct message test_msg;
	pthread_t thread_id;
	test_msg.i = 10;
	test_msg.j = 20;
	// To create a thread.
	pthread_create(&thread_id, NULL, (void *)*hello, &test_msg);
	printf("parent, the tid = %lu, pid = %ld\n", pthread_self(), syscall(SYS_gettid));
	pthread_join(thread_id, NULL);
	return 0;
}

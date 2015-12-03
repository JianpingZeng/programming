#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BITS	3

static char* perm[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

int main(int argc, char* argv[])
{
	unsigned int mask = 0700;
	if (argc > 1)
	{
		struct stat* buff = (struct stat*)malloc(sizeof(struct stat));
		// reads permission info.
		if ( stat(argv[1], buff) != -1)
		{
			printf("permissions for %s\t", argv[1]);
			for(int i=2; i >= 0; i--)
			{
				printf("%3s", perm[(buff->st_mode &mask) >> i*BITS]);
				mask >>=BITS;
			}
			// return carriage.
			putchar('\n');
		}
		else 
		{
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
	}
	else 
	{
		fprintf(stderr, "Usage: %s file_name", argv[0]);
	}
	return 0;
}

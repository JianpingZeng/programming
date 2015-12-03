#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE	128

int main(int argc, char* argv[])
{
	char buff[BUFFSIZE];
	//initialize buff array with '\0'
	memset(buff, '\0', BUFFSIZE);
	// delete linked file named with sym_link_test
	unlink("sym_link_test");
	if (symlink(argv[1], "sym_link_test") < 0)
	{
		perror("symlink");
		exit(EXIT_FAILURE);
	}
	if (readlink("./sym_link_test", buff, BUFFSIZE) < 0)
	{
		perror("readlink");
		exit(EXIT_FAILURE);
	}
	printf("sym_link_test is the symbol link of %s\n", buff);
	// call system funtion to print basic information.
	system("ls -l sym_link_test");
	return 0;
}

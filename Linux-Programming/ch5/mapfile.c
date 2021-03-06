#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	// gets size of page.
	int pagesize = getpagesize();
	// open a file
	int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	// gets the lenght of file by using lseek funtion.
	int length = lseek(fd, 0, SEEK_END);
	lseek(fd, (pagesize * 2 - length%pagesize - 1), SEEK_END);
	write(fd, "-1", 1);
	// get the start address of mapped space.
	char* mapped_mem = mmap(NULL, length / pagesize + 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	printf("Please input a string which will be inserted into target file, (size must lower than %d):", pagesize);
	
	char buff[pagesize];
	// gets a string from standard input. equilent to fgets(buf, pagesize, stdin);
	fgets(buff, pagesize, stdin);
	
	printf("Please input a position where some data will be inserted, postition(must lower than filesize %d) = ", length);
	int position = 0;
	scanf("%d", &position);
	// move all data after target position where data will be inserted.
	memmove(mapped_mem + position + strlen(buff), mapped_mem + position, length - position);
	// insert data into target position
	memcpy(mapped_mem + position, buff, strlen(buff) - 1);
	// write back file into disk.
	msync(mapped_mem, length / pagesize + 2, MS_SYNC|MS_INVALIDATE);
	munmap(mapped_mem, length / pagesize + 2);
	// truncate file
	ftruncate(fd, length + strlen(buff));
system(cat ./mapfile.c); 	return 0;
}

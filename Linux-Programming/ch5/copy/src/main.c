#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include "copy.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s src_dir dest_dir\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	struct stat stat_src;
	if (stat(argv[1], &stat_src) != 0)
	{
		fprintf(stderr, "%s(%d): stat error (%s)!\n", __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	umask(0000);
	// if source file is regular file rather than a directory.
	if (S_ISREG(stat_src.st_mode))
	{
		struct stat stat_dest;
		// if target file is not exist.
		if (stat(argv[2], &stat_dest) == -1)
		{
			if (errno != ENOENT)
			{
				fprintf(stderr, "%s(%d): stat error (%s)!\n", __FILE__, __LINE__, strerror(errno));
				exit(EXIT_FAILURE);
			}
			else 
			{
				cp_file(argv[1], argv[2], stat_src.st_mode);
			}
		}
		else 		
		{
			// if target file is directory
			if (S_ISDIR(stat_dest.st_mode))
			{
				char* ptr = (char*)malloc(strlen(argv[1]) + 1 + strlen(argv[2]) + 1);
				sprintf(ptr, "%s/%s\0", argv[2], argv[1]);
				cp_file(argv[1], ptr, stat_src.st_mode);
				free(ptr);
			}
			// otherwise, target is regular file.
			else 
			{
				printf("file %s is exist, do you wanna overwrite it[Y/N] ?", argv[2]);
				char ch;
				while(!scanf("%c", &ch))
				{
					getchar();
				}
				if (ch == 'Y' || ch=='y')
				{
					// delete target if user wanna overwrite it.
					unlink(argv[2]);
					// copy file
					cp_file(argv[1], argv[2], stat_src.st_mode);
				}
				else return 1;				
			}
		}
	}
	
	// if source file regular file
	else if (S_ISDIR(stat_src.st_mode))
	{
		struct stat stat_dest;
		// if target file is not exist.
		if (stat(argv[2], &stat_dest) == -1)
		{
			if (errno != ENOENT)
			{
				fprintf(stderr, "%s(%d): stat error (%s)!\n", __FILE__, __LINE__, strerror(errno));
				exit(EXIT_FAILURE);
			}
			else 
			{
				errno = 0;
				if (mkdir(argv[2], stat_src.st_mode) == -1)
				{
					perror("mkdir");
					exit("EXIT_FAILURE");
				}
				cp_dir(argv[1], argv[2]);
			}
		}
		else if (S_ISREG(stat_dest.st_mode))
		{
			fprintf(stderr, "can't copy a directory to file.\n");
			exit(EXIT_FAILURE);
		}
		else 
		{
			char* ptr = (char*)malloc(strlen(argv[1]) + 1 + strlen(argv[2]) + 1);
			sprintf(ptr, "%s/%s\0", argv[2], argv[1]);
			if (mkdir(ptr, stat_src.st_mode) == -1)
			{	
				perror("mkdir");	
				exit(EXIT_FAILURE);
			}
			cp_dir(argv[1], ptr);	
			free(ptr);
		}
	}
}

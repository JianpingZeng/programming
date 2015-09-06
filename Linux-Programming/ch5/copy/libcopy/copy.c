/* To copy large file */
#define _LARGEFILE_SOURCE
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "copy.h"
#define BUFF_LEN 128


/*
* copy file from source file to destination.
@param	src		source file
@param	dest	destination file
@param	mode	mode.
*/
int cp_file(char* src, char* dest, __mode_t mode)
{
  int fd_src;
  if ((fd_src = open(src, O_RDONLY)) < 0)
    {
      printf("Open source file failured.");
      return 0;
    }
  int fd_dest;
  if ((fd_dest = open(dest, O_WRONLY|O_CREAT|O_EXCL, mode)) < 0)
    {
      printf("Open target file failured.");
      return 0;
    }
  int num = 0;
  char buff[BUFF_LEN];
  while((num = read(fd_src, buff, BUFF_LEN)) > 0)
    {
      write(fd_dest, buff, BUFF_LEN);
    }
  close(fd_src);
  close(fd_dest);
  return 0;
}

int cp_dir(const char* src, const char* dest)
{
	DIR* dir = NULL;
	// open source directory
	if ((dir = opendir(src)) == NULL)
	{
		perror("mkdir");	
		exit(EXIT_FAILURE);
	}
	// reads all entry in directory
	struct dirent* dirp;
	while ((dirp = readdir(dir)) != NULL)
	{
		// ignores parent folder and current.
		if (strcmp(dirp->d_name, "..") == 0 || strcmp(dirp->d_name, ".") == 0)
			continue;
			
		char* name_src = (char*)malloc(strlen(src) + 1 + strlen(dirp->d_name) + 1);
		sprintf(name_src, "%s/%s\0", src, dirp->d_name);
		
		char* name_dest = (char*)malloc(strlen(dest) + 1 + strlen(dirp->d_name) + 1);
		sprintf(name_dest, "%s/%s\0", dest, dirp->d_name);
		
		struct stat stat_src;
		if (stat(name_src, &stat_src) == -1)
		{
			fprintf(stderr, "%s(%d): stat error (%s)!\n", __FILE__, __LINE__, strerror(errno));
			exit(EXIT_FAILURE);
		}
		// regular file, copy
		if (S_ISREG(stat_src.st_mode))
		{
			cp_file(name_src, name_dest, stat_src.st_mode);
			free(name_src);
			free(name_dest);
		}
		// directory
		else if(S_ISDIR(stat_src.st_mode))
		{
			if (mkdir(name_dest, stat_src.st_mode) == -1)
			{
				perror("mkdir");
				exit(EXIT_FAILURE);
			}
			cp_dir(name_src, name_dest);
			free(name_src);
			free(name_dest);
		}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

/*
* Open a directory and reads all file from it.
*/

int main(int argc, char* argv[])
{
	if (argc <=1 ) return 0;
	struct dirent* dirp = NULL;
	DIR* dir = opendir(argv[1]);
	if (dir != NULL)
	{
		printf("All file or directory at current directory[\"%s\"] is listed as following:\n", argv[1]);
		while ((dirp = readdir(dir))!= NULL)
		{
			printf("inode=%lu\t", dirp->d_ino);
			printf("reclen=%d\t", dirp->d_reclen);
			printf("name=%s\t", dirp->d_name);
			printf("type=%c\n", dirp->d_type);
		}
		closedir(dir);		
	}
	return 0;
}

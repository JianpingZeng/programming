#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "node.h"
#include "display.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("usage: %s file_name", argv[0]);
		exit(EXIT_FAILURE);
	}
	// print status of specified file step by step.
	for (int idx= 1; idx < argc; idx++)
	{
		struct stat stat_info;
		Node* fnode = NULL;
		if (stat(argv[idx], &stat_info) < 0)
		{
			perror("stat");
			exit(EXIT_FAILURE);
		}
		// display basic information of regular file.
		if (S_ISREG(stat_info.st_mode))
		{
			Node* temp = NULL;
			if ((temp = (Node*)malloc(sizeof(Node))) == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			temp->next = NULL;
			memset(temp->name, '\0', NAME_SIZE);
			memcpy(temp->name, argv[idx], strlen(argv[idx]));
 			fnode = insert(fnode, temp);
 			display(fnode);
		}
		// display basic information of directory.
		else if(S_ISDIR(stat_info.st_mode))
		{
			// used to save old work directory
			char oldDir[NAME_SIZE];
			getcwd(oldDir, NAME_SIZE);
			
			
			DIR *dir = opendir(argv[idx]);
			if (dir == NULL)
			{
				perror("opendir");
				exit(EXIT_FAILURE);
			}
			
			struct dirent* entry;
			while ((entry = readdir(dir)) != NULL)
			{
				Node* temp = NULL;
				if ((temp = (Node*)malloc(sizeof(Node))) == NULL)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}
				temp->next = NULL;
				memset(temp->name, '\0', NAME_SIZE);
				memcpy(temp->name, entry->d_name, strlen(entry->d_name));
	 			fnode = insert(fnode, temp);
			}
			// change current directory
			chdir(argv[idx]);
			closedir(dir);
 			display(fnode);
 			
 			// return to previous directory
 			chdir(oldDir);
		}
		free_list(fnode);
	}
	return 0;
}

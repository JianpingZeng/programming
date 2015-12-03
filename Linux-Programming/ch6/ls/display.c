
#include "display.h"


static char type[] = {'p', 'c', 'd', 'b', '-', 'l', 's'};

static char* perm[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

static void print_type_permission(mode_t mode)
{
	int index = ((mode>>12)&0xF)>>1;
	printf("%c", type[index]);
	
	printf("%s", perm[mode>>6 &0x7]);
	printf("%s", perm[mode>>3 &0x7]);
	printf("%s", perm[mode &0x7]);	
}

static void print_user_group(uid_t uid, gid_t gid)
{
	struct passwd* user = getpwuid(uid);
	if (user == NULL) 
	{
		perror("getpwuid");
		exit(EXIT_FAILURE);
	}
	printf("  %s", user->pw_name);
	
	struct group* grp = getgrgid(gid);
	if (grp == NULL)
	{
		perror("getpwuid");
		exit(EXIT_FAILURE);
	}
	printf("  %s", grp->gr_name);
}

static void print_mtime(time_t mytime)
{
	char buff[256];
	memset(buff, '\0', sizeof(buff));
	ctime_r(&mytime, buff);
	buff[strlen(buff) - 1] = '\0';
	printf("  %s", buff);
}

void display(Node* head)
{
	struct stat mystat;
	Node* temp = head;
	while(temp != NULL)
	{
		if (stat(temp->name, &mystat) < 0)
		{
			// if current file is not exist,continue.
			perror("stat");
			continue;
		}
		print_type_permission(mystat.st_mode);
		printf("  %4d", mystat.st_nlink);
		print_user_group(mystat.st_uid, mystat.st_gid);
		printf("  %8ld", mystat.st_size);
		print_mtime(mystat.st_mtime);
		printf("  %s", temp->name);
		putchar('\n');
		temp = temp->next;
	}
}

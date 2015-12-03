#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	struct passwd *ptr;
	unsigned int uid;
	if (argc > 1)
	{
		uid = atoi(argv[1]);
		ptr = getpwuid(uid);
		if (ptr == NULL)		
		{	
			fprintf(stderr, "user with id [%s] is absent.\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		printf("user name:%s\n", ptr->pw_name);
		printf("user password:%s\n", ptr->pw_passwd);
		printf("user ID:%u\n", ptr->pw_uid);
		printf("user group ID:%u\n", ptr->pw_gid);
		printf("home directory:%s\n", ptr->pw_dir);
		printf("default shell:%s\n", ptr->pw_shell);		
	}
	else 
	{
		fprintf(stderr, "Usage: %s user_ID\n", argv[0]);
	}
	return 0;
}

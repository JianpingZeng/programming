#include <stdio.h>
#include <time.h>
#include <string.h>

int main()
{
  // A struct storaged time
  time_t timep;
  time(&timep);
  // display time with string format
  printf("Current time is: %s\n", ctime(&timep));
  time_t timep1, timep2;
  time(&timep1);
  time(&timep2);
  // display time with GMT format
  printf("UCT is : %s\n", asctime(gmtime(&timep1)));
  // display time with local time format
  printf("Local time is : %s\n", asctime(localtime(&timep2)));
  
  char buff[128];
  memset(buff, '\0', sizeof(buff)/sizeof(char));
  printf("Globle time is: ");
  strftime(buff, 128, "%Z", gmtime(&timep1));
  printf("Time zone is: %s\n", buff);
  
  printf("Local time is: ");
  strftime(buff, 128, "%Z", localtime(&timep2));
  printf("Time zone is: %s\n", buff);
  return 0;
}

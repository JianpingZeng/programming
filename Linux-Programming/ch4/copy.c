#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    printf("Usage is like this: cp source_file dest_file");
    return 0;
  }
  
  FILE * fp_src;
  if ((fp_src = fopen(argv[1], "r")) == NULL)
    {
      printf("open source file failured.");
      return 0;
    }
  FILE * fp_dest;
  if ((fp_dest = fopen(argv[2], "w")) == NULL)
  {
      printf("open destination file failured.");
      return 0;
  }

  char buff[128];
  while (feof(fp_src) != 1)
    {
      int num = fread(buff, sizeof(char), sizeof(buff), fp_src);
      fwrite(buff, sizeof(char), sizeof(buff), fp_dest );
    }
  fclose(fp_src);
  fclose(fp_dest);
  return 0;

}

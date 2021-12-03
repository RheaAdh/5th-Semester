#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
 
void printdir(char *dir, int depth)
{
  DIR *d;
  struct dirent *entry;
  struct stat statbuf;
 
  if((d = opendir(dir)) == NULL)
  {
    fprintf(stderr,"Cannot open directory: %s\n",dir);
    return;
  }

  chdir(dir);
 
  while((entry = readdir(d)) != NULL)
  {
    lstat(entry->d_name,&statbuf);
 
    if(S_ISDIR(statbuf.st_mode))
    {
      if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
      {
        continue;
      }
 
      printf("%*s%s/\n",depth,"",entry->d_name);
 
      printdir(entry->d_name, depth+4);
    }
    else { 
      printf("%*s%s\n",depth,"",entry->d_name);
    }
  }

  chdir("..");
  closedir(d);
}
 
int main()
{
  printf("Scan of current directory:\n");
  printdir(".",0);
  printf("Completed.\n");
  exit(0);
}
#include<stdio.h>
#include<dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
int main()
{
char dirname[10];
char cwd[PATH_MAX];
DIR*p;
struct dirent *d;

if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }


printf("Enter directory name\n");
scanf("%s",dirname);
p=opendir(dirname);
if(p==NULL)
  {
  perror("Cannot find directory");
  exit(-1);
  }
while(d=readdir(p))
  printf("%s\t\n",d->d_name);

  return 0;
}
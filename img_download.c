
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<dirent.h>
#include <ctype.h>


int cmd_imgDownloader(char **args)
{
// char link[]= args;
 char command1[]="ffmpeg -r 1/3 -i Naruto.jpeg -vcodec copy out.mp4";
 char command[] = "wget -O Naruto.png ";
 
 strcat(command, args[1]);
 system(command); 

 
    
     return 0;
     
}

int main(int argc, char **argv)
{
  
  cmd_imgDownloader(argv);

  return 0;
}

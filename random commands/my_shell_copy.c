#include <sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

char *builtin_str[] = {
  "dc",
  "help",
  "exit",
  "cw",
  "ip", 
  "aud"
};




int lsh_dc(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"dc\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_IP(char **args)
{
  struct addrinfo* res;
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
 
  // if (argc != 2) {
  //   perror("Usage: hostnamelookup <hostname>\n");
  //   exit(1);
  // }

  hostname = args[1];
 
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
 
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);

  printf("Address for %s is %s\n", hostname, hostaddr);
  exit(0);
}
int lsh_aud(char **args)
{
    
}


int lsh_cw(char **args)
{
           int character_count = 0;
           int space_count = 0;
           int word_count = 0;
           int line_count = 0;
           char ch;

           FILE *fp;

         
           fp = fopen(args[1],"r");

           while((ch=fgetc(fp))!=EOF)
           {
                       character_count++;
                       if(ch == ' ')
                       {
                             space_count++;
                             word_count++;
                       }
                       if(ch == '\n')
                       {
line_count++;
word_count++;
                       }
     
           }
           printf("character_count = %d\n",character_count);
           printf("space_count = %d\n",space_count);
           printf("word_count = %d\n",word_count);
           printf("line_count = %d\n",line_count);
           int file_pointer; 
           char *buff[BUFFER_SIZE];
           int op;

           file_pointer = open(args[1], O_RDONLY);

           while (op=read(file_pointer, buff, BUFFER_SIZE)){
        write(1, buff, op);
      }
   
      close(file_pointer);

           return 1;
}
int lsh_help(char **args)
{
  int i;
  printf("My Custom Shell\n");
  printf("----------------------------------------------------\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are my custom commands:\n");

  for (i = 0; i < 6*sizeof(char); i++) {
    
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}


int lsh_exit(char **args)
{
  return 0;
}


int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    
    perror("lsh");
  } else {
    
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}


int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    
    return 1;
  }

  for (i = 0; i < 6*sizeof(char); i++) {
    if (strcmp(args[0], "help") == 0) {
      return (lsh_help(args));
    }
    else if (strcmp(args[0], "dc") == 0) {
      
      return (lsh_dc(args));
    }
    else if (strcmp(args[0], "exit") == 0) {
      
      return 0;
    }
    else if (strcmp(args[0], "cw") == 0) {
      
      return (lsh_cw(args));
    }
    else if (strcmp(args[0], "ip") == 0) {
      
      return (lsh_IP(args));
    }
    else if (strcmp(args[0], "aud") == 0) {
      
      return (execvp(args[0], args));
    }
  }

  return lsh_launch(args);
}

#define LSH_RL_BUFSIZE 1024

char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    
    c = getchar();

    
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

   
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}


void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("--> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}


int main(int argc, char **argv)
{
  
  lsh_loop();

  

  return EXIT_SUCCESS;
} 

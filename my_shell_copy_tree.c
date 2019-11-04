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
#include <dirent.h>

#define BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 2

char *builtin_str[] = {
  "dc",
  "help",
  "exit",
  "cw",
  "ip",
  "repl",
  "hex",
  "tree"
};


struct t_node
{
	char* name;
	int  ptd;		
	struct t_node *next_dfile;	
	struct t_node *next_file;
};

static struct t_node* create_tree(char *);
void print_tree(struct t_node *);
static struct t_node* create_tnode(char* );
int count;


static struct t_node* create_tree(char *root_name)
{
	DIR *dir=opendir(root_name);
	printf("\nrootname : %s",root_name);
	struct dirent *dr={NULL};
	struct t_node *ptr_tstart=NULL,*temp=NULL,*temp1=NULL;
	char *name=(char *)calloc(2000,sizeof(char));


	if(dir==NULL)
	{
		printf("\nFailed to open ..!!");
		printf(" : %s",root_name);
		return NULL;
	}

	while((dr=readdir(dir))!= NULL)
	{
			if(strcmp((dr->d_name),".")!=0 && strcmp((dr->d_name),"..")!=0) 
				temp=create_tnode(dr->d_name);
			else
			{
				temp=NULL;
				continue;
			}
			
			if(temp1!=NULL)
			{
				temp1->next_file=temp;
			
			}
			else
			{
				(ptr_tstart)=temp;
			}

			if((dr->d_type)==DT_DIR ) 
			{
				temp->ptd=TRUE;
				strcpy(name,root_name);
				(temp->next_dfile)=create_tree((strcat((strcat(name,"/")),dr->d_name)));
				strcpy(name,root_name);
			}
			else
			{
				(temp)->ptd=FALSE;
				(temp)->next_dfile=NULL;		
			}

		temp1=temp;
	}
return (ptr_tstart);
}

static struct t_node* create_tnode(char* n)
{
	struct t_node *temp=(struct t_node * )malloc(sizeof(struct t_node ));
	temp->name=n;
	temp->next_dfile=NULL;
	temp->next_file=NULL;
return temp;
}

void print_tree(struct t_node *start)
{
	char *s="|-----",*s1="|     ";
	struct t_node *temp=start;
	int i;

		if(start==NULL)
			return;

		printf("\n");
		for(i=0;i<(count-1);i++)
			printf("%s",s1);
		if(count>0)
			printf("%s",s);

		printf("%s",temp->name);
		
		if(temp->ptd==TRUE)
		{	
			count++;
			print_tree(temp->next_dfile);
			count--;
		}
		print_tree(temp->next_file);	

} 



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

int lsh_hex(char **args)
{
    unsigned char str[100],strH[200];
    int i,j;
     
    printf("Enter string: ");
    scanf("%[^\n]s",str);
    //str=args[1];
     
    //printf("\nString is: %s\n",str);
     
    /*set strH with nulls*/
    memset(strH,0,sizeof(strH));
     
    /*converting str character into Hex and adding into strH*/
    for(i=0,j=0;i<strlen(str);i++,j+=2)
    { 
        sprintf((char*)strH+j,"%02X",str[i]);
    }
    strH[j]='\0'; /*adding NULL in the end*/
     
    printf("Hexadecimal converted string is: \n");
    printf("%s\n",strH);
     
     
    return 1;
}

#define MAX 256
int lsh_repl(char **args)
{
    FILE *fptr1, *fptr2;
        int lno, linectr = 0;
        char str[MAX],fname[MAX];        
        char newln[MAX], temp[] = "temp.txt";

printf("\n\n Replace a specific line in a text file with a new text :\n");
printf("-------------------------------------------------------------\n");
printf(" Input the file name to be opened : ");
        fgets(fname, MAX, stdin);
        fname[strlen(fname) - 1] = '\0';
        fptr1 = fopen(fname, "r");
        if (!fptr1)
        {
                printf("Unable to open the input file!!\n");
                return 0;
        }
        fptr2 = fopen(temp, "w");
        if (!fptr2)
        {
                printf("Unable to open a temporary file to write!!\n");
                fclose(fptr1);
                return 0;
        }
        /* get the new line from the user */
        printf(" Input the content of the new line : ");
        fgets(newln, MAX, stdin);
        /* get the line number to delete the specific line */
        printf(" Input the line no you want to replace : ");
        scanf("%d", &lno);
        lno++;
         // copy all contents to the temporary file other except specific line
        while (!feof(fptr1))
        {
            strcpy(str, "\0");
            fgets(str, MAX, fptr1);
            if (!feof(fptr1))
            {
                linectr++;
                if (linectr != lno)
                    {
                        fprintf(fptr2, "%s", str);
                    }
                    else
                    {
                        fprintf(fptr2, "%s", newln);
                    }
                }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove(fname);
        rename(temp, fname);
        printf(" Replacement did successfully..!! \n");
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

  for (i = 0; i < 8*sizeof(char); i++) {
    
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


int lsh_execute(char **args, int argc )
{
  int i;

  if (args[0] == NULL) {
    
    return 1;
  }

  for (i = 0; i < 8*sizeof(char); i++) {
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
    else if (strcmp(args[0], "repl") == 0) {
      
      return (lsh_repl(args));
    }
    else if (strcmp(args[0], "hex") == 0) {
      
      return (lsh_hex(args));
    }
    else if (strcmp(args[0], "tree") == 0) {
      struct t_node *tstart=create_tnode(".");
      if(args>2)
      {
        printf("\n USAGE : ./a.out [PATH]");
        exit(0);
      }
      
      tstart->ptd=TRUE;
      (tstart->next_dfile)=create_tree(((argc==2)? args[1]:getcwd(0,0)));
      print_tree(tstart);
      // return (lsh_hex(args));
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


void lsh_loop(int argc)
{
  char *line;
  char **args;
  int status;

  do {
    printf("--> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args, argc);

    free(line);
    free(args);
  } while (status);
}


int main(int argc, char **argv)
{
  
  lsh_loop(argc);

  

  return EXIT_SUCCESS;
} 

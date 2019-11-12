
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


#define MAX_WORDS   10000
int cmd_wordCount()
{
    
    FILE *fptr;
    char path[100];
    int i, len, index, isUnique;

    // List of distinct words
    char words[MAX_WORDS][500];
    char word[500];

    // Count of distinct words
    int  count[MAX_WORDS];


    /* Input file path */
    printf("Enter file path: ");
    scanf("%s", path);


    /* Try to open file */
    fptr = fopen(path, "r");

    /* Exit if file not opened successfully */
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read previleges.\n");

        exit(EXIT_FAILURE);
    }

    // Initialize words count to 0
    for (i=0; i<MAX_WORDS; i++)
        count[i] = 0;




    index = 0;
    
    while (fscanf(fptr, "%s", word) != EOF)
    {
        // Convert word to lowercase
        //strlwr(word);

        // Remove last punctuation character
        len = strlen(word);
        if (ispunct(word[len - 1]))
            word[len - 1] = '\0';


        // Check if word exits in list of all distinct words
        isUnique = 1;
        for (i=0; i<index && isUnique; i++)
        {
            if (strcmp(words[i], word) == 0)
                isUnique = 0;
        }

        // If word is unique then add it to distinct words list
        // and increment index. Otherwise increment occurrence 
        // count of current word.
        if (isUnique) 
        {
            strcpy(words[index], word);
            count[index]++;

            index++;
        }
        else
        {
            count[i - 1]++;
        }
    }

    // Close file
    fclose(fptr);
    int j=0,a=0;


    for (i = 0; i < index; ++i) 
        {
 
            for (j = i + 1; j <index; ++j)
            {
 
                if (count[i] < count[j]) 
                {
 
                    a =  count[i];
                    count[i] = count[j];
                    count[j] = a;

                    a = word [i];
                    word[i] = word[j];
                    word[j] = a;
 
                }
 
            }
 
        }
 


    /*
     * Print occurrences of all words in file. 
     */
    printf("\nOccurrences of all distinct words in file: \n");
    for (i=0; i<10; i++)
    {
        /*
         * %-15s prints string in 15 character width.
         * - is used to print string left align inside
         * 15 character width space.
         */
        printf("%-15s => %d\n", words[i], count[i]);
    }    

    return 1;
    
}    
int main(int argc, char **argv)
{
  
 
  cmd_wordCount();

  return 0;
}
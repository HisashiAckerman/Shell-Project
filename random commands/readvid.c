 
#include <stdlib.h>
#include <stdio.h>

#define BUFFERSIZE 0x8000 // 32k buffer (adapt at will)

int main()
{
  FILE *fp1 = fopen("Brave Shine.mp3", "rb");

  if (fp1 == NULL)
  {
    // display error message to be written
    exit(1);
  }
  FILE *fp2 = fopen("FOOTBALL_352x288_30_copy_01.mp3", "wb");
  if (fp2 == NULL)
  {
    // display error message to be written
    exit(1);
  }    

  for (;;)   // loop for ever
  {
    char buffer[BUFFERSIZE];
    size_t bytesread = fread(buffer, 1, sizeof buffer, fp1);

    // bytesread contains the number of bytes actually read
    if (bytesread == 0)
    {
      // no bytes read => end of file
      break;
    }

    fwrite(buffer, bytesread, 1, fp2);
  }

  fclose(fp1);
  fclose(fp2);
}

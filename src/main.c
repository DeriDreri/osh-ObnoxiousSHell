#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1 
#define FALSE 0

const uint32_t size_of_buffer_chunk = 1024;

char * oshReadLine(void) 
{
  char * line        = NULL;
  size_t buffer_size = 0; 

  if (getline(&line, &buffer_size, stdin) == -1){
    if (feof(stdin)) 
    {
      exit(EXIT_SUCCESS);
    } 
    else  
    {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }

  return line;
}

void oshLoop(void)
{
  char * line; 
  while(1) 
  { 
    printf("osh > ");
    line = oshReadLine();
    printf("%s", line);
    free(line);
  }
}


int main(int argc, char *argv[])
{
  // Init 
  
  oshLoop();

  // Clean
  
  return EXIT_SUCCESS;
}

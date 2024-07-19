#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1 
#define FALSE 0

#ifdef DEBUG 
  #define DEBUG_PRINT(x) fprintf(stderr, "DEBUG: "); fprintf(stderr,x);
  #define DEBUG_PRINT2(x,y) fprintf(stderr, "DEBUG: "); fprintf(stderr,x,y);
#else
  #define DEBUG_PRINT(x) {}
  #define DEBUG_PRINT2(x,y) {}
#endif

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

  DEBUG_PRINT2("Line read from the STDIN:\n\t%s", line)
  return line;
}

void oshLoop(void)
{
  char * line; 
  DEBUG_PRINT("Starting the main shell loop\n")
  while(1) 
  { 
    printf("osh > ");
    line = oshReadLine();
    free(line);
  }
}


int main(int argc, char *argv[])
{
  // Init 
  DEBUG_PRINT("Initialised the shell\n")
    
  oshLoop();

  // Clean
  DEBUG_PRINT("Cleaning and closing the shell\n")
  
  return EXIT_SUCCESS;
}

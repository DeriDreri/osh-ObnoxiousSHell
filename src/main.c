#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1 
#define FALSE 0

#ifdef DEBUG 
  #define DEBUG_PRINT(x) fprintf(stderr, "DEBUG> "); fprintf(stderr,x)
  #define DEBUG_PRINT2(x,y) fprintf(stderr, "DEBUG> "); fprintf(stderr,x,y)
#else
  #define DEBUG_PRINT(x) {}
  #define DEBUG_PRINT2(x,y) {}
#endif

const uint32_t  tokenizer_buffer_chunk_size  = 64;
const char *    tokenizer_delimeters         = " \t\r\n\a";
const uint32_t  size_of_buffer_chunk         = 1024;

char ** oshTokenizeLine(char * line)
{
  uint32_t  buffer_size  = tokenizer_buffer_chunk_size;
  uint32_t  position     = 0;
  char **   tokens       = malloc(buffer_size * sizeof(char*));
  char *    token;

  if (!tokens) 
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  
  token = strtok(line, tokenizer_delimeters);
  while(token != NULL)
  {
    tokens[position] = token;
    position++;

    if (position >= buffer_size) 
    {
      buffer_size += tokenizer_buffer_chunk_size;
      tokens = realloc(tokens, buffer_size * sizeof(char*));
      if (!tokens) 
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, tokenizer_delimeters);
  }
  DEBUG_PRINT("Passed tokens\n");
  DEBUG_PRINT2("\tFirst token: %s\n", tokens[0]);
  DEBUG_PRINT2("\tLast token: %s\n", tokens[position-1]);

  tokens[position] = NULL;
  return tokens;
}

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

  DEBUG_PRINT("Line read from the STDIN:\n");
  DEBUG_PRINT2("\t%s", line);
  return line;
}

void oshLoop(void)
{
  char *  line; 
  char ** tokens;
  DEBUG_PRINT("Starting the main shell loop\n");
  while(1) 
  { 
    printf("osh > ");
    line = oshReadLine();
    tokens = oshTokenizeLine(line);

    if (strcmp(tokens[0],"exit") == 0)
    {
      free(tokens);
      free(line);
      break;
    }

    free(tokens);
    free(line);
  }
}


int main(int argc, char *argv[])
{
  // Init 
  DEBUG_PRINT("Initialised the shell\n");
    
  oshLoop();

  // Clean
  DEBUG_PRINT("Cleaning and closing the shell\n");
  
  return EXIT_SUCCESS;
}

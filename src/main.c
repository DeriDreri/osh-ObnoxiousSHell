/*
 *   Copyright (c) 2024 Dominik Cybulski
 *   All rights reserved.
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <osh/global.h>
#include <osh/builtin.h>

const uint32_t  tokenizer_buffer_chunk_size  = 64;
const char *    tokenizer_delimeters         = " \t\r\n\a";
const uint32_t  size_of_buffer_chunk         = 1024;

int osh_launch(char ** args)
{
  pid_t pid;
  pid_t wpid;
  int   status;

  pid = fork();
  if (0 == pid)
  {
    if (-1 == (execvp(args[0], args)))
    {
      perror("osh");
    }
  exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    perror("osh");
  }
  else
  {
    do
    {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}

int osh_execute(char ** args)
{
  if (NULL == args[0])
  {
    return 1;
  }

  for (int i = 0; i < oshCountBuiltins(); i++)
  {
    if (strcmp(args[0], builtint_names[i]) == 0)
    {
      return (*builtint_functions[i])(args);
    }
  }

  return osh_launch(args);
}

char ** oshTokenizeLine(char * line)
{
  uint32_t  buffer_size  = tokenizer_buffer_chunk_size;
  uint32_t  position     = 0;
  char **   tokens       = malloc(buffer_size * sizeof(char*));
  char *    token;

  if (!tokens)
  {
    fprintf(stderr, "osh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, tokenizer_delimeters);
  while (token != NULL)
  {
    tokens[position] = token;
    position++;

    if (position >= buffer_size)
    {
      buffer_size += tokenizer_buffer_chunk_size;
      tokens = realloc(tokens, buffer_size * sizeof(char*));
      if (!tokens)
      {
        fprintf(stderr, "osh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, tokenizer_delimeters);
  }

  tokens[position] = NULL;

  DEBUG_PRINT("Passed tokens\n");
  DEBUG_PRINT2("\tFirst token: %s\n", tokens[0] != NULL ? tokens[0] : "NULL");
  DEBUG_PRINT2("\tLast token: %s\n", tokens[0] != NULL ?
                                     tokens[position-1] :
                                     "NULL");

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
  int     status = 1;

  DEBUG_PRINT("Starting the main shell loop\n");
  while (status)
  {
    printf("osh > ");
    line = oshReadLine();
    tokens = oshTokenizeLine(line);

    if (tokens[0] == NULL)
    {
      free(tokens);
      free(line);
      continue;
    }
    status = osh_execute(tokens);
    free(tokens);
    free(line);
  }
}


int main(int argc, char *argv[])
{
  // Init
  #ifndef DEBUG
    // Clean screen
    printf("\033[2J");
    // Put cursor on top
    printf("\033[0;0H");
    // Change color to bold red
    printf("\033[1;31m");
  #endif /* ifndef DEBUG */

  DEBUG_PRINT("Initialised the shell\n");

  oshLoop();

  // Clean
  DEBUG_PRINT("Cleaning and closing the shell\n");
  // Reset the terminal option
  printf("\033[0m");
  return EXIT_SUCCESS;
}

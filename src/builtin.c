/*
 *   Copyright (c) 2024 Dominik Cybulski
 *   All rights reserved.
 */
#include <stdio.h>
#include <unistd.h>

#include <osh/builtin.h>
#include <osh/global.h>

char const * const builtint_names[] =
{
    "cd",
    "help",
    "exit"
};

int (* const builtint_functions[])(char **) =
{
  &osh_cd,
  &osh_help,
  &osh_exit
};

int oshCountBuiltins(void)
{
  return sizeof(builtint_names) / sizeof(char *);
}

int osh_cd(char **args)
{
  if (NULL == args[1])
  {
    DEBUG_PRINT("cd: no arguments");
    return 2;
  }
  if (0 != chdir(args[1]))
  {
    perror("osh");
  }
  return 1;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int osh_help(char ** args)
{
  printf("Obnoxious SHell\n");
  printf("Type program name and arguments and hit ENTER\n");
  printf("The following are built in:\n");
  for (int i = 0; i < oshCountBuiltins(); i++)
  {
    printf("\t%s\n", builtint_names[i]);
  }
  return 1;
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int osh_exit(char ** args)
{
  return 0;
}
#pragma GCC diagnostic pop

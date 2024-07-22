#pragma once

int osh_cd(char ** args);
int osh_help(char ** args);
int osh_exit(char ** args);

extern char const * const builtint_names[];

extern int (* const builtint_functions[]) (char **);

int oshCountBuiltins(void);

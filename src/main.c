#include <stdlib.h>
#include <stdio.h>

void osh_loop(void)
{
  while(1) 
  { 
    char c;
    printf("> ");
    c = getchar();
    printf("\n");
  }
}


int main(int argc, char *argv[])
{
  // Init 
  
  osh_loop();

  // Clean
  
  return EXIT_SUCCESS;
}

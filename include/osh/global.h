#pragma once

#define TRUE 1
#define FALSE 0

#ifdef DEBUG
  #define DEBUG_PRINT(x) fprintf(stderr, "DEBUG> "); fprintf(stderr, x)
  #define DEBUG_PRINT2(x, y) fprintf(stderr, "DEBUG> "); fprintf(stderr, x, y)
#else
  #define DEBUG_PRINT(x) {}
  #define DEBUG_PRINT2(x, y) {}
#endif

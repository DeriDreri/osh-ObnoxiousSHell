#pragma once 

#include <stdint.h>

typedef struct RingBuffer 
{
  char **     buffer;
  uint32_t    buffer_size;
  uint32_t    position;
} RingBuffer;

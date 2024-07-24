#pragma once

#include <stdint.h>

#define STARTING_HISTORY_SIZE 50

typedef struct RingBuffer
{
  char **     buffer;
  uint32_t    buffer_size;
  uint32_t    position;
} RingBuffer;

RingBuffer *  initRingBuffer(uint32_t size);
void          destroyRingBuffer(RingBuffer * ringBuffer);
void          writeRingBuffer(RingBuffer * ringBuffer, char * value);
void          printRingBuffer(RingBuffer * ringBuffer);

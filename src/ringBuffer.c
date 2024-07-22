/*
 *   Copyright (c) 2024 Dominik Cybulski
 *   All rights reserved.
 */ 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <ringBuffer.h>

RingBuffer * initRingBuffer(uint32_t size)
{
  RingBuffer * ringBuffer = malloc(sizeof(RingBuffer));
  ringBuffer->buffer = calloc(size, sizeof(char *));
  ringBuffer->buffer_size = size;
  ringBuffer->position = 0;
  return ringBuffer;
}

void destroyRingBuffer(RingBuffer * ringBuffer)
{
  uint32_t current_position = ringBuffer->position;
  current_position = (current_position - 1 + ringBuffer->buffer_size) % ringBuffer->buffer_size;

  while(ringBuffer->buffer[current_position] != NULL) 
  {
    free(ringBuffer->buffer[current_position]);
    ringBuffer->buffer[current_position] = NULL;
    current_position = (current_position - 1 + ringBuffer->buffer_size) % ringBuffer->buffer_size;
  }
  free(ringBuffer->buffer);
  free(ringBuffer);
}

void writeRingBuffer(RingBuffer * ringBuffer, char * value)
{
  if (ringBuffer -> buffer[ringBuffer->position] != NULL)
  {
    free(ringBuffer->buffer[ringBuffer->position]);
  }
  ringBuffer->buffer[ringBuffer->position] = malloc((strlen(value) + 1) * sizeof(char));
  strcpy(ringBuffer->buffer[ringBuffer->position], value);
  ringBuffer->position = (ringBuffer->position + 1) % ringBuffer->buffer_size;
}

void printRingBuffer(RingBuffer * ringBuffer)
{
  uint32_t current_position = ringBuffer->position;
  uint32_t prints_counter = 0;
  do
  {
    if (ringBuffer->buffer[current_position] != NULL) 
    {
      printf("%s\n", ringBuffer->buffer[current_position]);
    }
    current_position = (current_position + 1) % ringBuffer->buffer_size;
    prints_counter++;
  } while(prints_counter < ringBuffer->buffer_size);
  printf("\n");
}

#pragma once

#include <stdint.h>

#define STARTING_HISTORY_SIZE 50

typedef struct HistoryBuffer
{
  char **     buffer;
  uint32_t *  counts;
  uint32_t    buffer_size;
  uint32_t    position;
} HistoryBuffer;

HistoryBuffer *  HistoryBuffer_init(uint32_t size);
void          HistoryBuffer_destroy(HistoryBuffer * historyBuffer);
void          HistoryBuffer_write(HistoryBuffer * historyBuffer, char * value);
void          HistoryBuffer_print(HistoryBuffer * historyBuffer);

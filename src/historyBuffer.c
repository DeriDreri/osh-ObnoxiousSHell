/*
 *   Copyright (c) 2024 Dominik Cybulski
 *   All rights reserved.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <historyBuffer.h>

HistoryBuffer * HistoryBuffer_init(uint32_t size)
{
  HistoryBuffer * historyBuffer = malloc(sizeof(HistoryBuffer));
  historyBuffer->buffer = calloc(size, sizeof(char *));
  historyBuffer->counts = calloc(size, sizeof(int));
  historyBuffer->buffer_size = size;
  historyBuffer->position = 0;
  return historyBuffer;
}

void HistoryBuffer_destroy(HistoryBuffer * historyBuffer)
{
  uint32_t current_position = historyBuffer->position;
  current_position = (current_position - 1 + historyBuffer->buffer_size)
                      % historyBuffer->buffer_size;

  while (historyBuffer->buffer[current_position] != NULL)
  {
    free(historyBuffer->buffer[current_position]);
    historyBuffer->buffer[current_position] = NULL;
    current_position = (current_position - 1 + historyBuffer->buffer_size)
                        % historyBuffer->buffer_size;
  }
  free(historyBuffer->buffer);
  free(historyBuffer->counts);
  free(historyBuffer);
}

void HistoryBuffer_write(HistoryBuffer * historyBuffer, char * value)
{
  uint32_t current_position  = historyBuffer->position;
  uint32_t previous_position = (current_position - 1
                                + historyBuffer->buffer_size)
                               % historyBuffer->buffer_size;

  if (historyBuffer -> buffer[current_position] != NULL)
  {
    free(historyBuffer->buffer[current_position]);
  }

  uint32_t string_length = strlen(value) + 1;
  historyBuffer->buffer[current_position] = malloc((string_length+ 1)
                                                    * sizeof(char));
  snprintf(historyBuffer->buffer[current_position], string_length, "%s", value);
  historyBuffer->counts[current_position] =
                      historyBuffer->counts[previous_position] + 1;

  historyBuffer->position = (historyBuffer->position + 1)
                          % historyBuffer->buffer_size;
}

void HistoryBuffer_print(HistoryBuffer * historyBuffer)
{
  uint32_t current_position = historyBuffer->position;
  uint32_t prints_counter = 0;
  do
  {
    if (historyBuffer->buffer[current_position] != NULL)
    {
      printf("%d %s\n",
             historyBuffer->counts[current_position],
             historyBuffer->buffer[current_position]);
    }
    current_position = (current_position + 1) % historyBuffer->buffer_size;
    prints_counter++;
  } while (prints_counter < historyBuffer->buffer_size);
}

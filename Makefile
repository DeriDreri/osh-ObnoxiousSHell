TARGET = osh
TARGET_DIR = build
SRC = src/main.c
INCLUDE = include
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

$(TARGET_DIR)/$(TARGET): $(SRC)
	$(CC) -o $(TARGET_DIR)/$(TARGET) $(CFLAGS) -I$(INCLUDE) $(SRC)

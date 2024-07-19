TARGET = osh
TARGET_DIR = build
SRC = src/main.c
INCLUDE = include
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

help:
	@echo '------------------------------------------------------'
	@echo "make buld - build the project"
	@echo "make run - build and run the project"
	@echo "make debug - build and run the project in debug mode"
	@echo "make clean - clean the project"
	@echo '------------------------------------------------------'

debug: CFLAGS += -DDEBUG -g
debug: $(TARGET_DIR)/$(TARGET)
	@./$(TARGET_DIR)/$(TARGET)

build: $(TARGET_DIR)/$(TARGET)

run: $(TARGET_DIR)/$(TARGET)
	@./$(TARGET_DIR)/$(TARGET)

clean:
	@rm $(TARGET_DIR)/*

$(TARGET_DIR)/$(TARGET): $(SRC)
	$(CC) -o $(TARGET_DIR)/$(TARGET) $(DFLAGS) $(CFLAGS) -I$(INCLUDE) $(SRC)

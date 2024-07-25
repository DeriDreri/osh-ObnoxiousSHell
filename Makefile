TARGET = osh
TARGET_DIR = build
BUILD_DIR = obj
SRC = $(shell find src -type f -name "*.c")
OBJ = $(patsubst src/%,$(BUILD_DIR)/%,$(SRC:.c=.o))
INCLUDE = include
CC = gcc
CCFLAGS = -Wall -Wextra -pedantic

help:
	@echo '------------------------------------------------------------'
	@echo "make buld - build the project"
	@echo "make run - build and run the project"
	@echo "make debug - build and run the project in debug mode"
	@echo "make clean - remove the executable"
	@echo "make cleaner - remove the executable and the build directory"
	@echo '------------------------------------------------------------'

debug: CCFLAGS += -DDEBUG -g -fsanitize=address
debug: $(TARGET_DIR)/$(TARGET)
	@./$(TARGET_DIR)/$(TARGET)

build: $(TARGET_DIR)/$(TARGET)
	@cpplint $(SRC)

run: $(TARGET_DIR)/$(TARGET)
	@./$(TARGET_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) -c $(CCFLAGS) -I$(INCLUDE) $< -o $@

clean:
	@rm $(TARGET_DIR)/*

cleaner:
	@rm $(TARGET_DIR)/$(TARGET)
	@rm -rf $(BUILD_DIR)

$(TARGET_DIR)/$(TARGET): $(OBJ)
	$(CC) -o $(TARGET_DIR)/$(TARGET) $(CCFLAGS) -I$(INCLUDE) $(SRC)

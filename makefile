CC = gcc
CFLAGS  = -g -Wall -pedantic
BIN_DIR = ./code/bin
SRC_DIR = ./code/src
OBJ_DIR = ./code/obj
INC_DIR = ./code/include
TEST_DIR = ./code/tests

TARGET = $(BIN_DIR)/huffman
# You can use a wildcard to get all .c files in the source directory
# This assumes all your .c files that you wish to compile are in the SRC_DIR
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Replace .c with .o and change the source directory to object directory for object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

# Link the target with all object files
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each source file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

test: $(TARGET)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(TEST_DIR)/test.c -o $(BIN_DIR)/test
	$(BIN_DIR)/test
	

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean

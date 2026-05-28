CC = gcc
CFLAGS = -Wall -O0 -g -Iinclude
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

COMMON_SRC = $(SRC_DIR)/common.c
SORT_SRC = $(SRC_DIR)/sort/sort.c
KNAPSACK_SRC = $(SRC_DIR)/knapsack/brute_force.c \
               $(SRC_DIR)/knapsack/dp.c \
               $(SRC_DIR)/knapsack/greedy.c \
               $(SRC_DIR)/knapsack/backtrack.c
TEST_SRC = $(SRC_DIR)/test/main.c \
           $(SRC_DIR)/test/test_sort.c \
           $(SRC_DIR)/test/test_knapsack.c

COMMON_OBJ = $(OBJ_DIR)/common.o
SORT_OBJ = $(OBJ_DIR)/sort.o
KNAPSACK_OBJ = $(OBJ_DIR)/brute_force.o \
               $(OBJ_DIR)/dp.o \
               $(OBJ_DIR)/greedy.o \
               $(OBJ_DIR)/backtrack.o
TEST_OBJ = $(OBJ_DIR)/main.o \
           $(OBJ_DIR)/test_sort.o \
           $(OBJ_DIR)/test_knapsack.o

ALL_OBJ = $(COMMON_OBJ) $(SORT_OBJ) $(KNAPSACK_OBJ) $(TEST_OBJ)
TARGET = $(BIN_DIR)/algorithm_experiment

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(ALL_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/sort/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/knapsack/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/test/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	rm -f ../results/*.csv
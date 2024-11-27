CC = gcc
CFLAGS = -Wall -Wextra -std=c11
PROFILING_FLAGS = -pg

TARGET = main
SRC_DIR = src
OBJ_DIR = obj

all: $(TARGET)

$(TARGET): $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_DIR)/main.o

profile: CFLAGS += $(PROFILING_FLAGS)
profile: $(OBJ_DIR)/main_profile.o
	$(CC) $(CFLAGS) -o $(TARGET)_profile $(OBJ_DIR)/main_profile.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/main_profile.o: $(SRC_DIR)/main.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main_profile.o

clean:
	rm -f $(TARGET) $(TARGET)_profile $(OBJ_DIR)/*.o gmon.out

CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

# Folders
SRC_FOLDER = src/
TEST_FOLDER = test/
OBJ_FOLDER = obj/
BIN_FOLDER = bin/
INCLUDE_FOLDER = include/

# Source files
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(filter-out $(SRC_FOLDER)OrdIndTeste.cpp, $(SRC)))
TEST_SRC = $(TEST_FOLDER)OrdIndTeste.cpp
TEST_OBJ = $(patsubst $(TEST_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(TEST_SRC))

# Targets
TARGET = main
TEST_TARGET = test

# Create directories if they don't exist
$(OBJ_FOLDER):
	mkdir -p $(OBJ_FOLDER)

$(BIN_FOLDER):
	mkdir -p $(BIN_FOLDER)

# Compile source files
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp | $(OBJ_FOLDER)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

# Compile test files
$(OBJ_FOLDER)%.o: $(TEST_FOLDER)%.cpp | $(OBJ_FOLDER)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

# Link the main program
all: $(OBJ_FOLDER) $(BIN_FOLDER) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

# Link the test program
test: $(OBJ_FOLDER) $(BIN_FOLDER) $(OBJ) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN_FOLDER)$(TEST_TARGET) $(OBJ) $(TEST_OBJ)
	$(BIN_FOLDER)$(TEST_TARGET)

# Clean build artifacts
clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*

.PHONY: all test clean
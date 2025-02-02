# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Diretórios
SRC_DIR = src
TEST_DIR = test
INCLUDE_DIR = include
BIN_DIR = bin
OBJ_DIR = obj

# Arquivos fonte e objetos
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

SRC_OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/src_%.o)
TEST_OBJ_FILES = $(TEST_FILES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/test_%.o)

# Executáveis
EXEC = $(BIN_DIR)/tp3.out
TEST_EXEC = $(BIN_DIR)/tests.out

# Regras principais
all: $(EXEC)

memtest: $(TEST_EXEC)
	@echo "Running all tests with Valgrind:"
	valgrind --leak-check=full $(TEST_EXEC)

timetest: $(TEST_EXEC)
	@echo "Running time test:"
	time $(TEST_EXEC)

testall: $(TEST_EXEC)
	@for input in $(wildcard ./test/inputs/*); do \
		echo "Running test with input $$input:"; \
		./$(TEST_EXEC) $$input; \
	done

run: $(EXEC)
	./$(EXEC) ./test/inputs/input_1.txt

debug: $(EXEC)
	gdb --args $(EXEC) $(ARGS)

# Compilar o executável principal
$(EXEC): $(SRC_OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar executável de todos os testes
$(TEST_EXEC): $(TEST_OBJ_FILES) $(filter-out $(OBJ_DIR)/src_main.o, $(SRC_OBJ_FILES)) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regras para compilar objetos
$(OBJ_DIR)/src_%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Diretórios auxiliares
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Dependências
-include $(SRC_OBJ_FILES:.o=.d)
-include $(TEST_OBJ_FILES:.o=.d)

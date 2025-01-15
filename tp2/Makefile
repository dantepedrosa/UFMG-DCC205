# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = test
BIN_DIR = bin
OBJ_DIR = obj

# Arquivos fonte e objetos
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES = $(TEST_FILES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executável
EXEC = $(BIN_DIR)/tp2.out
TEST_EXEC = $(BIN_DIR)/test.out

# Regra padrão
all: $(EXEC)

# Regra para compilar o executável principal
$(EXEC): $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar os arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para rodar os testes
test: $(TEST_EXEC)
	$(TEST_EXEC)

# Regra para compilar o executável de testes
$(TEST_EXEC): $(TEST_OBJ_FILES) $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES)) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar os arquivos objeto de teste
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regras para criar os diretórios bin e obj se não existirem
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC) $(TEST_EXEC)

# Regra para rodar o programa principal
run: $(EXEC)
	$(EXEC) $(file)

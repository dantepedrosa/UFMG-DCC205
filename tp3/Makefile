# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
LDFLAGS = 

# Diretórios
SRC_DIR = src
TEST_DIR = test
INCLUDE_DIR = include
BIN_DIR = bin
OBJ_DIR = obj
DOC_DIR = doc

# Alvos principais
EXEC = $(BIN_DIR)/tp3.out
EXEC_INTERATIVO = $(BIN_DIR)/tp3_interativo.out
TEST_EXEC = $(BIN_DIR)/tests
TEST_MAIN_EXEC = $(BIN_DIR)/testeMain.out

# Headers
HEADERS = $(wildcard $(INCLUDE_DIR)/*.hpp)

# Arquivos fonte
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Objetos
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/test_%.o,$(TEST_FILES))
TEST_MAIN_OBJ = $(OBJ_DIR)/testeMain.o

# Alvos principais
.PHONY: all interativo clean doc stress debug memcheck help run

all: $(EXEC)

interativo: $(EXEC_INTERATIVO)

# Compila o executável principal
$(EXEC): $(filter-out $(OBJ_DIR)/mainPontoExtra.o $(OBJ_DIR)/testeMain.o,$(OBJS))
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -DMODO_PADRAO $^ -o $@ $(LDFLAGS)

# Compila o executável interativo
$(EXEC_INTERATIVO): $(filter-out $(OBJ_DIR)/main.o $(OBJ_DIR)/testeMain.o,$(OBJS))
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -DMODO_INTERATIVO $^ -o $@ $(LDFLAGS)

# Compila o executável de teste
$(TEST_MAIN_EXEC): $(TEST_MAIN_OBJ) $(filter-out $(OBJ_DIR)/main.o $(OBJ_DIR)/mainPontoExtra.o,$(OBJS))
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regra para objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para objetos de teste
$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para objeto de testeMain
$(OBJ_DIR)/testeMain.o: $(SRC_DIR)/testeMain.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilar e executar testes de stress
stress: $(TEST_MAIN_EXEC)
	for i in $$(seq 15 15 360); do \
		./$(TEST_MAIN_EXEC) $$i; \
		valgrind --leak-check=full --log-fd=1 ./$(TEST_MAIN_EXEC) $$i 2>&1 | \
		awk '/allocs/ || /LEAK SUMMARY/' | tr -s ' '; \
	done

# Gera documentação usando Doxygen
doc:
	@mkdir -p $(DOC_DIR)
	doxygen Doxyfile

# Executa com Valgrind para verificar vazamentos de memória
memcheck: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC) ./test/inputs/input_6.txt

memcheck-interativo: $(EXEC_INTERATIVO)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC_INTERATIVO)

# Debug com GDB
debug: CXXFLAGS += -g
debug: $(EXEC)
	gdb $(EXEC)

debug-interativo: CXXFLAGS += -g
debug-interativo: $(EXEC_INTERATIVO)
	gdb $(EXEC_INTERATIVO)

# Executa o programa com a entrada do arquivo ./test/inputs/input_6.txt
run: $(EXEC)
	./$(EXEC) ./test/inputs/input_6.txt

# Limpa arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)

# Exibe ajuda
help:
	@echo "Alvos disponíveis:"
	@echo "  all              : Compila o executável principal"
	@echo "  interativo       : Compila o executável interativo"
	@echo "  stress           : Compila e executa o testeMain com parâmetros de 50 a 1000"
	@echo "  doc              : Gera documentação com Doxygen"
	@echo "  memcheck         : Executa com Valgrind (versão padrão)"
	@echo "  memcheck-interativo: Executa com Valgrind (versão interativa)"
	@echo "  debug            : Executa com GDB (versão padrão)"
	@echo "  debug-interativo : Executa com GDB (versão interativa)"
	@echo "  clean            : Remove arquivos gerados"
	@echo "  help             : Exibe esta mensagem"

# Inclui dependências geradas automaticamente
-include $(OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)

# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Werror

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Source files
SRCS = $(SRCDIR)/mat.c $(SRCDIR)/matop.c
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Executável
TARGET = $(BINDIR)/matop

# Alvo padrão
all: $(TARGET)

# Linkar o executável
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^
	@chmod +x $(TARGET)

# Compilar arquivos fonte em arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar artefatos de build
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Executar o programa com os comandos especificados
run: $(TARGET)
	$(TARGET) -s -x 5 -y 5
	$(TARGET) -m -x 5 -y 5
	$(TARGET) -t -x 5 -y 5

.PHONY: all clean run
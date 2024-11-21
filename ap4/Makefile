# Ensure SRC is provided
ifndef SRC
$(error SRC is not set. Usage: make debug SRC=src/yourfile.c or make run SRC=src/yourfile.c)
endif

# Directories
BINDIR = bin
INCLUDEDIR = include
OBJDIR = obj
SRCDIR = src
LOGDIR = log

# Extract the base name without the .c extension
BASE_NAME = $(notdir $(basename $(SRC)))
OBJ = $(OBJDIR)/$(BASE_NAME).o
EXE = $(BINDIR)/$(BASE_NAME)

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -I$(INCLUDEDIR)

# Default target: compile the script with -g flag and run it
all: $(EXE)

# Compile the source file into an object file
$(OBJ): $(SRC)
	@mkdir -p $(BINDIR) $(OBJDIR) $(LOGDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the object file to create the executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $<

# Debug the script - Usage: make debug SRC=src/yourfile.c
debug: $(EXE)
	gdb ./$(EXE)

# Run without debugging - Usage: make run SRC=src/yourfile.c
run: $(EXE)
	./$(EXE)

memtest: $(EXE)
	valgrind --leak-check=full ./$(EXE)

# Clean build artifacts
clean:
	rm -f $(BINDIR)/* $(OBJDIR)/* $(LOGDIR)/*
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Iinclude

# Directories
SRCDIR = src
INCLUDEDIR = include
OBJDIR = obj
BINDIR = bin

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Executable name
TARGET = $(BINDIR)/heap

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
    @mkdir -p $(BINDIR)
    $(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
    @mkdir -p $(OBJDIR)
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
    rm -rf $(OBJDIR)/* $(BINDIR)/*

.PHONY: all clean
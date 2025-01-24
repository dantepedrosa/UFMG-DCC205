# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wno-all

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Default target
TARGET = $(BINDIR)/pa1.out

all: directories $(TARGET)

directories:
	mkdir -p $(OBJDIR) $(BINDIR)

$(TARGET):  $(OBJS) ; $(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c ; $(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/pa1.out

run: all
	$(TARGET) -z 9 -s 27 -a s
	$(TARGET) -z 9 -s 27 -a i
	$(TARGET) -z 9 -s 27 -a q
	$(TARGET) -z 9 -s 27 -a q3
	$(TARGET) -z 9 -s 27 -a qi
	$(TARGET) -z 9 -s 27 -a q3i
	$(TARGET) -z 9 -s 27 -a h
	$(TARGET) -z 9 -s 27 -a rs
	$(TARGET) -z 81 -s 17 -a s
	$(TARGET) -z 81 -s 17 -a i
	$(TARGET) -z 81 -s 17 -a q
	$(TARGET) -z 81 -s 17 -a q3
	$(TARGET) -z 81 -s 17 -a qi
	$(TARGET) -z 81 -s 17 -a q3i
	$(TARGET) -z 81 -s 17 -a h
	$(TARGET) -z 81 -s 17 -a rs
	$(TARGET) -z 448 -s 15 -a s
	$(TARGET) -z 448 -s 15 -a i
	$(TARGET) -z 448 -s 15 -a q
	$(TARGET) -z 448 -s 15 -a q3
	$(TARGET) -z 448 -s 15 -a qi
	$(TARGET) -z 448 -s 15 -a q3i
	$(TARGET) -z 448 -s 15 -a h
	$(TARGET) -z 448 -s 15 -a rs
	$(TARGET) -z 4803 -s 34 -a s
	$(TARGET) -z 4803 -s 34 -a i
	$(TARGET) -z 4803 -s 34 -a q
	$(TARGET) -z 4803 -s 34 -a q3
	$(TARGET) -z 4803 -s 34 -a qi
	$(TARGET) -z 4803 -s 34 -a q3i
	$(TARGET) -z 4803 -s 34 -a h
	$(TARGET) -z 4803 -s 34 -a rs
	$(TARGET) -z 19097 -s 25 -a s
	$(TARGET) -z 19097 -s 25 -a i
	$(TARGET) -z 19097 -s 25 -a q
	$(TARGET) -z 19097 -s 25 -a q3
	$(TARGET) -z 19097 -s 25 -a qi
	$(TARGET) -z 19097 -s 25 -a q3i
	$(TARGET) -z 19097 -s 25 -a h
	$(TARGET) -z 19097 -s 25 -a rs

.PHONY: all clean run
CC = gcc
CFLAGS = -I../include -Wall
OBJDIR = ../obj
BINDIR = ../bin

SRCS = matop.c mat.c matnomod.c
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/matop

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJDIR)/*.o $(TARGET)
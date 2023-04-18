CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) `pkg-config --cflags glib-2.0 libxml-2.0`
LIBS = `pkg-config --libs glib-2.0 libxml-2.0` -lm
BINDIR = bin
OBJDIR = obj
SRCDIR = src
INCDIR = include
TARGET = $(BINDIR)/main

# Recursively find all .c files in the src directory and its subdirectories
SOURCES := $(shell find $(SRCDIR) -type f -name '*.c')
# Convert each .c file path to a corresponding .o file path
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

all: $(BINDIR) $(OBJDIR) $(TARGET)

# Create the bin directory if it does not exist
$(BINDIR):
	mkdir -p $(BINDIR)

# Create the obj directory if it does not exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile each source file into an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $(OBJDIR)/$*.o)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Clean up the obj and bin directories
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean

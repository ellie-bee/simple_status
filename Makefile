# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I.

# Directories
BUILDDIR = build
BINDIR = bin

# Target executable
TARGET = $(BINDIR)/main

# Source and object files
SOURCES = $(wildcard *.c) $(wildcard status_components/*.c)
OBJECTS = $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCES)))

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $(TARGET) -ggdb -lX11

# Compile source files into object files
$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -ggdb

$(BUILDDIR)/%.o: status_components/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -ggdb

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Create bin directory
$(BINDIR):
	mkdir -p $(BINDIR)

# Clean up build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Phony targets
.PHONY: all clean

# Automatically generate dependencies
-include $(OBJECTS:.o=.d)

# Rule to generate dependency files
$(BUILDDIR)/%.d: %.c | $(BUILDDIR)
	@$(CC) $(CFLAGS) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILDDIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(BUILDDIR)/%.d: status_components/%.c | $(BUILDDIR)
	@$(CC) $(CFLAGS) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILDDIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Executable name
TARGET = analyzer

# Source files
SRCS = $(filter-out test.c, $(wildcard *.c)) 

# Header files
HEADERS = $(wildcard *.h) 

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything
rebuild: clean all


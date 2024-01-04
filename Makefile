# Makefile for your project

# Compiler
CC = gcc

# Source and Build directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Compiler flags
CFLAGS = -lGLU -lGL -lX11 -lm -Werror=vla -Og

# Output executable
TARGET = out

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)

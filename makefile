# Compiler
CXX = g++

# Common compiler flags
CXXFLAGS = -Wall -Wextra

# Debug-specific flags
DEBUG_FLAGS = -DDEBUG -g

# Release-specific flags
RELEASE_FLAGS = -O2

# Target executable
TARGET = main

# Source files
SRCS = main.cpp bingo.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target (release build)
all: release

# Debug target
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Release target
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all debug release clean

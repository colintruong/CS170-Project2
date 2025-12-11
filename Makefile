# Compiler
CXX = g++
# C++ standard
CXXFLAGS = -std=c++23 -g
# Output executable name
TARGET = test.exe
# Source files (all .cpp in folder)
SRCS = $(wildcard *.cpp)
# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target: build everything
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)

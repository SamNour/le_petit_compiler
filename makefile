CXX = /usr/bin/g++
CXXFLAGS = -fdiagnostics-color=always -g -ggdb -pedantic-errors -Werror -std=c++23
SRC = $(wildcard src/*.cpp) # Get all .cpp files in the current directory

# Default target
all: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o main

# Target to format the code using clang-format
format:
	clang-format -i $(SRC)

clean:
	rm -f main

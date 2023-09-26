CPP = g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic
SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp) $(wildcard src/*/*/*/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = mmc

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN)

.PHONY: clean run valgrind
clean:
	@rm $(OBJ)
	@rm $(BIN)
run: $(BIN)
	@./$(BIN)
valgrind: $(BIN)
	@valgrind --leak-check=full -s ./$(BIN)

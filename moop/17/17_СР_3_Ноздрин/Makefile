FLAGS=-Wall -O0 -g
COMP=g++
GCC=gcc
NAME=runable
PIECES=main.cpp array.h array.cpp

$(NAME): $(PIECES) 
	$(COMP) $(FLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(NAME)

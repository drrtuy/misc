FLAGS=-Wall -O0 -g
COMP=g++
GCC=gcc
NAME=runable
PIECES=main.cpp module.cpp module.h dec.cpp dec.h

$(NAME): $(PIECES) 
	$(COMP) $(FLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(NAME)

FLAGS=-Wall -O0 -g
COMP=g++
GCC=gcc
NAME=runable
PIECES=main.cpp date.h date.cpp module.cpp module.h

$(NAME): $(PIECES) 
	$(COMP) $(FLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(NAME)

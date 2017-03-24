FLAGS=-Wall -O0 -g
COMP=g++
GCC=gcc
NAME=runable

$(NAME): main.cpp module.cpp module.h
	$(COMP) $(FLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(NAME)

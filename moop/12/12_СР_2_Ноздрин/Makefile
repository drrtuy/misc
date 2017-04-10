FLAGS=-Wall -O0 -g
COMP=g++
GCC=gcc
NAME=runable
PIECES=main.cpp bitstring.h bitstring.cpp module.h module.cpp

$(NAME): $(PIECES)
	$(COMP) $(FLAGS) $^ -o $@

.PHONY: cean

clean:
	rm -f $(NAME)

FLAGS=-Wall -O0 -g
COMP=g++
GCC=gcc

runable: main.cpp module.cpp module.h
	$(COMP) $(FLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f runable

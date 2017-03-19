FLAGS=-Wall -O0 -g
COMP=g++
GCC=gcc

sl_4: main.c module.c module.h
	$(GCC) $(FLAGS) $^ -o $@

unit: ./tests/unit.c ./tests/unity.c ./tests/unity.h ./module.c
	$(GCC) -I./ $(FLAGS) $^ -o $@ 

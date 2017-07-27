FLAGS=-Wall -O0 -g -I/usr/include/postgresql #-I/usr/src/linux-headers-4.9.0-0.bpo.3-common/include/linux
LDFLAGS=-lpq
GCC=gcc
NAME=runable
PIECES=main.c executer.h executer.c

$(NAME): $(PIECES) 
	$(GCC) $(FLAGS) $(LDFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(NAME)

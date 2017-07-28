FLAGS=-Wall -O0 -g -L/usr/pgsql-9.4/lib -I/usr/include/postgresql -I/usr/pgsql-9.4/include/ #-I/usr/src/linux-headers-4.9.0-0.bpo.3-common/include/linux
LDFLAGS=-lpq
GCC=gcc
NAME=runable
PIECES=main.c executer.h executer.c

$(NAME): $(PIECES) 
	$(GCC) $(FLAGS) $(LDFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(NAME)

FLAGS=-std=gnu11 -Wall -O0 -g 
PPCFLAGS=
LDFLAGS=
GCC=gcc
NAME=netcp
PIECES=main.c netcp.c

$(NAME): $(PIECES) 
	$(GCC) $(FLAGS) $(PPCFLAGS) $(LDFLAGS) $^ -o $@

client: client.c
	$(GCC) $(FLAGS) $(PPCFLAGS) $(LDFLAGS) $^ -o -bash

.PHONY: clean

clean:
	rm -f $(NAME)
	rm -f client

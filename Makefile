all: main
.PHONY: main
main: main.c fibheap.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -rf *.o main
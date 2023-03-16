all: my_echo 

my_echo: main.o
	gcc -m32 -g -Wall -o my_echo main.o 

main.o: main.c
	gcc -g -Wall -m32 -c -o main.o main.c 

.PHONY: clean

clean:
	rm -f *.0
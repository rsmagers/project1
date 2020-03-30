all: 
	make clean
	gcc -pedantic -Wall -g -o project1 project1.c
clean:
	-rm ./project1

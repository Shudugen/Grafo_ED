# -*- Makefile -*-

executavel: funcoes.o main.o headers.h
	gcc funcoes.o main.o -o executavel
main.o: main.c headers.h
	gcc -c main.c
funcoes.o: funcoes.c headers.h
	gcc -c funcoes.c
clean:
	rm *.o executavel

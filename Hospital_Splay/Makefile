#This is makefile for project

project: main.o Splay.o
	cc main.o Splay.o -o project
main.o: main.c Splay.h
	cc -c main.c 
Splay.o: Splay.c Splay.h
	cc -c Splay.c
clean:
	rm * o project

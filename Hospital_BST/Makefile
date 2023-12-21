#This is makefile for project

project: main.o Vanilla.o
	cc main.o Vanilla.o -o project
main.o: main.c Vanilla.h
	cc -c main.c 
Vanilla.o: Vanilla.c Vanilla.h
	cc -c Vanilla.c
clean:
	rm * o project

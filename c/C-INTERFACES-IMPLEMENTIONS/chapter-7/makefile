list : main.o list.o
	cc -o list main.o list.o -g

main.o : list.h
	cc -c -g -o main.o main.c
list.o : list.h
	cc -c -g -o list.o list.c

clean :
	rm list *.o

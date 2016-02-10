arrstack : main.o arr_stack.o
	cc -o arrstack main.o arr_stack.o
main.o : arr_stack.h
arr_stack.o : arr_stack.h

clean:
	rm arrstack *.o

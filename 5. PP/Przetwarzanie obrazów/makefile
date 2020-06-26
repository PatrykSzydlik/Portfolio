__start__: a.out
	./a.out

a.out: main.o edit.o file.o
	gcc main.o edit.o file.o

main.o: main.c main.h
	gcc -c -Wall -pedantic main.c

edit.o: edit.c main.h edit.h
	gcc -c -Wall -pedantic edit.c

file.o: file.c main.h file.h
	gcc -c -Wall -pedantic file.c



a.out: main2.o edit2.o file2.o arg.o
	gcc main2.o edit2.o file2.o arg.o

main2.o: main2.c main.h
	gcc -c -Wall -pedantic main2.c

edit2.o: edit2.c main.h edit.h
	gcc -c -Wall -pedantic edit2.c

file2.o: file2.c main.h file.h
	gcc -c -Wall -pedantic file2.c

arg.o: arg.c arg.h main.h
	gcc -c -Wall -pedantic arg.c

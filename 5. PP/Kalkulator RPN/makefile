a.out: main.o kalk.o strukt.o
	gcc main.o kalk.o strukt.o

main.o: main.c main.h kalk.h strukt.h
	gcc -c -Wall -pedantic main.c

kalk.o: kalk.c main.h kalk.h strukt.h
	gcc -c -Wall -pedantic kalk.c

strukt.o: strukt.c main.h strukt.h
	gcc -c -Wall -pedantic strukt.c

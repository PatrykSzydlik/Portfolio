#
#	Compilation options
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

#
#	Building tree
#

run: build
	./exec/graphs 1> testy.txt

build: obj obj/main.o
	g++ -Wall -pedantic -std=c++0x -o exec/graphs obj/main.o

obj:
	mkdir obj

obj/main.o: src/main.cpp inc/time_measurements.hh inc/list.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp


clean:
	rm -f obj/*.o exec/*

cleanlog:
	rm -f log/* routes/* time_log.txt
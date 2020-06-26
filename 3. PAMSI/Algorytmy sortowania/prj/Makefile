#
#	Compilation options
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

#
#	Building tree
#

__start__: sorting_algorithms
	./sorting_algorithms 1> testy.txt

sorting_algorithms: obj obj/main.o
	g++ -Wall -pedantic -std=c++0x -o sorting_algorithms obj/main.o

obj:
	mkdir obj

obj/main.o: src/main.cpp inc/quicksort.hh inc/random_data_generation.hh inc/mergesort.hh inc/introsort.hh inc/insertionsort.hh inc/heapsort.hh inc/time_measurements.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp


clean:
	rm -f obj/*.o sorting_algorithms
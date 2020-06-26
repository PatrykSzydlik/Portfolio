#
#	Compilation options
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

#
#	Building tree
#

__start__: tik_tak_toe
	./tik_tak_toe 

tik_tak_toe: obj obj/main.o
	g++ ${CXXFLAGS} -o tik_tak_toe obj/main.o -lsfml-graphics -lsfml-window -lsfml-system

obj:
	mkdir obj

obj/main.o: src/main.cpp
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp


clean:
	rm -f obj/*.o tik_tak_toe
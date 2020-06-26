#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

__start__: rotation_2D
	./rotation_2D

rotation_2D: obj obj/main.o obj/Rectangle.o obj/Matrix2x2.o obj/Vector2D.o\
           obj/gnuplot_link.o
	g++ -Wall -pedantic -std=c++0x -o rotation_2D obj/main.o obj/Vector2D.o\
                        obj/Matrix2x2.o obj/Rectangle.o obj/gnuplot_link.o

obj:
	mkdir obj

obj/gnuplot_link.o: inc/gnuplot_link.hh src/gnuplot_link.cpp
	g++ -c ${CXXFLAGS} -o obj/gnuplot_link.o src/gnuplot_link.cpp

obj/main.o: src/main.cpp inc/Rectangle.hh inc/Matrix2x2.hh inc/Vector2D.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/Rectangle.o: src/Rectangle.cpp inc/Rectangle.hh
	g++ -c ${CXXFLAGS} -o obj/Rectangle.o src/Rectangle.cpp

obj/Matrix2x2.o: src/Matrix2x2.cpp inc/Matrix2x2.hh 
	g++ -c ${CXXFLAGS} -o obj/Matrix2x2.o src/Matrix2x2.cpp

obj/Vector2D.o: src/Vector2D.cpp inc/Vector2D.hh
	g++ -c ${CXXFLAGS} -o obj/Vector2D.o src/Vector2D.cpp

clean:
	rm -f obj/*.o rotation_2D

#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++11

__start__: rotation_3D
	./rotation_3D

rotation_3D: obj obj/main.o obj/gnuplot_link.o
	g++ -Wall -pedantic -std=c++11 -o rotation_3D obj/main.o \
                        obj/gnuplot_link.o

obj:
	mkdir obj

obj/gnuplot_link.o: inc/gnuplot_link.hh src/gnuplot_link.cpp
	g++ -c ${CXXFLAGS} -o obj/gnuplot_link.o src/gnuplot_link.cpp

obj/main.o: src/main.cpp inc/Figure.hh inc/Matrix.hh inc/Prism.hh inc/Vector.hh inc/Object3D.hh inc/NEW_Matrix.hh  inc/NEW_Vector.hh  inc/Hex_prism.hh  inc/Rotor.hh  inc/Drone.hh  inc/Cuboid.hh  inc/Body.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp


clean:
	rm -f obj/*.o rotation_3D

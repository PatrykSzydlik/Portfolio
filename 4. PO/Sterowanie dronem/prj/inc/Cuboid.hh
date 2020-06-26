/*!
   \file Cuboid.hh
   \brief Definiuje prostopadłościan na podstawie wzorca
   \author Patryk Szydlik
   \date 03.05.2019
 */
#pragma once

#include "Prism.hh"
#include "Object3D.hh"

/*!
 * \brief Klasa modeluje bryłę prostopadłościanu z metodami wyswietlajacymi
 */
class Cuboid : public Prism<4>{
        static int Amount_of_cuboids; /*!< Zmienna ilosc istniejacych cuboid */
public:

        Cuboid(float a, float b, float h) : Prism<4>(a,b,h)  {
                NEW_Vector offset;
                offset[OZ]=h/2;
                ++Amount_of_cuboids;


        }

        virtual ~Cuboid(){
                --Amount_of_cuboids;
        }

        /*!
           \brief Zlicza ilosc aktualnych cuboid
           \return Ilość istniejących cuboid
         */

        static int Read_amount(){
                return Amount_of_cuboids;
        }

        /*!
           \brief Wyswietla wspolrzedne bryly
           \param Strm strumien wyjsciowy
         */
        void Display(std::ostream &Strm) {
                NEW_Vector sym_coord;

                for(int i=0; i<4; ++i) {sym_coord[OY]+=_Faces[UP][i][OY]; };
                for(int i=0; i<4; ++i) {sym_coord[OX]+=_Faces[UP][i][OX]; };
                for(int i=0; i<4; ++i) {sym_coord[OZ]+=_Faces[UP][i][OZ]; };
                sym_coord[OX]=sym_coord[OX]/4;
                sym_coord[OY]=sym_coord[OY]/4;
                sym_coord[OZ]=sym_coord[OZ]/4;
                NEW_Vector sym_axis_up(sym_coord[OX],sym_coord[OY],sym_coord[OZ]);

                sym_coord[OX]=0.0;
                sym_coord[OY]=0.0;
                sym_coord[OZ]=0.0;
                for(int i=0; i<4; ++i) {sym_coord[OX]+=_Faces[DOWN][i][OX]; };
                for(int i=0; i<4; ++i) {sym_coord[OY]+=_Faces[DOWN][i][OY]; };
                for(int i=0; i<4; ++i) {sym_coord[OZ]+=_Faces[DOWN][i][OZ]; };
                sym_coord[OX]=sym_coord[OX]/4;
                sym_coord[OY]=sym_coord[OY]/4;
                sym_coord[OZ]=sym_coord[OZ]/4;
                NEW_Vector sym_axis_down(sym_coord[OX],sym_coord[OY],sym_coord[OZ]);

                for(int i=0; i<4; ++i) {
                        Strm<<sym_axis_down<<endl;
                        Strm<<this->_Faces[DOWN][i]<<endl;
                        Strm<<this->_Faces[UP][i]<<endl;
                        Strm<<sym_axis_up<<endl<<"#"<<endl<<endl;
                }
                Strm<<sym_axis_down<<endl;
                Strm<<this->_Faces[DOWN][0]<<endl;
                Strm<<this->_Faces[UP][0]<<endl;
                Strm<<sym_axis_up<<endl<<"#"<<endl<<endl;
                Strm<<endl<<endl<<endl;
        }

        /*!
           \brief Funkcja sprawdzajaca rownosc i wyswietlajaca dlugosci krawedzi bryly
         */
        void EdgesLenght()  const {
                float lenght[4];
                for(int i=0; i<4; ++i) {lenght[i]=0; };


                lenght[0]=(_Faces[DOWN][0]-_Faces[DOWN][1]).Lenght();
                lenght[1]=(_Faces[DOWN][2]-_Faces[DOWN][3]).Lenght();
                lenght[2]=(_Faces[UP][0]-_Faces[UP][1]).Lenght();
                lenght[3]=(_Faces[UP][2]-_Faces[UP][3]).Lenght();
                if(lenght[0]!=lenght[1] || lenght[1]!=lenght[2] || lenght[2]!=lenght[3] || lenght[3]!=lenght[1] ) {
                        cout << "OX opposite edges are not equal to each other:"<<endl;
                }else{
                        cout << "OX opposite edges are equal to each other:"<<endl;
                };

                for(int i=0; i<4; ++i) {
                        cout << "Edge "<<i+1<<" = "<<std::setw(16) << std::fixed << std::setprecision(10)<<lenght[i]<<endl;
                };


                lenght[0]=(_Faces[DOWN][2]-_Faces[DOWN][1]).Lenght();
                lenght[1]=(_Faces[DOWN][0]-_Faces[DOWN][3]).Lenght();
                lenght[2]=(_Faces[UP][2]-_Faces[UP][1]).Lenght();
                lenght[3]=(_Faces[UP][0]-_Faces[UP][3]).Lenght();
                if(lenght[0]!=lenght[1] || lenght[1]!=lenght[2] || lenght[2]!=lenght[3] || lenght[3]!=lenght[1] ) {
                        cout << "OY opposite edges are not equal to each other:"<<endl;
                }else{
                        cout << "OY opposite edges are equal to each other:"<<endl;
                };

                for(int i=0; i<4; ++i) {
                        cout << "Edge "<<i+1<<" = "<<std::setw(16) << std::fixed << std::setprecision(10)<<lenght[i]<<endl;
                };

                lenght[0]=(_Faces[DOWN][0]-_Faces[UP][0]).Lenght();
                lenght[1]=(_Faces[DOWN][1]-_Faces[UP][1]).Lenght();
                lenght[2]=(_Faces[DOWN][2]-_Faces[UP][2]).Lenght();
                lenght[3]=(_Faces[DOWN][3]-_Faces[UP][3]).Lenght();
                if(lenght[0]!=lenght[1] || lenght[1]!=lenght[2] || lenght[2]!=lenght[3] || lenght[3]!=lenght[1] ) {
                        cout << "OZ opposite edges are not equal to each other:"<<endl;
                }else{
                        cout << "OZ opposite edges are equal to each other:"<<endl;
                };

                for(int i=0; i<4; ++i) {
                        cout << "Edge "<<i+1<<" = "<<std::setw(16) << std::fixed << std::setprecision(10)<<lenght[i]<<endl;
                };
        }


};

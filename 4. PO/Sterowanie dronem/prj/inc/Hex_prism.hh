/*!
   \file Hex_prism.hh
   \brief Definiuje graniastosłup sześciokątny na podstawie wzorca
   \author Patryk Szydlik
   \date 03.05.2019
 */
#pragma once

#include "Prism.hh"

/*!
 * \brief Klasa modeluje bryle prostopadloscianu szesciokatnego prostego
 */
class Hex_prism : public Prism<6>{
        static int Amount_of_hexprism; /*!< Zmienna ilosc istniejacych hexprism */
public:

        Hex_prism(float a,float b, float h) : Prism<6>(a,0.0,h){
                NEW_Vector offset;
                offset[OZ]=h/2;
                ++Amount_of_hexprism;

        }

        virtual ~Hex_prism(){
                --Amount_of_hexprism;
        }

        /*!
           \brief Zlicza ilosc aktualnych hexprism
           \return Ilość istniejących hexprism
         */
        static int Read_amount(){
                return Amount_of_hexprism;
        }

        /*!
           \brief Wyswietla wspolrzedne bryly
           \param Strm strumien wyjsciowy
         */
        void Display(std::ostream &Strm) const {
                NEW_Vector sym_coord;

                for(int i=0; i<6; ++i) {sym_coord[OX]+=_Faces[UP][i][OX]; };
                for(int i=0; i<6; ++i) {sym_coord[OY]+=_Faces[UP][i][OY]; };
                for(int i=0; i<6; ++i) {sym_coord[OZ]+=_Faces[UP][i][OZ]; };
                sym_coord[OX]=sym_coord[OX]/6;
                sym_coord[OY]=sym_coord[OY]/6;
                sym_coord[OZ]=sym_coord[OZ]/6;

                NEW_Vector sym_axis_up(sym_coord[OX],sym_coord[OY],sym_coord[OZ]);

                sym_coord[OX]=0.0;
                sym_coord[OY]=0.0;
                sym_coord[OZ]=0.0;

                for(int i=0; i<6; ++i) {sym_coord[OX]+=_Faces[DOWN][i][OX]; };
                for(int i=0; i<6; ++i) {sym_coord[OY]+=_Faces[DOWN][i][OY]; };
                for(int i=0; i<6; ++i) {sym_coord[OZ]+=_Faces[DOWN][i][OZ]; };
                sym_coord[OX]=sym_coord[OX]/6;
                sym_coord[OY]=sym_coord[OY]/6;
                sym_coord[OZ]=sym_coord[OZ]/6;

                NEW_Vector sym_axis_down(sym_coord[OX],sym_coord[OY],sym_coord[OZ]);

                for(int i=0; i<6; ++i) {
                        Strm<<sym_axis_down<<endl;
                        Strm<<this->_Faces[DOWN][i]<<endl;
                        Strm<<this->_Faces[UP][i]<<endl;
                        Strm<<sym_axis_up<<endl<<"#"<<endl<<endl;
                }
                Strm<<sym_axis_down<<endl;
                Strm<<this->_Faces[DOWN][0]<<endl;
                Strm<<this->_Faces[UP][0]<<endl;
                Strm<<sym_axis_up<<endl<<"#"<<endl<<endl;
                Strm<<endl<<endl;

        }

        /*!
           \brief Funkcja sprawdzajaca rownosc i wyswietlajaca dlugosci krawedzi bryly
         */
        void EdgesLenght() const {
                float lenght[3];
                for(int i=0; i<3; ++i) {lenght[i]=0; };


                lenght[0]=(_Faces[DOWN][0]-_Faces[DOWN][1]).Lenght();
                lenght[1]=(_Faces[DOWN][1]-_Faces[DOWN][2]).Lenght();
                lenght[2]=(_Faces[DOWN][0]-_Faces[DOWN][2]).Lenght();
                if(lenght[0]!=lenght[1] || lenght[1]!=lenght[2] || lenght[2]!=lenght[0] ) {
                        cout << "Edges of first face are not equal to each other:"<<endl;
                }else{
                        cout << "Edges of first face are equal to each other:"<<endl;
                };

                for(int i=0; i<3; ++i) {
                        cout << "Edge "<<i+1<<" = "<<std::setw(16) << std::fixed << std::setprecision(10)<<lenght[i]<<endl;
                };


                lenght[0]=(_Faces[UP][0]-_Faces[UP][1]).Lenght();
                lenght[1]=(_Faces[UP][2]-_Faces[UP][1]).Lenght();
                lenght[2]=(_Faces[UP][0]-_Faces[UP][2]).Lenght();
                if(lenght[0]!=lenght[1] || lenght[1]!=lenght[2] || lenght[2]!=lenght[0]) {
                        cout << "Edges of second face are not equal to each other:"<<endl;
                }else{
                        cout << "Edges of second face are equal to each other:"<<endl;
                };

                for(int i=0; i<3; ++i) {
                        cout << "Edge "<<i+1<<" = "<<std::setw(16) << std::fixed << std::setprecision(10)<<lenght[i]<<endl;
                };

                lenght[0]=(_Faces[DOWN][0]-_Faces[UP][0]).Lenght();
                lenght[1]=(_Faces[DOWN][1]-_Faces[UP][1]).Lenght();
                lenght[2]=(_Faces[DOWN][2]-_Faces[UP][2]).Lenght();
                if(lenght[0]!=lenght[1] || lenght[1]!=lenght[2] || lenght[2]!=lenght[0]) {
                        cout << "Side edges are not equal to each other:"<<endl;
                }else{
                        cout << "Side edges are equal to each other:"<<endl;
                };

                for(int i=0; i<3; ++i) {
                        cout << "Edge "<<i+1<<" = "<<std::setw(16) << std::fixed << std::setprecision(10)<<lenght[i]<<endl;
                };


        }



};

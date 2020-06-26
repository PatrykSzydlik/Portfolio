/*!
   \file NEW_Vector.hh
   \brief Definiuje klase wektora 3D na bazie wzorca
   \author Patryk Szydlik
   \date 04.05.2019
 */

#pragma once

#include "Vector.hh"

/*!
 * \brief Klasa definiuje wektor trójwymiarowy wraz z metodami liczącymi ich ilość 
 */
class NEW_Vector : public Vector<float,3> {
        static int Amount_of_vectors; /*!< Zmienna ilosc istniejacych wektorow */
        static int Created_vectors;/*!< Zmienna suma dotychczas utworzonych wektorów */

public:
        NEW_Vector() {
                for(int i=0; i<3; i++) coordinates[i]=0;
                ++Amount_of_vectors;
                ++Created_vectors;
        };

        NEW_Vector(Vector<float,3> W) {
                for(int i=0; i<3; i++) coordinates[i]=W[i];
                ++Amount_of_vectors;
                ++Created_vectors;
        };

        NEW_Vector(float x, float y,float z)
        {
                coordinates[OX]=x;
                coordinates[OY]=y;
                coordinates[OZ]=z;
                ++Amount_of_vectors;
                ++Created_vectors;
        };
        NEW_Vector(const NEW_Vector& W){
                ++Amount_of_vectors;
                ++Created_vectors;
                coordinates[OX]=W[OX];
                coordinates[OY]=W[OY];
                coordinates[OZ]=W[OZ];

        };
        virtual ~NEW_Vector(){
                --Amount_of_vectors;
        }
/*!
   \brief Pozwala na szybką zmianę wszystkich 3 parametrów wektora
   \param x wspolrzedna OX
   \param y wspolrzedna OY
   \param z wspolrzedna OZ
   \return BRAK
 */
        void change(float x, float y, float z){
                (*this)[OX]=x;
                (*this)[OY]=y;
                (*this)[OZ]=z;
        }
/*!
   \brief Zlicza ilosc aktualnych wektorow
   \return Ilość istniejących wektorów
 */
        static int Read_amount() {
                return Amount_of_vectors;
        };
        /*!
           \brief Zlicza ilosc stworzonych dotychczas wektorow
           \return Ilość wektorów stworzonych od uruchomienia programu
         */
        static int Read_sum() {
                return Created_vectors;
        };

}; //koniec klasy NEW_Vector+

/*!
   \file Body.hh
   \brief Zawiera klase i metody obslugujace kadłub
   \author Patryk Szydlik
   \date 20.04.19
 */
#pragma once

#include "Object3D.hh"
#include "Cuboid.hh"

/*!
 * \brief Klasa tworzy model kadłuba dla klasy dron
 */
class Body : public Object3D {
        Cuboid Object;
        static int Amount_of_bodies; /*!< Ilośc aktualnie istniejacych kadłubów */
public:
        Body(float a, float b, float h) : Object(a,b,h) {
                ++Amount_of_bodies;
        }

        Body(const Body & obs) : Object(obs.Object){
                ++Amount_of_bodies;
        }
        virtual ~Body(){
                --Amount_of_bodies;
        }
/*!
   \brief Zwraca ilośc istniejących kadłubów dronów
   \return Wartośc istniejących kadłubów dronów
 */
        static int Read_amount(){
                return Amount_of_bodies;
        }

/*!
   \brief Wywoluje sprawdzenie dlugosci krawedzi kadłuba
   \return Brak
 */
        void EdgesLenght(){
                Object.EdgesLenght();
        }

        /*!
           \brief Wyswietla wspolrzedne rotora
           \param Strm strumien wyjsciowy
         */


        virtual void Display(std::ostream &Strm){
                Cuboid result(Object);
                result.Turn(rotation[1]);
                result.Move(position);
                result.Display(Strm);
        }
};

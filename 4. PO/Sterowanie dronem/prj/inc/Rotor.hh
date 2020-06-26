/*!
   \file Rotor.hh
   \brief Zawiera klase i metody obslugujace rotor
   \author Patryk Szydlik
   \date 20.04.19
 */
#pragma once
#include "Object3D.hh"
#include "Hex_prism.hh"

/*!
 * \brief Klasa tworzy model rotora dla klasy dron wraz z metodami obsługującymi go
 */
class Rotor : public Object3D {
        Hex_prism Object;
        static int Amount_of_rotors; /*!< Ilosc aktualnie istniejacych rotorów */
        NEW_Vector center;
        float spin; /*!< Kierunek obrotu rotoru */
        float speed; /*!< prędkość obrotu rotoru */
        NEW_Matrix spin_rot; /*!< zmienna zapisujaca macierz rotacji rotora */
public:
        Rotor(float radius, float height,NEW_Vector pos, float new_spin) : Object(radius,0.0,height) {
                center=pos;
                ++Amount_of_rotors;
                spin=new_spin;
                speed=1;
        }

        virtual ~Rotor(){
                --Amount_of_rotors;
        }

        /*!
           \brief Czyta ilosc aktualnie istniejacych rotorow
           \return Wartosc istniejacych aktualnie rotorow
         */
        static int Read_amount(){
                return Amount_of_rotors;
        }




        /*!
           \brief Zmienia punkt środkowy obiektu.
           \param V wektor przesunięcia
           \return Brak
         */

        void Change_center(const NEW_Vector &V){
                center=center+V;
        }


        /*!
           \brief Wyswietla wspolrzedne rotora
           \param Strm strumien wyjsciowy
         */


        virtual void Display(std::ostream &Strm) {
                Hex_prism result(Object);
                result.Turn(spin_rot);
                result.Move(center);
                result.Turn(rotation[1]);
                result.Move(position);
                result.Display(Strm);
        }
        /*!
           \brief Zwraca wartosc spinu
           \return Wartość spinu rotora
         */
        int Read_spin() const {
                return spin;
        }
/*!
   \brief Zwraca wartość prędkości obrotu
   \return Wartość prędkości obrotu
 */
        int Read_speed() const {
                return speed;
        }

/*!
   \brief Zmienia wartośc prędkości obrotu rotora
   \param new_speed nowa prędkość obrotowa
   \return Brak
 */
        void Change_speed(float new_speed){
                speed=new_speed;
        }

/*!
   \brief Obraca rotory podczas ruchu
   \param seconds czas wirowania rotoru
   \return Brak
 */
        void Spin(float seconds){
                NEW_Matrix spin_new;
                spin_new.Add(speed*seconds*spin,'z');
                spin_rot=spin_new*spin_rot;
        }

};

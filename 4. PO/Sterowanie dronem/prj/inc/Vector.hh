/*!
   \file Vector.hh
   \brief Zawiera szablok klasy Wektor
   \author Patryk Szydlik
   \date 02.04.2019
 */
#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>

#define OX 0 /** indeks wsp X*/
#define OY 1 /** indeks wsp Y*/
#define OZ 2 /** indeks wsp Z*/

using namespace std;
/*!
 * \brief Klasa modelujaca wektor dowolnych rozmiarow do opisania punktow w przestrzeni
 */
template<typename COORD, int SIZE>
class Vector {

protected:

        COORD coordinates[SIZE]; /*!< wspolrzedne wektora */

public:
        Vector() {
                for(int i=0; i<SIZE; i++) coordinates[i]=0;
        };

        virtual ~Vector(){
        };

/*!
   \brief Pobieranie wartości współrzędnych wektora
   \param Ind - indeks pobranej zmiennej
   \pre indeks nie wychodzi poza tablice
   \return wartosc zmiennej
 */
        COORD operator[] (int Ind) const {       /* P wartości */
                if(Ind>SIZE) {cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!"; return 0.0; };
                return this->coordinates[Ind];
        }
        /*!
             \brief Pobieranie wartości współrzędnych wektora
             \param Ind - indeks pobranej zmiennej
             \pre indeks nie wychodzi poza tablice
             \return referencja na wartosc zmiennej
         */
        COORD& operator[] (int Ind)    {        /* L Wartości */
                if(Ind>SIZE) {
                        cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!";
                };
                return this->coordinates[Ind];
        }
/*!
   \brief wyswietla wektora na ostream
   \param Strm - referencja do strumienia
 */
        void Display(std::ostream &Strm) const {
                for(int i=0; i<SIZE; i++)
                        Strm << std::setw(16) << std::fixed << std::setprecision(10) << this->coordinates[i];
        }
/*!
   \brief dodawanie wektorow
   \param W vector
   \return zwraca referencją wynik dodawania
 */
        Vector<COORD,SIZE> & operator += (const Vector<COORD,SIZE> &W){
                for(int i=0; i<SIZE; ++i) {
                        (*this)[i]=(*this)[i]+W[i];
                };
                return *this;
        }

        /*!
           \brief kopiowanie wektorow
           \param W vector
           \return zwraca referencją wynik dodawania
         */
        Vector<COORD,SIZE> & operator = (const Vector<COORD,SIZE> &W){
                for(int i=0; i<SIZE; i++)
                        (*this)[i]=W[i];
                return *this;
        }

        /*!
           \brief dodawanie wektorow
           \param W vector stały
           \return zwraca wynik dodawania
         */
        Vector<COORD,SIZE>& operator + (const Vector<COORD,SIZE> &W) const {
                Vector<COORD,SIZE> Sum=*this;
                return Sum+=W;
        }
        /*!
           \brief odejmowanie wektorow
           \param W vector const
           \return zwraca referencją wynik odejmowania
         */
        Vector<COORD,SIZE>& operator - (const Vector<COORD,SIZE> &W) const {
                Vector<COORD,SIZE> Sum=*this;
                Vector<COORD,SIZE> Diff;
                for(int i=0; i<SIZE; ++i) {
                        Diff[i]=-1*W[i];
                };
                return Sum+Diff;
        }
        /*!
           \brief mnozenie wektora przez liczbe
           \param multiplier - mnoznik
           \return zwraca referencją wynik mnozenia
         */
        Vector<COORD,SIZE> operator * (float multiplier) const {
                Vector<COORD,SIZE> Sum=*this;
                for(int i=0; i<SIZE; i++)
                        Sum[i]=Sum[i]*multiplier;

                return Sum;
        }


        /*!
           \brief mnozenie wektora przez liczbe
           \param multiplier - mnoznik
           \return zwraca referencją wynik mnozenia
         */
        Vector<COORD,SIZE> operator * (const Vector<COORD,SIZE>& V2) const {
                Vector<COORD,SIZE> Sum;
                Sum[0]=(*this)[1]*V2[2]-(*this)[2]*V2[1];
                Sum[1]=(*this)[2]*V2[0]-(*this)[0]*V2[2];
                Sum[2]=(*this)[0]*V2[1]-(*this)[1]*V2[0];
                return Sum;
        }

/*!
   \brief Oblicza iloczyn skalarny wektorów
   \param V2 wektor przez który mnożymy
   \return wynik mnożenia
 */

        COORD operator & (const Vector<COORD,SIZE>& V2) const {//iloczyn skalarny
                COORD result=0;
                for(int Ind=0; Ind<SIZE; ++Ind) {
                        result += (*this)[Ind]*V2[Ind];
                };
                return result;
        }

/*!
   \brief Oblicza długość wektora
   \return Zwraca wartość długości
 */
        double Lenght () const {
                COORD result;
                result=*this & *this;
                return sqrt(result);
        }
}; //koniec klasy Vector

/*!
   \brief Wyświetla wektor na stdo
   \param Strm strumien wyjscia
    \param W wektor wyświetlany
   \return referencja do strumienia
 */
template <typename COORD,int SIZE>
ostream& operator << (ostream &Strm,const Vector<COORD,SIZE> &W){
        for(int i=0; i<SIZE; i++)
                Strm << std::setw(16) << std::fixed << std::setprecision(10) << W[i];
        return Strm;
}

/*!
   \brief Wczytuje wektor z stdi
   \param Strm strumien wejscia
    \param W wektor wczytywany
   \return referencja do strumienia
 */

template <typename COORD,int SIZE>
istream& operator >> (istream &Strm,Vector<COORD,SIZE> &W){
        for(int i=0; i<SIZE; ++i) {
                Strm>>W[i];
        };
        return Strm;
}

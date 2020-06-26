#pragma once

#include <iostream>
#include "Vector2D.hh"
#include "Matrix2x2.hh"

#define ILOSC_WIERZCHOLKOW 4

/*
 *  Klasa modelujacy na plaszczyznie 2D prostokat
 */
class Rectangle {
        Vector2D _Wierz[ILOSC_WIERZCHOLKOW];

public:
        Vector2D operator[] (int Ind) const {
                if(Ind>ILOSC_WIERZCHOLKOW) {cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!"; return _Wierz[0]; };
                return _Wierz[Ind];
        }
        Vector2D& operator[] (int Ind)  {
                if(Ind>ILOSC_WIERZCHOLKOW) {cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!"; return _Wierz[0]; };
                return _Wierz[Ind];
        }
        void Display(std::ostream &Strm) const {
                for(int i=0; i<ILOSC_WIERZCHOLKOW; i++) Strm << _Wierz[i]<<endl;
        }

        /*  Rectangle& operator = (const Rectangle rect) {
                  for(int i=0; i<ILOSC_WIERZCHOLKOW; i++) {
                          this->_Wierz[i]=rect._Wierz[i];
                  }
                  return *this;
           }*/

        /*
         * Funkcja wykonujaca przesuniecie prostokata o zadany wektor (x, y)
         *
         * param_wej: klasa Wektor2D
         * param_wyj: zmienione wspolrzedne wierzcholkow
         */
        void Move(const Vector2D &W_trans);
        /*
         * Funkcja wykonujaca obrot prostokata o zadany kat w stopniach
         *
         * param_wej: Macierz2x2 z danymi do obrotu, kat i w stopniach
         * param_wyj: zmienione wspolrzedne wierzcholkow
         */
        void Turn(Matrix2x2 M, int l_obr);
};


/*
 * Przeciazenie operatora wypisujacego wektor
 *
 * param_wej: standardowy strumien wyjsciowy std::ostream, Prostokat
 * param_wyj: zwracamy strumien
 */
std::ostream& operator << (std::ostream & stream, const Rectangle & rect);
/*!
   \brief Dokonuje obrotu wokol srodka ukladu
   \param_in angle - kat obrotu
   \param_in l_obr - liczba obrotow
   \param_in base - bazowy Prostokat
   \param_out - prostokat po obrocie
   \pre Brak
   \post Brak
   \return Zwraca referencje na zmieniony Prostokat
 */
Rectangle& Rotate(float angle,int l_obr, Rectangle& base);
/*!
   \brief Dokonuje obrotu wokol srodka ciezkosci bryly
   \param_in angle - kat obrotu
   \param_in l_obr - liczba obrotow
   \param_in base - bazowy Prostokat
   \param_out - prostokat po obrocie
   \pre Brak
   \post Brak
   \return Zwraca referencje na zmieniony Prostokat
 */
Rectangle& Rotate_Center(float angle,int l_obr, Rectangle& base);

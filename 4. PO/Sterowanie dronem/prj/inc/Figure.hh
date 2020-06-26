/*!
   \file Figure.hh
   \brief Zawiera klase Figure oraz jej metody. Sluzy do opisania powierzchni równoległej do XZ
   \author Patryk Szydlik
   \date 20.04.19
 */
#pragma once

#include <iostream>
#include "NEW_Vector.hh"
#include "NEW_Matrix.hh"

/*!
 * \brief Klasa tworzy figure 2D o określonych właściwościach
 */
template<int TIPS>
class Figure {
        NEW_Vector _Wierz[TIPS]; /*!< Tablica wierzcholkow podstawy */

public:
        Figure(){
        }
        /*!
           \brief Kreator klasy. Tworzy podstawe o bokach a,b
           \param a pierwszy bok
           \param b drugi bok
         */
        Figure(float a, float b){
                if(TIPS==4) {
                        _Wierz[0][0]=-a/2;
                        _Wierz[0][1]=-b/2;
                        _Wierz[0][2]=0;
                        _Wierz[1][0]=a/2;
                        _Wierz[1][1]=-b/2;
                        _Wierz[1][2]=0;
                        _Wierz[2][0]=a/2;
                        _Wierz[2][1]=b/2;
                        _Wierz[2][2]=0;
                        _Wierz[3][0]=-a/2;
                        _Wierz[3][1]=b/2;
                        _Wierz[3][2]=0;
                };
                if(TIPS==6) {
                        if(b==0.0) {
                                _Wierz[0][0]=a;
                                _Wierz[0][1]=0;
                                _Wierz[0][2]=0;
                                _Wierz[1][0]=a/2;
                                _Wierz[1][1]=a*sqrt(3)/2;
                                _Wierz[1][2]=0;
                                _Wierz[2][0]=-a/2;
                                _Wierz[2][1]=sqrt(3)*a/2;
                                _Wierz[2][2]=0;
                                _Wierz[3][0]=-a;
                                _Wierz[3][1]=0;
                                _Wierz[3][2]=0;
                                _Wierz[4][0]=-a/2;
                                _Wierz[4][1]=-a*sqrt(3)/2;
                                _Wierz[4][2]=0;
                                _Wierz[5][0]=a/2;
                                _Wierz[5][1]=-sqrt(3)*a/2;
                                _Wierz[5][2]=0;
                        };
                };

        }

        virtual ~Figure(){

        }
        /*!
           \brief Pozwala sprawdzic zawartosc danego wierzcholka podstawy
           \param Ind numer wierzcholka
           \return Wektor okreslajacy wierzcholek
         */
        NEW_Vector operator[] (int Ind) const {
                if(Ind>TIPS) {cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!"; };
                return _Wierz[Ind];
        }
        /*!
           \brief Pozwala sprawdzic zawartosc danego wierzcholka podstawy
           \param Ind numer wierzcholka
           \return referencja na wektor okreslajacy wierzcholek
         */
        NEW_Vector& operator[] (int Ind)  {
                if(Ind>TIPS) {cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!"; };
                return _Wierz[Ind];
        }
        /*!
           \brief Wyswietla wierzcholki podstawy
           \param Strm strumien wyjsciowy
         */
        void Display(std::ostream &Strm) const {
                for(int i=0; i<TIPS; i++) Strm<<_Wierz[i]<<endl;
        }
/*!
   \brief Przekazuje wartosc wierzcholkow podstawy
   \param rect - kopiowana podstawa
   \return Podstawe po skopiowaniu
 */
        Figure& operator = (const Figure &rect) {
                for(int i=0; i<TIPS; i++) {
                        this->_Wierz[i]=rect._Wierz[i];
                }
                return *this;
        }

        /*!
           \brief Funkcja wykonujaca przesuniecie prostokata o zadany wektor (x, y,z)
           \param W_trans klasa Wektor2D
           \return zmienione wspolrzedne wierzcholkow
         */

        void Move(const NEW_Vector &W_trans){
                for (NEW_Vector &W_biezacy : _Wierz) W_biezacy+=W_trans;
        }

        /*!
           \brief Funkcja wykonujaca obrot prostokata o zadany kat w stopniach
           \param  M Macierz2x2 z danymi do obrotu, kat i w stopniach
           \return zmienione wspolrzedne wierzcholkow
         */

        void Turn(const NEW_Matrix &M){
                for (int i=0; i<TIPS; ++i)
                        this->_Wierz[i]=M*this->_Wierz[i];
        }
};

/*!
   \brief Przeciazenie operatora wypisujacego wektor
   \param Strm standardowy strumien wyjsciowy std::ostream,
   \param Pr  Prostokat
   \return zwracamy strumien
 */

template<int TIPS>
std::ostream& operator << (std::ostream & Strm, const Figure<TIPS> &Pr){
        Pr.Display(Strm);
        return Strm;
}
/*!
   \brief Dokonuje obrotu wokol srodka ukladu
   \param angle - kat obrotu
   \param base - bazowy Prostokat
   \return Zwraca referencje na zmieniony Prostokat
 */
template<int TIPS>
Figure<TIPS>& Rotate(float angle, char axis, Figure<TIPS>& base){
        NEW_Matrix matr;
        matr.Add(angle,axis);
        base.Turn(matr);
        return base;
}

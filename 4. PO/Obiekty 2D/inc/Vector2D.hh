#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#define OX 0
#define OY 1
#define ROZM 2

using namespace std;


class Vector2D {

        double coordinates[ROZM]; /*!< wspolrzedne wektora */

public:
        Vector2D() {
                for(int i=0; i<ROZM; i++) coordinates[i]=0;
        }
        Vector2D(double x, double y)
        {
                coordinates[OX]=x;
                coordinates[OY]=y;
        };

        ~Vector2D(){
        };

/*!
   \brief Pobieranie wartości współrzędnych wektora
   \param Ind - indeks pobranej zmiennej
   \pre indeks nie wychodzi poza tablice
   \return wartosc zmiennej
 */
        double operator[] (int Ind) const {       /* P wartości */
                if(Ind>ROZM) {cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!"; return 0.0; };
                return this->coordinates[Ind];
        }
        /*!
             \brief Pobieranie wartości współrzędnych wektora
             \param Ind - indeks pobranej zmiennej
             \pre indeks nie wychodzi poza tablice
             \return referencja na wartosc zmiennej
         */
        double& operator[] (int Ind)    {        /* L Wartości */
                if(Ind>ROZM) {
                        cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!";
                };
                return this->coordinates[Ind];
        }
/*!
   \brief wyswietla wektora na ostream
   \param Strm - referencja do strumienia
 */
        void Display(std::ostream &Strm) const {
                Strm << std::setw(16) << std::fixed << std::setprecision(10) << this->coordinates[OX];
                Strm << std::setw(16) << std::fixed << std::setprecision(10) << this->coordinates[OY];
        }
/*!
   \brief dodawanie wektorow
   \param vector M
   \param vector This
   \return zwraca referencją wynik dodawania
 */
        Vector2D & operator += (const Vector2D &W){
                (*this)[OX]=(*this)[OX]+W[OX];
                (*this)[OY]=(*this)[OY]+W[OY];
                return *this;
        }

        /*!
           \brief dodawanie wektorow
           \param vector stały M
           \param vector This
           \return zwraca wynik dodawania
         */
        Vector2D& operator + (const Vector2D &W){
                Vector2D Sum=*this;
                return Sum+=W;
        }
        /*!
           \brief odejmowanie wektorow
           \param vector const M
           \param vector This
           \return zwraca referencją wynik odejmowania
         */
        Vector2D& operator - (const Vector2D &W){
                Vector2D Sum=*this;
                Vector2D Diff(-W[OX],-W[OY]);
                return Sum+=Diff;
        }
        /*!
           \brief mnozenie wektora przez liczbe
           \param multiplier - mnoznik
           \param vector This
           \return zwraca referencją wynik mnozenia
         */
        Vector2D operator * (float multiplier){
                Vector2D Sum=*this;
                Sum[OX]=Sum[OX]*multiplier;
                Sum[OY]=Sum[OY]*multiplier;

                return Sum;
        }

        double operator & (const Vector2D& V2) const; //iloczyn skalarny
        double Lenght () const {
                return sqrt(*this & *this);
        };
};



/*
 * Przeciazenie wczytuje wektor ze strumienia standardowego wejscia std::istream
 */

std::istream& operator >> (std::istream &Strm, Vector2D &W);

/*
 * Przeciazenie wypisuje wektor 2D na standardowym wyjsciu std::ostream
 */
std::ostream& operator << (std::ostream &Strm, const Vector2D &Wek);

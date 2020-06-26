/*!
   \file Prism.hh
   \brief Zawiera klase i funkcje do obslugi bryly
   \author Patryk Szydlik
   \date 20.04.19
 */
#pragma once

#define UP 1 /** Stala wartosc dla gornej powierzchni bryly*/
#define DOWN 0 /** Stala wartosc dla dolnej powierzchni bryly*/

#include "Figure.hh"
/*!
 * \brief Klasa modeluje pojecie graniastoslupa skladajacego sie z dwoch podstaw
 */
template<int TIPS>
class Prism {
protected:
        Figure<TIPS> _Faces[2];/*!< Powierzchnie podstaw bryly */
public:
        Prism(float a, float b, float height){
                Figure<TIPS> base(a,b);
                NEW_Vector offset;
                offset[OZ]=height/2;
                _Faces[DOWN]=base;
                _Faces[UP]=base;
                _Faces[UP].Move(offset);
                _Faces[DOWN].Move(offset* -1);
        }

        virtual ~Prism(){

        }
/*!
   \brief Tworzy nowa bryle o krawedziach a,b,h
   \param a pierwszy bok
   \param b drugi bok
   \param height wysokosc
 */
        void Create(float a, float b, float height){
                Figure<TIPS> base(a,b);
                NEW_Vector offset;
                offset[OZ]=height/2;
                _Faces[DOWN]=base;
                _Faces[UP]=base;
                _Faces[UP].Move(offset);
                _Faces[DOWN].Move(offset* -1);
        }
        /*!
           \brief Pozwala sprawdzic zawartosc danej podstawy bryly
           \param Ind numer pozycji 0 lub 1
           \return powierzchnia bryly
         */
        Figure<TIPS> operator[] (int Ind) const {
                if(Ind>2) {cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!"; };
                return _Faces[Ind];
        }
        /*!
           \brief Pozwala sprawdzic zawartosc danej podstawy bryly
           \param Ind numer pozycji 0 lub 1
           \return referencja do powierzchni bryly
         */
        Figure<TIPS>& operator[] (int Ind)  {
                if(Ind>2) {cerr<<"Bledne indeksowanie! Wyjscie poza pamiec dostepna!"; };
                return _Faces[Ind];
        }
/*!
   \brief Wyswietla wspolrzedne bryly
   \param Strm strumien wyjsciowy
 */
        virtual void Display(std::ostream &Strm) const {
                for(int i=0; i<TIPS; ++i) {
                        Strm<<_Faces[0][i]<<endl<<_Faces[1][i]<<endl;
                };
        };
/*!
   \brief Przekazuje zawartosc bryly
   \param new_prism kopiowana bryla
   \return kopia danej bryly
 */
        Prism<TIPS>& operator =(const Prism<TIPS> &new_prism) {
                for(int i=0; i<2; i++) {
                        (*this)._Faces[i]=new_prism._Faces[i];
                }
                return *this;
        };

        /*!
           \brief Funkcja wykonujaca przesuniecie graniastoslupa o zadany wektor (x,y,z)
           \param W_trans klasa Wektor2D
           \return zmienione wspolrzedne wierzcholkow
         */

        void Move(const NEW_Vector &W_trans){
                for(int i=0; i<2; i++) {
                        _Faces[i].Move(W_trans);
                }
        };

        /*!
           \brief Funkcja wykonujaca obrot graniastoslupa o zadany kat w stopniach
           \param  M Macierz3x3 z danymi do obrotu
           \return zmienione wspolrzedne wierzcholkow
         */

        virtual void Turn(const NEW_Matrix &M){
                for(int i=0; i<2; i++) {
                        _Faces[i].Turn(M);
                }
        };
/*!
   \brief Funkcja sprawdzająca długość krawędzi bryły
   \return BRAK
 */
        virtual void EdgesLenght() const {
                cout<<"Hard to say"<<endl;
        }
}; ///Koniec klasy Prism

/*!
   \brief Wyświetla graniastoslup na stdo
   \param Strm strumien wyjscia
    \param P graniastoslup wyświetlany
   \return referencja do strumienia
 */
template <int TIPS>
ostream& operator << (ostream &Strm,const Prism <TIPS> &P){
        P.Display(Strm);
        return Strm;
}

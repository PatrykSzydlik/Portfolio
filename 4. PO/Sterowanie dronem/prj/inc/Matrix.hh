/*!
   \file Matrix.hh
   \brief Zawiera szablon klasy Macierz
   \author Patryk Szydlik
   \date 04.04.2019
 */

#pragma once

#include "Vector.hh"

#define TRANS 2


/*!
 * \brief Klasa modeluje macierz dowolnych rozmiarow wraz z metodami
 */
template<typename ELEM, int SIZE>
class Matrix {
protected:
        ELEM _Tab[SIZE][SIZE];

public:
        Matrix () {
                for(int i=0; i<SIZE; i++) {
                        for(int j=0; j<SIZE; j++) {
                                if(i==j) {
                                        _Tab[i][j]=1;
                                }else{
                                        _Tab[i][j]=0;
                                };
                        }
                };

        }
        Matrix (float a) {
                for(int i=0; i<SIZE; i++) {
                        for(int j=0; j<SIZE; j++) {
                                if(i==j) {
                                        _Tab[i][j]=a;
                                }else{
                                        _Tab[i][j]=a;
                                };
                        }
                };

        }
        virtual ~Matrix(){

        }
        /*!
           \brief Pozyskuje wartość komórki z macierzy
           \param i numer wiersza
           \param j numer kolumny
           \pre czy nie przekroczono zakresu
           \return wartość elementu
         */
        ELEM operator() (int i, int j) const {

                return _Tab[i][j];
        }
        ELEM& operator() (int i, int j)    {
                return _Tab[i][j];
        }


        /*!
           \brief Wykonuje mnożenie wektora przez macierz
           \param V Wector Vector2D V
           \return Vector2D po obroceniu
         */

        Vector<ELEM,SIZE> operator * (const Vector<ELEM,SIZE> &V) const {
                Vector<ELEM,SIZE> W;
                for(int i=0; i<SIZE; ++i) {
                        for(int j=0; j<SIZE; ++j) {
                                W[i]+=V[j]*(*this)(i,j);
                        };
                };
                return W;
        }

        /*!
           \brief Wykonuje mnożenie dwóch macierzy
           \param M Macierz będąca mnożnikiem
           \return Macierz po dokonaniu mnożenia
         */

        Matrix operator * (const Matrix &M) const {
                Matrix m1(0);
                for(int i=0; i<SIZE; ++i) {
                        for(int j=0; j<SIZE; ++j) {
                                for(int k=0; k<SIZE; ++k) {
                                        m1(i,j)+=(*this)(i,k)*M(k,j);
                                };
                        };
                };
                return m1;
        }

        /*!
           \brief Wykonuje odejmowanie dwóch macierzy
           \param M Macierz będąca odejmowaną
           \return Macierz różnice odejmowania
         */

        Matrix operator - (const Matrix &M) const {
                Matrix result(0);
                for(int i=0; i<SIZE; ++i) {
                        for(int j=0; j<SIZE; ++j) {
                                result(i,j)=(*this)(i,j)-M(i,j);
                        };
                };
                return result;
        }

        /*!
           \brief Wykonuje dodawanie dwóch macierzy
           \param M Macierz będąca dodawaną
           \return Macierz suma dodawania
         */

        Matrix operator + (const Matrix &M) const {
                Matrix sum;
                for(int i=0; i<SIZE; ++i) {
                        for(int j=0; j<SIZE; ++j) {
                                sum(i,j)=(*this)(i,j)+M(i,j);
                        };
                };
                return sum;
        }

/*!
   \brief Wyswietla zawartosc macierzy
 */
        void Display() const {
                for(int i=0; i<SIZE; i++) {
                        for(int j=0; j<SIZE; j++) {
                                cout<<(*this)(i,j)<<" ";
                        }
                        cout<<endl;
                };

        }
        /*!
           \brief Wykonuje podstawienie wartości macierzy do innej
           \param M Macierz będąca kopiowaną
           \return Macierz po dokonaniu mnożenia
         */

        Matrix& operator = (const Matrix &M) {
                for(int i=0; i<SIZE; ++i) {
                        for(int j=0; j<SIZE; ++j) {
                                (*this)(i,j)=M(i,j);
                        };
                };
                return *this;
        }



        /*!
           \brief Oblicza wyznacznik frobeniusa
           \return wartość wyznacznika
         */

        float Frobenius() const {
                float sum=0;
                for(int i=0; i<SIZE; i++) {
                        for(int j=0; j<SIZE; j++) {
                                sum+=((*this)(i,j))*((*this)(i,j));
                        };
                };
                return sqrt(sum);
        }


}; //koniec klasy matrix

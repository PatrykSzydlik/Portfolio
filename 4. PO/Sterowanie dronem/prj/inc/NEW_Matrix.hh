/*!
   \file NEW_Matrix.hh
   \brief Definiuje macierz 3x3 na podstawie wzorca
   \author Patryk Szydlik
   \date 03.05.2019
 */
#pragma once

#include "Matrix.hh"

/*!
 * \brief Klasa jest zdefiniowaną klasą macierzy 3x3 do obrotow trojwymiarowych
 */
class NEW_Matrix : public Matrix<float,3> {
        static int Amount_of_matrix; /*!< Zmienna ilosc istniejacych macierzy */

public:

        NEW_Matrix () {
                for(int i=0; i<3; i++) {
                        for(int j=0; j<3; j++) {
                                if(i==j) {
                                        _Tab[i][j]=1;
                                }else{
                                        _Tab[i][j]=0;
                                };
                        }
                };

        }

        NEW_Matrix (Matrix<float,3> M) {
                for(int i=0; i<3; i++) {
                        for(int j=0; j<3; j++) {
                                _Tab[i][j]=M(i,j);
                        };
                };

        }

        NEW_Matrix (float a) {
                for(int i=0; i<3; ++i) {
                        for(int j=0; j<3; ++j) {
                                if(i==j) {
                                        _Tab[i][j]=a;
                                }else{
                                        _Tab[i][j]=a;
                                };
                        }
                };

        }

        virtual ~NEW_Matrix(){

        }

        /*!
           \brief Wstawia do macierzy wartosci zalezne od kata obrotu i osi
           \param angle kąt obrotu
           \param axis oś obrotu
           \return wartość 1 gdy pomyślnie dodano wartości lub 0
         */

        bool Add (double angle, char axis){
                int w,k,c;
                w=k=0;
                c=1;
                switch(axis) {
                case 'x':
                        w=1;
                        k=1;
                        break;
                case 'y':
                        k=2;
                        c=-1;
                        break;
                case 'z':
                        k=1;
                        break;
                default: return 0;

                };
                for(int i=0; i<3; ++i) {for(int j=0; j<3; ++j) {if(i==j) {(*this)(i,j)=1; }else{(*this)(i,j)=0; }; }; };
                (*this)(w,w) = cos(angle*M_PI/180);
                (*this)(w,w+k) = -c*sin(angle*M_PI/180);
                (*this)(w+k,w) = c*sin(angle*M_PI/180);
                (*this)(w+k,w+k) = cos(angle*M_PI/180);
                return 1;
        }
        /*
           \brief Zlicza ilosc aktualnych macierzy
           \return Ilość istniejących macierzy
         */
        static int Read_amount() {
                return Amount_of_matrix;
        };

        float det() const {
                float result=0;

                result = (*this)(0,0)*(*this)(1,1)*(*this)(2,2);
                result += (*this)(0,1)*(*this)(1,2)*(*this)(2,0);
                result += (*this)(0,2)*(*this)(1,0)*(*this)(2,1);
                result -= (*this)(0,2)*(*this)(1,1)*(*this)(2,0);
                result -= (*this)(0,0)*(*this)(1,2)*(*this)(2,1);
                result -= (*this)(0,1)*(*this)(1,0)*(*this)(2,2);

                return result;
        }

        float det_D(int i, int j) const {
                int wn,kn;
                float result=0;
                Matrix<float,2> matrix_d;
                wn=kn=0;
                for(int w=0; w<3; ++w) {
                        if(w!=i) {

                                kn=0;
                                for(int k=0; k<3; ++k) {
                                        if(k==j) {
                                                ++k;
                                        };
                                        if(k<3&&w<3) {
                                                matrix_d(wn,kn)=(*this)(w,k);
                                                ++kn;
                                        };
                                };
                                ++wn;
                        };
                };
                result=matrix_d(0,0)*matrix_d(1,1)-matrix_d(0,1)*matrix_d(1,0);
                return result;
        }

        NEW_Matrix find_reverse() const {
                NEW_Matrix result=(*this);
                float det_m;
                if((*this).det()!=0) {
                        det_m=1/(*this).det();
                        for(int w=0; w<3; ++w) {
                                for(int k=0; k<3; ++k) {
                                        result(k,w)=(*this).det_D(w,k)*det_m*pow(-1,k+w);
                                };
                        };
                }else{
                        cout<<" Nie istnieje macierz odwrotna"<<endl;
                };
                return result;
        }



}; //koniec klasy NEW_Matrix

#pragma once

#include <iostream>
#include "Vector2D.hh"
#define ROZM 2

/*
 * Klasa modeluje macierz rozmiarow 2x2, przechowujaca wspolczynniki do przeksztalcen 2D
 */
class Matrix2x2 {
        double _Tab[ROZM][ROZM];

public:
        Matrix2x2 () {
                for(int i=0; i<ROZM; i++) {for(int j=0; j<ROZM; j++) {_Tab[i][j]=0; }}
        }

        /* Ponizej funkcje pozyskujace wartosci z macierzy */

        double operator() (int i, int j) const {

                return _Tab[i][j];
        }
        double& operator() (int i, int j)    {
                return _Tab[i][j];
        }

/*
 *  Wykonuje mnożenie wektora przez macierz
 *   par_wej - Macierz This oraz Vectow vector V
 *   par_wyj - Vector po obroceniu
 */

        Vector2D operator * (const Vector2D &V) const {
                Vector2D W;
                W[0]=V[0]*(*this)(0,0)+V[1]*(*this)(0,1);
                W[1]=V[0]*(*this)(1,0)+V[1]*(*this)(1,1);
                return W;
        }

/*
 *  Wstawia do macierzy wartosci zalezne od kata obrotu
 *   par_wej - kąt obrotu angle
 *   par_wyj - macierz M do ktorej wpisujemy wsp
 */
        void Add (double angle, Matrix2x2 &M);

        float Frobenius() const {
                float sum=0;
                for(int i=0; i<ROZM; i++) {
                        for(int j=0; j<ROZM; j++) {
                                sum+=((*this)(i,j))*((*this)(i,j));
                        };
                };
                return sqrt(sum);
        };
};

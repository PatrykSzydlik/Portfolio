#include "Matrix2x2.hh"
#include <cmath>


/*
 *  Tutaj nalezy zdefiniowac odpowiednie metody
 *  klasy Matrix2x2, ktore zawieraja wiecej kodu
 *  niz dwie linijki.
 *  Mniejsze metody mozna definiwac w ciele klasy.
 */

using namespace std;

/*
 * Funkcja ustawiajaca wspolczynniki macierzy
 *
 * param_wej: pobierany zadany kat obrotu
 * param_wyj: podstawienie do macierzy obrotow odpowiednich wartosci
 */

void Matrix2x2::Add (double angle, Matrix2x2 &M){
        M(0,0) = cos(angle*M_PI/180);
        M(0,1) = -sin(angle*M_PI/180);
        M(1,0) = sin(angle*M_PI/180);
        M(1,1) = cos(angle*M_PI/180);
}

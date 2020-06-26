#include "Vector2D.hh"


/*
 *  Tutaj nalezy zdefiniowac odpowiednie metody
 *  klasy Vector2D, ktore zawieraja wiecej kodu
 *  niz dwie linijki.
 *  Mniejsze metody mozna definiwac w ciele klasy.
 */


/*
 * Przeciazenie operatora wypisujacego wektor
 *
 * param_wej: standardowy strumien wyjsciowy std::ostream, Wektor2D
 * param_wyj: zwracamy strumien
 */
ostream& operator << (ostream &Strm, const Vector2D &W){
        W.Display(Strm);
        return Strm;
}

/*
 * Przeciazenie operatora wczytujacego wektor
 *
 * param_wej: standardowy strumien wejsciowy std::istream, Wektor2D
 * param_wyj: wpisany Wektor2D
 */
istream& operator >> (istream &Strm, Vector2D &W){
        for(int i=0; i<ROZM; i++) {
                Strm >> W[i];
                if(Strm.fail())
                        return Strm;
        }
        return Strm;
}
/*!
   \brief Oblicza iloczyn skalarny wektorow
   \param this - wektor pierwszy
   \param V2 - wektor drugi
   \return Zwraca wartosc iloczynu
 */

double Vector2D::operator & (const Vector2D &V2) const {
        double result=0;
        for(int Ind=0; Ind<ROZM; Ind++)
                result += (*this)[Ind]*V2[Ind];
        return result;
}

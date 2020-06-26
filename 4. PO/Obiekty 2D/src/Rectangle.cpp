#include "Rectangle.hh"


using namespace std;

/*
 * Przeciazenie operatora wypisujacego wektor
 *
 * param_wej: standardowy strumien wyjsciowy std::ostream, Prostokat
 * param_wyj: zwracamy strumien
 */
ostream& operator << (ostream &Strm, const Rectangle &Pr){
        Pr.Display(Strm);
        return Strm;
}

/*
 * Funkcja wykonujaca przesuniecie prostokata o zadany wektor (x, y)
 *
 * param_wej: klasa Wektor2D
 * param_wyj: zmienione wspolrzedne wierzcholkow
 */
void Rectangle::Move(const Vector2D &W_trans){
        for (Vector2D &W_biezacy : _Wierz) W_biezacy+=W_trans;
}

/*
 * Funkcja wykonujaca obrot prostokata o zadany kat w stopniach
 *
 * param_wej: Macierz2x2 z danymi do obrotu, kat i w stopniach
 * param_wyj: zmienione wspolrzedne wierzcholkow
 */
void Rectangle::Turn(Matrix2x2 M, int l_obr){
        for (int j=0; j<l_obr; ++j) {
                for (int i=0; i<ILOSC_WIERZCHOLKOW; ++i)
                        this->_Wierz[i]=M*this->_Wierz[i];
        }
}


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
Rectangle& Rotate(float angle,int l_obr, Rectangle& base){
        Matrix2x2 matr;
        matr.Add(angle,matr);
        base.Turn(matr,l_obr);
        return base;
}
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
Rectangle& Rotate_Center(float angle,int l_obr, Rectangle& base){
        Matrix2x2 matr;
        Vector2D center_point;

        for(int i=0; i<ILOSC_WIERZCHOLKOW; i++) {
                center_point+=base[i];
        };
        center_point=center_point* -(1/ILOSC_WIERZCHOLKOW);

        base.Move(center_point);
        matr.Add(angle,matr);
        base.Turn(matr,l_obr);
        center_point=center_point* -1;
        base.Move(center_point);

        return base;
}

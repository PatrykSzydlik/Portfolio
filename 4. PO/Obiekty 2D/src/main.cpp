#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>


#include "Vector2D.hh"
#include "Matrix2x2.hh"
#include "Rectangle.hh"
#include "gnuplot_link.hh"

#define DIFF 0.1   /** Ile procent dlugosci prostokata nie moze przekroczyc blad*/
#define FPS 60

using namespace std;


/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] output_stream - strumien wyjsciowy, do ktorego maja zostac
 *                            zapisane kolejne wspolrzedne.
 * \param[in] offset - ten parameter jest tylko po to, aby pokazać
 *                     mozliwosc zmiany wspolrzednych i prostokata
 *                     i zmiane jego polorzenia na okienku graficznym
 *                     rysownym przez gnuplota.
 * \param[in] rect    - prostokat z wierzcholkami do wyswietlenia
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void WriteToStream(ostream& output_stream,Rectangle rect, Vector2D offset)
{
        rect.Move(offset);
        for(int i=0; i<ILOSC_WIERZCHOLKOW; i++) {

                output_stream << rect[i]<<endl;
        };

        output_stream << rect[0]<<endl;
}



/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] filename - nazwa pliku, do którego zostana zapisane
 *                       wspolrzędne punktów.
 * \param[in] offset - ten parameter jest tylko po to, aby pokazać
 *                     mozliwosc zmiany wspolrzednych i prostokata
 *                     i zmiane jego polorzenia na okienku graficznym
 *                     rysownym przez gnuplota.
 * \param[in] rect    - prostokat z wierzcholkami do wyswietlenia
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool WriteToFile(string filename,Rectangle rect, Vector2D offset )
{
        ofstream file_stream;

        file_stream.open(filename);
        if (!file_stream.is_open())  {
                cerr << ":(  Operacja otwarcia do zapisu \"" << filename << "\"" << endl
                     << ":(  nie powiodla sie." << endl;
                return false;
        }

        WriteToStream(file_stream,rect,offset);

        file_stream.close();
        return !file_stream.fail();
}



int main()
{
        Rectangle rect;         // To tylko przykladowe definicje zmiennej
        PzG::GnuplotLink link;       // Ta zmienna jest potrzebna do wizualizacji
                                     // rysunku prostokata
        Vector2D W_trans, offset; /*!< Wektor translacji oraz offset */
        Matrix2x2 matrix; /*!< macierz obrotu */
        double angle; /*!< kat obrotu */
        int l_obr;/*!< liczba obrotow */
        char menu='m';/*!< zmienna znakowa do obslugi menu */
        char sign; /*!< zmienna znakowa do wczytania znakow ignorowanych */



        cout<<" r - nadanie nowych wspolrzednych prostokata"<<endl;
        cout<<" o - obrot prostokata o zadany kat"<<endl;
        cout<<" p - przesuniecie prostokata o zadany wektor"<<endl;
        cout<<" w - wyswietlenie wspolrzednych wierzcholkow"<<endl;
        cout<<" s - sprawdzenie dlugosci przeciwleglych bokow"<<endl;
        cout<<" m - wyswietl menu"<<endl;
        cout<<" a - animacja translacji figury"<<endl;
        cout<<" d - obrot wokol srodka ciezkosci"<<endl;
        cout<<" k - koniec dzialania programu"<<endl;
        cout<<" f - new feature - Frobenius"<<endl;

        while(menu!='k') {

                cout << "Twoj wybor? (m - menu) > ";
                cin >> menu;

                switch (menu) {


                case 'f':
                {
                        Matrix2x2 Frob;
                        cout<<"Podaj elementy macierzy:"<<endl;
                        for(int i=0; i<ROZM; i++) {
                                for(int j=0; j<ROZM; j++) {
                                        cout<<i+j+1<<". ";
                                        cin>>Frob(i,j);
                                        cout<<endl;
                                };
                        };
                        cout<<"Norma Frobiusa tej macierzy wynosi : "<<Frob.Frobenius()<<endl;
                }
                break;
                case 'a':
                        float seconds;
                        link.AddFilename("rectangle.dat",PzG::LS_CONTINUOUS,2);
                        do {
                                if(cin.fail()||seconds>10||seconds<0) {
                                        cin.clear();
                                        cin.ignore(1000,'\n');
                                        cout<<endl<<"Bledne wartosci! Sprobuj jeszcze raz!"<<endl;
                                };
                                cout<<"Podaj kat obrotu w stopniach:"<<endl;
                                cin >> angle;
                                cout<<endl<<"Ile obrotow wykonac?"<<endl;
                                cin >> l_obr;
                                cout<<endl<<"Podaj wektor przesuniecia:"<<endl;
                                cin >> W_trans;
                                cout<<endl<<"Podaj czas animacji z przedzialu 1-10 (s)"<<endl;
                                cin>>seconds;
                        } while(cin.fail()||seconds>10||seconds<0);
                        W_trans=W_trans*(1/(seconds*FPS));
                        angle=angle*l_obr;
                        //cout<<angle<<endl;
                        angle=angle*(1/(seconds*FPS));
                        //cout<<angle<<endl;
                        WriteToFile("rectangle.dat", rect, offset);
                        link.Draw();
                        usleep(1000000);
                        {
                                float new_angle;
                                Vector2D new_vec;
                                Rectangle copy;
                                for(int i=1; i<=seconds*FPS; i++) {
                                        {
                                                copy=rect;
                                                new_angle=angle*i;
                                                //cout<<new_angle<<endl;
                                                new_vec=W_trans*i;
                                                usleep(1000000/FPS);
                                                copy.Move(new_vec);
                                                Rotate(new_angle,1,copy);
                                                WriteToFile("rectangle.dat", copy, offset);
                                                link.Draw();
                                        }
                                };
                                rect=copy;
                                cout<<rect<<endl;
                        }
                        break;
                case 'r':
                        double a,b;
                        cout<<"Podaj dlugosc krotszego boku:"<<endl;
                        cin >> a;
                        cout<<"Podaj dlugosc dluzszego boku:"<<endl;
                        cin >> b;
                        rect[0][OX]=0;
                        rect[0][OY]=0;
                        rect[1][OX]=0+b;
                        rect[1][OY]=0;
                        rect[2][OX]=0+b;
                        rect[2][OY]=0+a;
                        rect[3][OX]=0;
                        rect[3][OY]=0+a;
                        break;

                case 'o': cout<<"Podaj kat obrotu w stopniach:"<<endl;
                        cin >> angle;
                        cout<<"Ile obrotow wykonac?"<<endl;
                        cin >> l_obr;
                        Rotate(angle, l_obr, rect);
                        break;

                case 'p': cout<<"Podaj wektor przesuniecia:"<<endl;
                        cin >> W_trans;
                        rect.Move(W_trans);
                        break;

                case 'w':

                        cout << rect << endl;
                        link.AddFilename("rectangle.dat",PzG::LS_CONTINUOUS,2); //rysowanie linia o grubosci 2
                        link.SetDrawingMode(PzG::DM_2D); //ustawienie trybu rysowania 2D
                        if (!WriteToFile("rectangle.dat", rect, offset))
                                return 1;
                        link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
                        cout << "Wprowadz znak i naciśnij ENTER, aby kontynuowac" << endl;
                        cin >> sign;

                        break;

                case 's':
                        double a1,a2,b1,b2;
                        {
                                Vector2D _tab[ILOSC_WIERZCHOLKOW];
                                for(int i=0; i<ILOSC_WIERZCHOLKOW; i++)
                                        if(i!=3) {
                                                _tab[i]=rect[i]-rect[i+1];
                                        }else if(i==3) {
                                                _tab[i]=rect[i]-rect[0];
                                        };
                                a1=_tab[0].Lenght();
                                a2=_tab[2].Lenght();
                                b1=_tab[1].Lenght();
                                b2=_tab[3].Lenght();
                                cout<< a1<<endl<< a2 <<endl<<b1<<endl<<b2<<endl;
                                if (a1<b1) {
                                        cout<<"Krotsze boki ";
                                        if((a1-a2)<-DIFF*a1 || (a1-a2)>DIFF*a1) cout<<"nie ";
                                        cout<<"sa rowne"<<endl;
                                        cout<<"Dluzsze boki ";
                                        if((b1-b2)<-DIFF*b1 || (b1-b2)>DIFF*b1) cout<<"nie ";
                                        cout<<"sa rowne"<<endl;
                                }
                                else{
                                        cout<<"Krotsze boki ";
                                        if((b1-b2)<-DIFF*b1 || (b1-b2)>DIFF*b1) cout<<"nie ";
                                        cout<<"sa rowne"<<endl;
                                        cout<<"Dluzsze boki ";
                                        if((a1-a2)<-DIFF*a1 || (a1-a2)>DIFF*a1) cout<<"nie ";
                                        cout<<"sa rowne"<<endl;
                                }
                        }
                        break;

                case 'm': cout<<" r - nadanie nowych wspolrzednych prostokata"<<endl;
                        cout<<" o - obrot prostokata o zadany kat"<<endl;
                        cout<<" p - przesuniecie prostokata o zadany wektor"<<endl;
                        cout<<" w - wyswietlenie wspolrzednych wierzcholkow"<<endl;
                        cout<<" s - sprawdzenie dlugosci przeciwleglych bokow"<<endl;
                        cout<<" d - obrot wokol srodka ciezkosci"<<endl;
                        cout<<" m - wyswietl menu"<<endl;
                        cout<<" a - animacja translacji figury"<<endl;
                        cout<<" k - koniec dzialania programu"<<endl<<endl;
                        break;

                case 'd':
                        cout<<"Podaj kat obrotu w stopniach:"<<endl;
                        cin >> angle;
                        cout<<"Ile obrotow wykonac?"<<endl;
                        cin >> l_obr;
                        Rotate_Center(angle, l_obr, rect);
                        break;

                case 'k': cout<<endl<<"KONIEC"<<endl<<endl;
                        return 0;
                        break;

                default:  cout<<"Nie ma takiej opcji!"<<endl<<endl;
                        menu='m';
                        break;
                } //koniec switch
        }         //koniec while
        return 0;

}

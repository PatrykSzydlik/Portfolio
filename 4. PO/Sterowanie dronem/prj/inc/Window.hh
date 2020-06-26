/*!
   \file Window.hh
   \brief Zawiera klase i metody obslugujace przeszkode
   \author Patryk Szydlik
   \date 19.05.19
 */

#pragma once
#define SZER 10

#include "Object3D.hh"
#include "Obstacle.hh"

/*!
 * \brief Klasa tworzy model przeszkody okna wraz z metodami
 */

class Window : public Object3D {
        Obstacle Wall1; /*!< sciana pionowa */
        Obstacle Wall2;/*!< sciana pozioma */
        Obstacle Wall3; /*!< sciana pionowa */
        Obstacle Wall4; /*!< sciana pozioma */
        float remember_size[2]; /*!< zapamietany rozmiar */
        static int Amount_of_windows; /*!< Ilośc aktualnie istniejacych kadłubów */
        static int Created_windows; /*!< ilosc stworzonych */
private:
        friend class Fabric;

        Window(int d, int kier,char new_name[20]) : Wall1(SZER,SZER,(d/sqrt(2)+SZER)),Wall2(d/sqrt(2),SZER,SZER),Wall3(SZER,SZER,(d/sqrt(2)+SZER)),Wall4(d/sqrt(2),SZER,SZER) {
                NEW_Vector trans;
                NEW_Matrix rotate_now;
                remember_size[0]=d;
                remember_size[1]=kier;
                rotate_now.Add(0,'z');
                if(kier==2) {
                        rotate_now.Add(90,'z');
                }else if(kier==3) {
                        rotate_now.Add(90,'x');
                }

                trans.change((-d/(2*sqrt(2)))-SZER/2,0,0);
                if(kier==2) {
                        trans.change(0,-d/sqrt(2)/2,0);
                };
                Wall1.Move(trans );

                trans.change(0,0,-d/sqrt(2)/2);
                if(kier==3) {
                        trans.change(0,-d/sqrt(2)/2,0);
                };
                Wall2.Move(trans );


                trans.change((d/(2*sqrt(2)))+SZER/2,0,0);
                if(kier==2) {
                        trans.change(0,d/sqrt(2)/2,0);
                };
                Wall3.Move(trans );

                trans.change(0,0,d/sqrt(2)/2);
                if(kier==3) {
                        trans.change(0,d/sqrt(2)/2,0);
                };

                Wall4.Move(trans);


                _ID=1000+Created_windows;
                for(int i=0; i<20; ++i) {_name[i]=new_name[i]; };
                Turn(rotate_now);
                ++Amount_of_windows;
                ++Created_windows;
        }
public:
// okno pionowo w strone x to 1
//okno pionowo w strone y to 2
//okno poziomo to 3

//domyslnie jest pionowo w kierunku x


        Window(const Window& obs) : Wall1(obs.Wall1),Wall2(obs.Wall2),Wall3(obs.Wall3),Wall4(obs.Wall4){
                position=obs.position;
                rotation[0]=obs.rotation[0];
                rotation[1]=obs.rotation[1];
                ++Amount_of_windows;
                ++Created_windows;

        }




        virtual ~Window(){
                --Amount_of_windows;
        }


        /*!
           \brief Wyswietla wspolrzedne okna
           \param Strm strumien wyjsciowy
         */


        virtual void Display(std::ostream &Strm) {

                Obstacle result(Wall1);
                Obstacle result2(Wall2);
                Obstacle result3(Wall3);
                Obstacle result4(Wall4);


                result.Turn(rotation[1]);
                result.Move(position);
                result.Display(Strm);


                result2.Turn(rotation[1]);
                result2.Move(position);
                result2.Display(Strm);


                result3.Turn(rotation[1]);
                result3.Move(position);
                result3.Display(Strm);


                result4.Turn(rotation[1]);
                result4.Move(position);
                result4.Display(Strm);

                //cout<<"Displayed window "<<_name<<endl;
        }

        float Read_orientation(){
                return remember_size[1];
        }
        /*!
           \brief Wyswietla wspolrzedne wierzcholkow obiektu
           \param Strm strumien wyjsciowy do zapisu
           \return Brak
         */
        virtual void Show_Size(std::ostream &Strm) const {
                Strm<<"   Windows diagonal    : "<<std::setw(5)<<remember_size[0]<<endl;
                Strm<<"   Window direction    : ";
                if(remember_size[1]==1) {cout<<"|| XZ "<<endl; };

                if(remember_size[1]==2) {cout<<"|| YZ "<<endl; };

                if(remember_size[1]==3) {cout<<"|| XY "<<endl; };
        };

/*!
   \brief Zlicza ilosc aktualnych wektorow
   \return Ilość istniejących wektorów
 */
        static int Read_amount() {
                return Amount_of_windows;
        };
/*!
   \brief Zlicza ilosc stworzonych dotychczas wektorow
   \return Ilość wektorów stworzonych od uruchomienia programu
 */
        static int Read_sum() {
                return Created_windows;
        };

/*!
   \brief Zwraca promien obiektu
   \return Wartosc promienia
 */

        virtual float Your_Size() const {
                float radius;
                radius=(remember_size[0]/2)+SZER;
                return radius;
        }

/*!
   \brief Sprawdza kolizje naszego okna z dronem ktory wyslal zapytanie
   \param Your_pos pozycja drona
   \param Your_move przemieszczenie drona
   \param radius promien drona
   \param height wysokosc drona
   \return true jesli doszlo do kolizji
 */
        virtual bool Is_This_Sit_Taken(const NEW_Vector &Your_pos,const NEW_Vector Your_move, float radius, float height) {
                NEW_Vector updated_pos;
                cout<<"halo halo"<<endl;
                updated_pos=Your_pos-position;
                Wall1.Turn(rotation[1]);
                Wall2.Turn(rotation[1]);
                Wall3.Turn(rotation[1]);
                Wall4.Turn(rotation[1]);
                cout<<"halo halo"<<endl;
                if(Wall1.Is_This_Sit_Taken(updated_pos,Your_move,radius,height)==1) {Wall1.Turn_undo(); return 1; };
                if(Wall2.Is_This_Sit_Taken(updated_pos,Your_move,radius,height)==1) {Wall2.Turn_undo(); return 1; };
                if(Wall3.Is_This_Sit_Taken(updated_pos,Your_move,radius,height)==1) {Wall3.Turn_undo(); return 1; };
                if(Wall4.Is_This_Sit_Taken(updated_pos,Your_move,radius,height)==1) {Wall4.Turn_undo(); return 1; };
                Wall1.Turn_undo();
                Wall2.Turn_undo();
                Wall3.Turn_undo();
                Wall4.Turn_undo();

                return 0;
        }

};

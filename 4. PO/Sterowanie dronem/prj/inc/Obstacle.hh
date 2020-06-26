/*!
   \file Obstacle.hh
   \brief Zawiera klase i metody obslugujace przeszkode
   \author Patryk Szydlik
   \date 19.05.19
 */

#pragma once

#include "Object3D.hh"
#include "Cuboid.hh"

/*!
 * \brief Klasa tworzy model kadłuba dla klasy dron
 */
class Obstacle : public Object3D {
        Cuboid Object; /*!< obiekt */
        float remember_size[3]; /*!< zapamietane wymiary */
        static int Amount_of_obstacles; /*!< Ilośc aktualnie istniejacych kadłubów */
        static int Created_obstacles; /*!< stworzone przeszkody */

private:
        friend class Fabric;
        friend class Window;

        Obstacle(float a, float b, float h, char new_name[20]) : Object(a,b,h) {
                _ID=Created_obstacles;
                remember_size[0]=a;
                remember_size[1]=b;
                remember_size[2]=h;
                for(int i=0; i<20; ++i) {_name[i]=new_name[i]; };
                ++Amount_of_obstacles;
                ++Created_obstacles;
        }

        Obstacle(float a, float b, float h) : Object(a,b,h) {
                _ID=Created_obstacles;
                char new_name[20]="Default\n";
                remember_size[0]=a;
                remember_size[1]=b;
                remember_size[2]=h;
                for(int i=0; i<20; ++i) {_name[i]=new_name[i]; };
                ++Amount_of_obstacles;
                ++Created_obstacles;
        }


public:


        Obstacle(const Obstacle& obs) : Object(obs.Object){
                char new_name[20]="Default\n";
                for(int i=0; i<20; ++i) {_name[i]=new_name[i]; };
                ++Amount_of_obstacles;
                ++Created_obstacles;
                position=obs.position;
                rotation[0]=obs.rotation[0];
                rotation[1]=obs.rotation[1];
                for(int i=0; i<3; ++i) {
                        remember_size[i]=obs.remember_size[i];
                };
        }


        virtual ~Obstacle(){
                --Amount_of_obstacles;
        }

/*!
   \brief Wywoluje sprawdzenie dlugosci krawedzi obstacle
   \return Brak
 */
        void EdgesLenght(){
                Object.EdgesLenght();
        }

        /*!
           \brief Wyswietla wspolrzedne obstacle
           \param Strm strumien wyjsciowy
         */


        virtual void Display(std::ostream &Strm) {
                Cuboid result(Object);
                result.Turn(rotation[1]);
                result.Move(position);
                result.Display(Strm);
                //  cout<<"Displayed obstacle "<<_name<<endl;
                //  result.Display(cout);
        }
        /*!
         * \brief Funkcja zapisuje wspolrzedne punktow bryly do pliku
         * \param[in] filename - nazwa pliku, do zapisu wspolrzednych
         * \retval true - gdy operacja zapisu powiodła się,
         * \retval false - w przypadku przeciwnym.
         */
        virtual bool WriteToFile(string filename){
                ofstream file_stream;

                file_stream.open(filename);
                if (!file_stream.is_open())  {
                        cerr << ":(  Operacja otwarcia do zapisu \"" << filename << "\"" << endl
                             << ":(  nie powiodla sie." << endl;
                        return false;
                }

                this->Display(file_stream);

                file_stream.close();
                return !file_stream.fail();
        }

        /*!
           \brief Wyswietla wspolrzedne wierzcholkow obiektu
           \param Strm strumien wyjsciowy do zapisu
           \return Brak
         */
        virtual void Show_Size(std::ostream &Strm) const {
                Strm<<"   Obstacle width    : "<<std::setw(5)<<remember_size[0]<<endl;
                Strm<<"   Obstacle lenght   : "<<std::setw(5)<<remember_size[1]<<endl;
                Strm<<"   Obstacle height   : "<<std::setw(5)<<remember_size[2]<<endl;
        }

        /*!
           \brief Zlicza ilosc aktualnych przeszkod
           \return Ilość istniejących przeszkod
         */
        static int Read_amount() {
                return Amount_of_obstacles;
        };
        /*!
           \brief Zlicza ilosc stworzonych dotychczas przeszkod
           \return Ilość przeszkod stworzonych od uruchomienia programu
         */
        static int Read_sum() {
                return Created_obstacles;
        };

        /*!
           \brief Zwraca promien obiektu
           \return Wartosc promienia
         */
        virtual float Your_Size() const {
                float radius;
                //cout<<"no tutaj licze przeciez"<<endl;
                radius = sqrt((remember_size[0]*remember_size[0]/4)+(remember_size[1]*remember_size[1]/4)+(remember_size[2]*remember_size[2]/4));
                //cout<<"policzylem "<<radius<<endl;
                return radius;
        }

        /*!
           \brief Sprawdza kolizje naszej przeszkody z dronem ktory wyslal zapytanie
           \param Your_pos pozycja drona
           \param Your_move przemieszczenie drona
           \param radius promien drona
           \param height wysokosc drona
           \return true jesli doszlo do kolizji
         */

        virtual bool Is_This_Sit_Taken(const NEW_Vector &Your_pos,const NEW_Vector Your_move, float radius, float height) {
                //Etap 1 Przejscia do układu lokalnego wspolrzednych
                float local_dist[3];           /*!< Zmienna przechowujaca odleglosci od osi lokalnych bryly */
                NEW_Vector local_pos;           /*!< Pozycja drona w układzie lokalnym */
                NEW_Matrix rot_reverse;
                NEW_Vector local_radius_up(radius,radius,height);
                NEW_Vector local_radius_down(radius,radius,-height);


                rot_reverse=(*this).give_rotation().find_reverse();
                local_pos =(Your_pos + Your_move-position);
                local_pos= rot_reverse * local_pos;
                local_radius_up=rot_reverse*local_radius_up;
                local_radius_down=rot_reverse*local_radius_down;

                for(int i=0; i<3; ++i) {
                        if(local_radius_down[i]<0) {
                                local_radius_down[i]*=-1;

                        };
                        if(local_pos[i]<0) {
                                local_pos[i]*=-1;
                        };
                        if(local_radius_up[i]<0) {
                                local_radius_up[i]*=-1;
                        };
                };

                for(int i=0; i<3; ++i) {
                        if(local_radius_up[i]>local_radius_down[i]) {
                                local_dist[i]=local_radius_up[i];
                        }else{
                                local_dist[i]=local_radius_down[i];
                        };
                };

                //Etap 2 Odleglosci od układu lokalnego bryły
                cout<<"In is.this.sit.taken before check"<<endl;
                if(local_pos[0]<=remember_size[0]/2+local_dist[0]) {
                        if(local_pos[1]<=remember_size[1]/2+local_dist[1]) {
                                if(local_pos[2]<=remember_size[2]/2+local_dist[2]) {
                                        cout<<" Odleglosc X "<<local_pos[OX]<<endl;
                                        cout<<" Wymiar przeszkody X "<<remember_size[OX]/2<<endl;
                                        cout<<" Wymiar X obszaru drona "<<local_dist[OX]<<endl;
                                        cout<<" Odleglosc Y "<<local_pos[OY]<<endl;
                                        cout<<" Wymiar przeszkody Y "<<remember_size[OY]/2<<endl;
                                        cout<<" Wymiar Y obszaru drona "<<local_dist[OY]<<endl;
                                        cout<<" Odleglosc Z "<<local_pos[OZ]<<endl;
                                        cout<<" Wymiar przeszkody Z "<<remember_size[OZ]/2<<endl;
                                        cout<<" Wymiar Z obszaru drona "<<local_dist[OZ]<<endl;
                                        cout<<"In is.this.sit.taken when return 1"<<endl;
                                        return 1;
                                };
                        };
                };


                return 0;
        }
};

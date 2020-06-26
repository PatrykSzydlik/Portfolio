/*!
   \file Drone.hh
   \brief Zawiera klase i metody obslugujace drona
   \author Patryk Szydlik
   \date 20.04.19
 */

#pragma once

#include "Body.hh"
#include "Rotor.hh"

/*!
 * \brief Klasa tworzy Dron wraz z metodami pozwalajacymi sterowanie nim
 */
class Drone : public Object3D {
        Body body; /*!< Kadłub */
        Rotor *rotors[4]; /*!< Rotory */
        NEW_Vector movement; /*!< Wektor kierunku ruchu */
        float speed; /*!< prędkość ruchu */
        float rising_angle; /*!< kąt wznoszenia */
        float remember_size[5]; /*!< zapamietane wymiary */
        bool moving=0; /*!< czy dron jest w trackie ruchu */
        static int Amount_of_drones; /*!< Ilośc istniejących dronów */
        static int Created_drones; /*!< stworzone drony */
private:
        friend class Fabric;
        Drone(float a, float b, float h, float radius, float h2, char new_name[20]) : body(a,b,h) {
                NEW_Vector rotor_pos;
                movement.change(0,1,0);

                remember_size[0]=a;
                remember_size[1]=b;
                remember_size[2]=h;
                remember_size[3]=radius;
                remember_size[4]=h2;

                rotor_pos.change(a/2,b/2,h/2+h2/2);
                rotors[0] = new Rotor(radius,h2,rotor_pos,1.0); //Prawy przedni
                rotor_pos.change(-a/2,b/2,h/2+h2/2);
                rotors[1] = new Rotor(radius,h2,rotor_pos,-1.0);  //Lewy Przedni
                rotor_pos.change(-a/2,-b/2,h/2+h2/2);
                rotors[2] = new Rotor(radius,h2,rotor_pos,1.0);  //Lewy tylni
                rotor_pos.change(a/2,-b/2,h/2+h2/2);
                rotors[3] = new Rotor(radius,h2,rotor_pos,-1.0);   //Prawy tylni
                rising_angle=0;
                speed=100;
                _ID=9000+Created_drones;
                for(int i=0; i<20; ++i) {_name[i]=new_name[i]; };
                ++Amount_of_drones;
                ++Created_drones;
        }

public:


        Drone(const Drone& obs) : body(obs.body){
                ++Amount_of_drones;
                ++Created_drones;

        }



        virtual ~Drone(){
                for(int i=0; i<4; ++i) {
                        delete rotors[i];
                };
                --Amount_of_drones;
        }

        /*!
           \brief Wyswietla wspolrzedne wierzcholkow obiektu
           \param Strm strumien wyjsciowy do zapisu
           \return Brak
         */
        virtual void Show_Size(std::ostream &Strm) const {
                Strm<<"   Drone width     : "<<std::setw(5)<<remember_size[0]<<endl;
                Strm<<"   Drone lenght    : "<<std::setw(5)<<remember_size[1]<<endl;
                Strm<<"   Drone height    : "<<std::setw(5)<<remember_size[2]<<endl;
                Strm<<"   Rotor radius    : "<<std::setw(5)<<remember_size[3]<<endl;
                Strm<<"   Rotor height    : "<<std::setw(5)<<remember_size[4]<<endl;
        }

/*!
   \brief Wyswietla wspolrzedne wierzcholkow drona
   \param Strm strumien wyjsciowy do zapisu
   \return Brak
 */
        virtual void Display(std::ostream &Strm) {

                (*this).Update_movement();
                body.Turn(rotation[1]);
                body.Move(position);
                body.Display(Strm);
                body.Move(position* -1);
                body.Turn_undo();
                for(int i=0; i<4; ++i) {
                        rotors[i]->Turn(rotation[1]);
                        rotors[i]->Move(position);
                        rotors[i]->Display(Strm);
                        rotors[i]->Move(position* -1);
                        rotors[i]->Turn_undo();
                };
                //cout<<"Displayed drone "<<_name<<endl;


        }



/*!
   \brief Odswieza aktualne wartosci wektora ruchu
   \return Brak
 */
        void Update_movement(){
                movement.change(0,1,0);
                movement[OY]=cos(rising_angle*M_PI/180);
                movement[OZ]=sin(rising_angle*M_PI/180);
                movement=rotation[1]*movement;
        }

/*!
   \brief Zmienia kat wznoszenia sie drona.
   \param new_angle nowa wartosc kata wznoszenia
   \return Brak
 */
        void Change_angle(float new_angle){
                rising_angle=new_angle;
                (*this).Update_movement();
        }
/*!
   \brief Zmienia wartosc predkosci drona
   \param new_speed nowa wartosc predkosci
   \return Brak
 */
        void Change_speed(float new_speed){
                speed=new_speed;
                for(int i=0; i<4; ++i) {
                        (*rotors[i]).Change_speed(new_speed*10);
                };
        }

/*!
   \brief Wykonuje lot drona.
   \param seconds - czas lotu drona
   \return Brak
 */
        void Move_time(float seconds){
                (*this).Update_movement();
                Spin_rotors(seconds);
                position=position+movement*(speed*seconds);
        }
        /*!
           \brief Wykonuje lot drona.
           \param distance - droga lotu drona
           \return Brak
         */
        void Move_distance(float distance){
                float time;
                (*this).Update_movement();
                time=distance/(movement.Lenght()*speed);
                (*this).Move_time(time);
        }

        /*!
           \brief Zwraca wartosc ostatniego kata wznoszenia
           \return Wartość kąta wznoszenia
         */
        float Read_angle() const {
                return rising_angle;
        }
        /*!
           \brief Odczytuje wektor ruchu
           \return Wektor ruchu
         */
        NEW_Vector Read_movement() const {
                return movement;
        }


        /*!
           \brief Odczytuje wektor ruchu
           \return Wektor ruchu
         */
        NEW_Vector Read_position() const {
                return position;
        }

        /*!
           \brief Odczytuje wartosc predkosci
           \return Wartosc predkosci drona
         */
        float Read_speed() const {
                return speed;
        }

        /*!
           \brief Zmienia wartosc predkosci obrotu rotorow
           \param L wsp predkosci obrotu lewego przedniego i prawego tylnego rotora
           \param P wsp predkosci obrotu prawego przedniego i lewego tylnego rotora
           \return Brak
         */
        void Rotor_spin_change(float L, float P){
                (*rotors[0]).Change_speed(P*speed*10);
                (*rotors[1]).Change_speed(L*speed*10);
                (*rotors[2]).Change_speed(P*speed*10);
                (*rotors[3]).Change_speed(L*speed*10);
        }
        /*!
           \brief Wywoluje funkcie wirowania rotorow
           \param seconds czas ruchu
           \return Brak
         */
        void Spin_rotors(float seconds){
                for(int i=0; i<4; ++i) {
                        (*rotors[i]).Spin(seconds);
                };
        }
        /*!
           \brief Pokazuje wlasciwosci drona
           \return Brak
         */
        void Show() const {
                cout<<"Drone current movement statistics:"<<endl;
                cout<<"  - center point position "<<position<<endl;
                cout<<"  - rotation matrix "<<endl;
                rotation[1].Display();
                cout<<"  - movement direction "<<movement<<endl;
                cout<<"  - speed value "<<speed<<endl;
                cout<<"  - rising angle "<<rising_angle<<endl;
        }

        /*!
         * \brief Funkcja zapisuje wspolrzedne punktow bryly do pliku
         * \param[in] filename - nazwa pliku, do zapisu wspolrzednych
         * \retval true - gdy operacja zapisu powiodła się,
         * \retval false - w przypadku przeciwnym.
         */

        virtual bool WriteToFile(string filename)
        {
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
   \brief Sprawdza dlugosci krawedzi kadluba
   \return Brak
 */
        void Body_edges(){
                body.EdgesLenght();
        }

        /*!
           \brief Zlicza ilosc aktualnych wektorow
           \return Ilość istniejących wektorów
         */
        static int Read_amount() {
                return Amount_of_drones;
        };
        /*!
           \brief Zlicza ilosc stworzonych dotychczas wektorow
           \return Ilość wektorów stworzonych od uruchomienia programu
         */
        static int Read_sum() {
                return Created_drones;
        };

        /*!
           \brief Zwraca promien obiektu
           \return Wartosc promienia
         */
        virtual float Your_Size() const {
                float your_radius;
                your_radius=sqrt(pow(remember_size[2]/2 + remember_size[4]/2,2) + pow((sqrt((pow(remember_size[0],2))/4 + (pow(remember_size[1],2))/4)+remember_size[3]),2));
                return your_radius;
        }

/*!
   \brief Ustawia drona jako w ruchu
 */
        void Set_In_Motion(){
                moving=1;
        }
        /*!
           \brief Ustawia drona jako w spoczynku
         */
        void Set_In_Standby(){
                moving=0;
        }


/*!
   \brief Sprawdza liste obiektow w poszukiwaniu kolizji
   \param obstacles lista przeszkod
   \return true jesli znalazlo kolizje
 */
        virtual bool Check_Collision(const std::list<std::shared_ptr<Object3D> >  &obstacles) const {
                auto iter = obstacles.begin();
                int end=0;
                while(end==0) {
                        if(iter==obstacles.end()) {
                                end=END_OF_DATA;
                        }else{
                                if((*iter)->ID()!=_ID) {
                                        cout<<"Sprawdzam kolizje z "<<(*iter)->ID()<<endl;
                                        if(Who_is_there(*(*iter))==1) {
                                                cout<<"tutaj"<<endl;
                                                return 1;
                                        };
                                };
                                ++iter;
                        };
                };
                return 0;
        }

/*!
   \brief Sprawdza kolizje z wybranym obiektem
   \param obstacle wybrany obiekt
   \return true jesli jest kolizja
 */
        virtual bool Who_is_there(Object3D& obstacle) const {
//SPRAWDZAMY ZDERZENIE Z DRONEM
                NEW_Vector real_center;
                NEW_Vector distance_direction;
                float other_radius;
                float distance_between;
                float radius;

                real_center=center();
                real_center[OZ]+=remember_size[4]/2;
                other_radius=obstacle.Your_Size();
                distance_direction=(position+(movement*(moving*speed/FPS)))-obstacle.center();
                radius=Your_Size();
                distance_between=distance_direction.Lenght();
                cout<<"odleglosc to "<<distance_between<<endl;
                cout<<"Promien drona to "<<radius<<endl;
                cout<<"Promien przeszkody to "<<other_radius<<endl;
                if(distance_between>=radius+other_radius) {
                        cout<<"Obiekt jest zbyt daleko"<<endl;
                        return 0;
                };              // Gdy obiekty są znacznie oddalone
                if(obstacle.ID()>=9000) {
                        radius=sqrt(pow(remember_size[0]/2,2)+pow(remember_size[1]/2,2))+remember_size[3];
                        if(obstacle.Is_This_Sit_Taken(real_center,movement*(moving*speed/FPS),radius,(remember_size[2]+remember_size[4])/2)) {
                                return 1;
                        };
//SPRAWDZAMY ZDERZENIE Z OKNEM
                }else if(obstacle.ID()>=1000) {
                        cout<<" Sprawdzam window"<<endl;
                        if(obstacle.Is_This_Sit_Taken(real_center,movement*(moving*speed/FPS),radius,(remember_size[2]+remember_size[4])/2)==1) {
                                cout<<"halo"<<endl;
                                return 1;
                        };
//SPRAWDZAMY ZDERZENIE Z PRZESZKODA
                }else{
                        cout<<" Sprawdzam obstacle"<<endl;
                        if(obstacle.Is_This_Sit_Taken(real_center,movement*(moving*speed/FPS),radius,(remember_size[2]+remember_size[4])/2)) {
                                return 1;
                        };

                };
                return 0;
        }

        /*!
           \brief Sprawdza kolizje naszego drona z dronem ktory wyslal zapytanie
           \param Your_pos pozycja drona
           \param Your_move przemieszczenie drona
           \param radius promien drona
           \param height wysokosc drona
           \return true jesli doszlo do kolizji
         */

        virtual bool Is_This_Sit_Taken(const NEW_Vector &Your_pos,const NEW_Vector Your_move, float radius, float height){

                NEW_Vector my_move;
                NEW_Vector local_position;
                float my_height;
                float my_radius;
                float distance_2D;
                float distance_OZ;
                my_radius=sqrt(pow(remember_size[0]/2,2)+pow(remember_size[1]/2,2))+remember_size[3];
                my_move = movement*(moving*speed/FPS);
                my_height=(remember_size[2]+remember_size[4])/2;

                local_position=Your_pos-position+Your_move-my_move;

                distance_2D=sqrt(pow(local_position[OX],2)+pow(local_position[OY],2));
                if(local_position[OZ]<0) {
                        distance_OZ=-1*local_position[OZ];
                }else{
                        distance_OZ=local_position[OZ];
                }
                cout<<"In is.this.sit.taken before check"<<endl;
                if(distance_2D<my_radius+radius) {
                        if(distance_OZ<=height+my_height) {
                                cout<<"Distance OZ "<<distance_OZ<<endl;
                                cout<<"Drone not moving height "<<height<<endl;
                                cout<<"Drone moving height "<<my_height<<endl;
                                cout<<"In is.this.sit.taken when return 1"<<endl;
                                return 1;
                        };
                };
                cout<<"In is.this.sit.taken when return 0"<<endl;
                return 0;
        }
};

/*!
   \file main.cpp
   \brief Glowny plik zawierajacy wywolanie menu i funkcji zewnetrznych
   \author Patryk Szydlik
   \date 20.04.19
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <string.h>



#include "gnuplot_link.hh"
using namespace std;




#include "Scene.hh"

int NEW_Vector::Amount_of_vectors=0;
int NEW_Vector::Created_vectors=0;
int NEW_Matrix::Amount_of_matrix=0;
int Drone::Amount_of_drones=0;
int Cuboid::Amount_of_cuboids=0;
int Body::Amount_of_bodies=0;
int Hex_prism::Amount_of_hexprism=0;
int Rotor::Amount_of_rotors=0;
int Obstacle::Amount_of_obstacles=0;
int Obstacle::Created_obstacles=0;
int Drone::Created_drones=0;
int Window::Amount_of_windows=0;
int Window::Created_windows=0;
Fabric_Ptr Fabric::_Fabric;




/*!
   \brief Funkcja zawiera w sobie kod menu wraz z wywolaniami wszystkich funkcji zewnetrznych
 */
int main(){
        PzG::GnuplotLink link;       /*!< Ta zmienna jest potrzebna do wizualizacji rysunku */
        NEW_Vector W_trans; /*!< Wektor translacji do przesuniecia bryly */
        NEW_Matrix M1,M2; /*!< Zmienne wykorzystane do sekwencji obrotow */
        NEW_Matrix rotation(0); /*!< macierz glowna obrotu */
        double angle; /*!< kat obrotu */
        char menu[4]="sm";/*!< zmienna do obslugi menu */
        char sign; /*!< zmienna znakowa do wczytania znakow ignorowanych */

        char axis; /*!< zmienna przechowujaca symbol wybranej osi obrotu */
        Scene scene;
        float distance=0; /*!< Dystans do przelotu */
        float speed=0; /*!< Predkosc ruchu */
        float time=0; /*!< czas ruchu */
        float ris_angle=0; /*!< kat wznoszenia */
        ofstream file_stream; /*!< Strumien plikowy */
        int numer=0; /*!< wartosc numeru */
        //  Obstacle* obs_ptr; /*!< wskaznik na obstacle */
        //  Drone* drn_ptr; /*!< wskaznik na dron */
        //  Window* win_ptr; /*!< wskaznik na window */
        char new_name[20]; /*!< tablica na name */

        shared_ptr<Object3D> chosen;
        shared_ptr<Drone> chosen_dr;
        ObjectType type;
        float size_param[5];   /*!< Zmienne przechowujace dlugosci bokow bryl */
        int obj_ID;
        link.Init();


//Tutaj bedzie nowe menu do obslugi zadania 6


//Stare menu
        link.Init();
        link.SetDrawingMode(PzG::DM_3D);
        link.SetRangeX(-600,600);
        link.SetRangeY(-400,1200);
        link.SetRangeZ(-1200,1200);

        system("clear");
        cout<<"   ------------------------------------------------------"<<endl;
        cout<<"  |                  BASIC INFORMATION                   |"<<endl;
        cout<<"   ------------------------------------------------------"<<endl;
        cout<<"    AMOUNT OF CREATED 3D OBJECTS  :  "<< Window::Read_sum()+Drone::Read_sum()+Obstacle::Read_sum()<<endl;
        cout<<"    AMOUNT OF EXISTING 3D OBJECTS :  "<< Window::Read_amount()+Drone::Read_amount()+Obstacle::Read_amount()<<endl;
        cout<<endl;
        cout<<"    AMOUNT OF CREATED VECTORS     :  "<< NEW_Vector::Read_sum()<<endl;
        cout<<"    AMOUNT OF EXISTING VECTORS    :  "<< NEW_Vector::Read_amount()<<endl;
        cout<<endl;
        cout<<"Put any char and click ENTER to continue."<<endl;
        cin.ignore(100,'\n');

        strcpy(new_name,"Cube 1");
        type=ITS_Obstacle;
        size_param[0]=200;
        size_param[1]=200;
        size_param[2]=200;
        obj_ID = scene.ADD(size_param,new_name,type);
        if(scene.give_by_ID(obj_ID,chosen)) {
                cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
        };
        if(obj_ID>=9000) {
                chosen_dr=std::static_pointer_cast<Drone> (chosen);
        };
        W_trans.change(0,900,-100);
        chosen->Move(W_trans);
        rotation.Add(60,'x');
        chosen->Turn(rotation);

        strcpy(new_name,"Flat cuboid");
        type=ITS_Obstacle;
        size_param[0]=100;
        size_param[1]=200;
        size_param[2]=50;
        obj_ID = scene.ADD(size_param,new_name,type);
        if(scene.give_by_ID(obj_ID,chosen)) {
                cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
        };
        if(obj_ID>=9000)
                chosen_dr=static_pointer_cast<Drone>(chosen);
        W_trans.change(300,200,200);
        chosen->Move(W_trans);

        strcpy(new_name,"Bar 1");
        type=ITS_Obstacle;
        size_param[0]=50;
        size_param[1]=50;
        size_param[2]=400;
        obj_ID = scene.ADD(size_param,new_name,type);
        if(scene.give_by_ID(obj_ID,chosen)) {
                cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
        };
        if(obj_ID>=9000) {
                chosen_dr=std::static_pointer_cast<Drone> (chosen);
        };
        W_trans.change(-200,-200,-200);
        chosen->Move(W_trans);

        strcpy(new_name,"Bar 2");
        type=ITS_Obstacle;
        size_param[0]=20;
        size_param[1]=20;
        size_param[2]=600;
        obj_ID = scene.ADD(size_param,new_name,type);
        if(scene.give_by_ID(obj_ID,chosen)) {
                cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
        };
        if(obj_ID>=9000) {
                chosen_dr=std::static_pointer_cast<Drone> (chosen);
        };
        W_trans.change(-400,900,400);
        chosen->Move(W_trans);

        strcpy(new_name,"Window 1");
        type=ITS_Window;
        size_param[0]=400;
        size_param[1]=1;
        obj_ID = scene.ADD(size_param,new_name,type);
        if(scene.give_by_ID(obj_ID,chosen)) {
                cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
        };
        if(obj_ID>=9000) {
                chosen_dr=std::static_pointer_cast<Drone> (chosen);
        };
        W_trans.change(0,300,0);
        chosen->Move(W_trans);

        strcpy(new_name,"Window 2");
        type=ITS_Window;
        size_param[0]=600;
        size_param[1]=3;
        obj_ID = scene.ADD(size_param,new_name,type);
        if(scene.give_by_ID(obj_ID,chosen)) {
                cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
        };
        if(obj_ID>=9000) {
                chosen_dr=std::static_pointer_cast<Drone> (chosen);
        };
        W_trans.change(0,900,400);
        chosen->Move(W_trans);

        strcpy(new_name,"Drone 1");
        type=ITS_Drone;
        size_param[0]=100;
        size_param[1]=150;
        size_param[2]=50;
        size_param[3]=40;
        size_param[4]=25;
        obj_ID = scene.ADD(size_param,new_name,type);
        if(scene.give_by_ID(obj_ID,chosen)) {
                cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
        };
        if(obj_ID>=9000) {
                chosen_dr=std::static_pointer_cast<Drone> (chosen);
        };
        W_trans.change(0,0,0);
        chosen->Move(W_trans);

        strcpy(new_name,"Drone 2");
        type=ITS_Drone;
        size_param[0]=100;
        size_param[1]=150;
        size_param[2]=50;
        size_param[3]=40;
        size_param[4]=25;
        obj_ID = scene.ADD(size_param,new_name,type);
        if(scene.give_by_ID(obj_ID,chosen)) {
                cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
        };
        W_trans.change(0,-400,0);
        chosen->Move(W_trans);
        if(obj_ID>=9000) {
                chosen_dr=std::static_pointer_cast<Drone> (chosen);
                scene.clear_tracking();
                scene.tracking_point(chosen_dr->Read_position());
        };





        link.SetDrawingMode(PzG::DM_3D);

        while(menu[0]!='Q') {
                scene.Update_files(link);  // Po wyk. instr. odświeża listę plików do rysowania
                scene.Display(chosen->ID());       // Po wyk. instr. zapisuje wspolrzedne do plików
                link.Draw();           // Po wyk. instr. rysuje scene


// Wyswietlanie nowego menu
                system("clear");
                cout<<"   ------------------------------------------------------"<<endl;
                cout<<"  |                  BASIC INFORMATION                   |"<<endl;
                cout<<"   ------------------------------------------------------"<<endl;
                cout<<"    AMOUNT OF CREATED 3D OBJECTS  :  "<< Window::Read_sum()+Drone::Read_sum()+Obstacle::Read_sum()<<endl;
                cout<<"    AMOUNT OF EXISTING 3D OBJECTS :  "<< Window::Read_amount()+Drone::Read_amount()+Obstacle::Read_amount()<<endl;
                cout<<endl;
                cout<<"    AMOUNT OF CREATED VECTORS     :  "<< NEW_Vector::Read_sum()<<endl;
                cout<<"    AMOUNT OF EXISTING VECTORS    :  "<< NEW_Vector::Read_amount()<<endl;
                cout<<endl;
                cout<<"    CHOSEN OBJECT   : "; if(chosen->ID()>=9000) {cout<<std::setw(20)<<" DRONE"<<endl; }else if(chosen->ID()>=1000) {cout<<std::setw(20)<<" WINDOW"<<endl; }else{cout<<std::setw(20)<<" OBSTACLE"<<endl; };
                cout<<"             NAME   : "; chosen->name(cout); cout<<endl;
                cout<<"               ID   :  "; cout<<std::setw(19)<<chosen->ID()<<endl;
                cout<<"         POSITION   : "; chosen->Read_position(cout); cout<<endl;
                if(chosen->ID()>=9000) {
                        cout<<"    CURRENT SPEED   : "; cout<<std::setw(20)<<chosen_dr->Read_speed()<<endl;
                };
                cout<<"   ------------------------------------------------------"<<endl;
                cout<<"  |                     EDIT OBJECT                      |"<<endl;
                cout<<"   ------------------------------------------------------"<<endl;
                if(chosen->ID()>=9000) {
                        cout<<"                F  -  FLY DRONE"<<endl;
                        cout<<"                T  -  TURN DRONE"<<endl;
                        cout<<"               CS  -  CHANGE SIZE OF DRONE"<<endl;
                        cout<<"               CP  -  CHANGE PARAMETERS"<<endl;
                        cout<<"               CN  -  CHANGE NAME OF DRONE"<<endl;

                }else{

                        cout<<"                M  -  MOVE OBSTACLE"<<endl;
                        cout<<"                R  -  ROTATE OBSTACLE"<<endl;
                        cout<<"               CS  -  CHANGE SIZE OF OBSTACLE"<<endl;
                        cout<<"               CN  -  CHANGE NAME OF OBSTACLE"<<endl;

                };
                cout<<"                A  -  ADD NEW OBJECT"<<endl;
                cout<<"                S  -  CHANGE SELECTION"<<endl;
                cout<<"                D  -  DELETE CHOSEN OBJECT"<<endl<<endl;
                cout<<"                Q  -  QUIT"<<endl<<endl<<endl;

                cout << "  YOUR CHOICE        >>>  ";
                cin.clear();
                cin >> menu;

                switch (menu[0]) {

//  Dodawanie nowego drona
                case 'U':
                        cout<<"czemu 2"<<endl;
                        cout<<"halo halo"<<endl;
                        break;
                case 'A':
                        system("clear");
                        cout<<"Choose what you want to add :"<<endl;
                        cout<<"   D - drone"<<endl;
                        cout<<"   O - obstacle"<<endl;
                        cout<<"   W - window"<<endl;
                        cout<<"   C - cancel"<<endl;
                        do {
                                cin>>menu;
                                if(menu[0]!='D' && menu[0]!='O' && menu[0]!='W' && menu[0]!='C') {
                                        cout<<" Wrong option! Try again."<<endl;
                                };
                        } while(menu[0]!='D' && menu[0]!='O' && menu[0]!='W' && menu[0]!='C');
                        switch(menu[0]) {
                        case 'D':
                                if(Drone::Read_amount()<3) {
                                        for(int i=0; i<5; ++i)
                                                size_param[i]=1;
                                        cout<<"Choose the width of drone: ";
                                        do {
                                                if(cin.fail()||size_param[0]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[0];
                                        } while(cin.fail()||size_param[0]<=0);
                                        cout<<"Choose the lenght of drone: ";
                                        do {
                                                if(cin.fail()||size_param[1]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[1];
                                        } while(cin.fail()||size_param[1]<=0);
                                        cout<<"Choose the height of Drone body:";
                                        do {
                                                if(cin.fail()||size_param[2]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[2];
                                        } while(cin.fail()||size_param[2]<=0);
                                        cout<<"Choose the radius of rotor : ";
                                        do {
                                                if(cin.fail()||size_param[3]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[3];
                                        } while(cin.fail()||size_param[3]<=0);
                                        cout<<"Choose the height of rotor : ";
                                        do {
                                                if(cin.fail()||size_param[4]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[4];
                                        } while(cin.fail()||size_param[4]<=0);
                                        cout<<"Choose the name for the drone : ";
                                        cin>>new_name;
                                        type=ITS_Drone;
                                        obj_ID = scene.ADD(size_param,new_name,type);
                                        if(scene.give_by_ID(obj_ID,chosen)) {
                                                cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
                                        };
                                        scene.clear_tracking();
                                        if(obj_ID>=9000) {
                                                chosen_dr=std::static_pointer_cast<Drone> (chosen);
                                                scene.tracking_point(chosen_dr->Read_position());
                                        };
                                        chosen_dr->Change_speed(50);
                                }else{
                                        cout<<"ERROR  :  Reached maximum number of drones!"<<endl;
                                        cout<<"Put any char and ENTER to continue."<<endl;
                                        cin>>sign;
                                        cin.ignore(100,'\n');
                                };
                                break;
                        case 'O':
                                for(int i=0; i<5; ++i)
                                        size_param[i]=1;
                                cout<<"Choose the width of obstacle: ";
                                do {
                                        if(cin.fail()||size_param[0]<=0) {
                                                cin.clear();
                                                cin.ignore(100,'\n');
                                                cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                        };
                                        cin>>size_param[0];
                                } while(cin.fail()||size_param[0]<=0);
                                cout<<"Choose the lenght of obstacle: ";
                                do {
                                        if(cin.fail()||size_param[1]<=0) {
                                                cin.clear();
                                                cin.ignore(100,'\n');
                                                cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                        };
                                        cin>>size_param[1];
                                } while(cin.fail()||size_param[1]<=0);
                                cout<<"Choose the height of obstacle:";
                                do {
                                        if(cin.fail()||size_param[2]<=0) {
                                                cin.clear();
                                                cin.ignore(100,'\n');
                                                cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                        };
                                        cin>>size_param[2];
                                } while(cin.fail()||size_param[2]<=0);
                                cout<<"Choose the name for the obstacle : ";
                                cin>>new_name;
                                type=ITS_Obstacle;
                                obj_ID = scene.ADD(size_param,new_name,type);
                                if(scene.give_by_ID(obj_ID,chosen)) {
                                        cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
                                };
                                scene.clear_tracking();
                                if(obj_ID>=9000) {
                                        chosen_dr=std::static_pointer_cast<Drone> (chosen);
                                        scene.tracking_point(chosen_dr->Read_position());
                                };
                                break;

                        case 'W':
                                for(int i=0; i<5; ++i)
                                        size_param[i]=1;
                                cout<<"Choose the diagonal of window: ";
                                do {
                                        if(cin.fail()||size_param[0]<=0) {
                                                cin.clear();
                                                cin.ignore(100,'\n');
                                                cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                        };
                                        cin>>size_param[0];
                                } while(cin.fail()||size_param[0]<=0);
                                cout<<"Choose the direction of window"<<endl;
                                cout<<"  1 - parallel to XZ"<<endl;
                                cout<<"  2 - parallel to YZ"<<endl;
                                cout<<"  3 - parallel to XY"<<endl;
                                do {
                                        if(cin.fail()||size_param[1]>3||size_param[1]<0) {
                                                cin.clear();
                                                cin.ignore(100,'\n');
                                                cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                        };
                                        cin>>size_param[1];
                                } while(cin.fail()||size_param[1]>3||size_param[1]<0);

                                cout<<"Choose the name for the window : ";
                                cin>>new_name;

                                type=ITS_Window;
                                obj_ID = scene.ADD(size_param,new_name,type);
                                if(scene.give_by_ID(obj_ID,chosen)) {
                                        cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
                                };
                                scene.clear_tracking();
                                if(obj_ID>=9000) {
                                        chosen_dr=std::static_pointer_cast<Drone> (chosen);
                                        scene.tracking_point(chosen_dr->Read_position());
                                };
                                break;

                        case 'C':
                                break;
                        };
                        break;

//  DZIAŁA
                case 'D':
                        system("clear");
                        if(chosen->ID()>=9000) {
                                scene.clear_tracking();
                                if(Drone::Read_amount()>=2) {
                                        scene.delete_ob(chosen); //Usuwa wskaznik na wybrany obiekt
                                        scene.give_by_iter(0,chosen);
                                        if(chosen->ID()>=9000) {
                                                chosen_dr = std::static_pointer_cast<Drone> (chosen);
                                                scene.tracking_point(chosen_dr->Read_position());
                                        };
                                }else{
                                        cout<<"ERROR  :  You can't delete last existing drone! "<<endl;
                                        cout<<"Put any char and ENTER to continue."<<endl;
                                        cin>>sign;
                                        cin.ignore(100,'\n');
                                };
                        }else{
                                scene.delete_ob(chosen);
                                scene.give_by_iter(0,chosen);
                                if(chosen->ID()>=9000) {
                                        chosen_dr = std::static_pointer_cast<Drone> (chosen);
                                        scene.tracking_point(chosen_dr->Read_position());
                                };
                        }
                        break;


                //  DO POPRAWIENIA MECHANIZM ZMIANY WYBORU
                case 'S':
                        system("clear");
                        cout<<"    CHOSEN OBJECT   : "; if(chosen->ID()>=9000) {cout<<std::setw(20)<<" DRONE"<<endl; }else if(chosen->ID()>=1000) {cout<<std::setw(20)<<" WINDOW"<<endl; }else{cout<<std::setw(20)<<" OBSTACLE"<<endl; };
                        cout<<"             NAME   : "; chosen->name(cout); cout<<endl;
                        cout<<"               ID   :  "; cout<<std::setw(19)<<chosen->ID()<<endl;
                        cout<<"         POSITION   : "; chosen->Read_position(cout); cout<<endl;
                        cout<<"   Choose an object to select  :"<<endl;
                        obj_ID=scene.enlist();
                        cout<<endl<<"   0 - cancel selection"<<endl<<endl;
                        cout<<"    >>>   ";
                        numer=0;
                        do {
                                if(cin.fail()||numer>obj_ID) {
                                        cin.clear();
                                        cin.ignore(100,'\n');
                                        cout<<"Incorrect angle value! Insert value one more time:"<<endl;
                                };
                                cin>>numer;
                        } while(cin.fail()||numer>obj_ID);
                        if(numer!=0) {
                                scene.give_by_iter(numer-1,chosen);
                                scene.clear_tracking();
                        };
                        if(chosen->ID()>=9000) {
                                chosen_dr = std::static_pointer_cast<Drone> (chosen);
                                scene.tracking_point(chosen_dr->Read_position());
                        };

                        break;


                //  OBRÓT BEZPOŚREDNI PRZESZKODY
                case 'R':
                        cout<<"here"<<endl;
                        if(chosen->ID()<9000) {
                                system("clear");
                                cout<<"Podaj oś i kat obrotu "<<endl;
                                while(axis!='.') {
                                        cin >> axis;
                                        if(axis=='x'||axis=='y'||axis=='z') {
                                                do {
                                                        if(cin.fail()) {
                                                                cin.clear();
                                                                cin.ignore(100,'\n');
                                                                cout<<"Incorrect angle value! Insert value one more time:"<<endl;
                                                        };
                                                        cin>>angle;
                                                } while(cin.fail());
                                                M2.Add(angle,axis);
                                                M1=M2*M1;
                                        } else if(axis=='.') {

                                        }else{
                                                cout<<"Incorrect sign of axis! Insert sign one more time:"<<endl;
                                        };
                                };
                                M2.Add(angle,axis);
                                rotation=M2;
                                (*chosen).Turn(rotation);
                        }else{
                                cout<<"ERROR  :  You can't simply rotate the drone!  Try using T - turn. "<<endl;
                                cout<<"Put any char and click ENTER to continue."<<endl;
                                cin>>sign;
                                cin.ignore(100,'\n');
                        };
                        break;

// DO POPRAWIENIA WYBÓR DRONA A NIE OBIEKTU
                case 'F':
                        if(chosen->ID()>=9000) {
                                system("clear");
                                sign='a';
                                cout<<"Choose the direction of flight (a - Ahead  r- Reverse)"<<endl;
                                do {
                                        if(cin.fail()||(sign!='a' && sign!='r')) {
                                                cin.clear();
                                                cin.ignore(100,'\n');
                                                cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                        };
                                        cin>>sign;
                                } while(cin.fail()||(sign!='a' && sign!='r'));

                                cout<<"Choose the distance of flight (s > 0)"<<endl;
                                do {
                                        cin>>distance;
                                        if(cin.fail()||distance<0) {
                                                cin.clear();
                                                cin.ignore(100,'\n');
                                                cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                        };

                                } while(cin.fail()||distance<0);


                                cout<<"Choose the angle of flight ( 90 >= a >= -90)"<<endl;
                                do {
                                        if(cin.fail()||ris_angle>90||ris_angle<-90) {
                                                cin.clear();
                                                cin.ignore(100,'\n');
                                                cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                        };
                                        cin>>ris_angle;
                                } while(cin.fail()||ris_angle>90||ris_angle<-90);
                                (*chosen_dr).Change_angle(ris_angle);


                                speed=(*chosen_dr).Read_speed();
                                W_trans =(*chosen_dr).Read_movement();
                                time=distance/(W_trans.Lenght()*speed);
                                if(sign=='r') {distance=-distance; };

                                scene.Update_files(link);
                                scene.Display(chosen->ID());

                                cout<<"Estimated flight time : "<<time<<endl;
                                cout << "Put char and push ENTER to start animation" << endl;
                                link.Draw();                        // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
                                cin >> sign;
                                usleep(1000000);

                                (*chosen_dr).Set_In_Motion();
                                distance=distance/(time*FPS);
                                scene.tracking_point(chosen_dr->Read_position());
                                for(int i=0; i<time*FPS; ++i) {
                                        usleep(1000000/FPS);
                                        if((*chosen_dr).Check_Collision(scene.Data_acces())==1) {
                                                i=time*FPS;
                                                cout<< " WARNING : Risk of collision has been detected! : "<<endl;
                                                cout<< "           Flight has been stopped.    "<<endl;
                                                cout << "Put char and push ENTER to continue" << endl;
                                                link.Draw();                        // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
                                                cin >> sign;
                                        }else{
                                                (*chosen_dr).Move_distance(distance);
                                                scene.tracking_point(chosen_dr->Read_position());
                                                scene.Display(chosen->ID());
                                                link.Draw();
                                        };

                                        scene.undo_tracking_point();


                                };

                                scene.tracking_point(chosen_dr->Read_position());
                                (*chosen_dr).Set_In_Standby();
                        }else{
                                cout<<"ERROR  :  Obstacle can't fly!  Try using M - move. "<<endl;
                                cout<<"Put any char and click ENTER to continue."<<endl;
                                cin>>sign;
                                cin.ignore(100,'\n');
                        };

                        break;

                case 'M':
                        if(chosen->ID()<9000) {
                                system("clear");
                                cout<<"Choose translation vector   : "<<endl;
                                cin >> W_trans;
                                (*chosen).Move(W_trans);


                        }else{
                                cout<<"ERROR  :  You can't simply move the drone!  Try using F - fly. "<<endl;
                                cout<<"Put any char and click ENTER to continue."<<endl;
                                cin>>sign;
                                cin.ignore(100,'\n');
                        };
                        break;

                case 'T':
                        system("clear");
                        if(chosen->ID()>=9000) {

                                axis='z';
                                cout<<"Choose angle of rotation:"<<endl;
                                M2.Add(0,'x');
                                do {
                                        if(cin.fail()) {
                                                cin.clear();
                                                cin.ignore(100,'\n');
                                                cout<<"Incorrect angle value! Insert value one more time:"<<endl;
                                        };
                                        cin>>angle;
                                } while(cin.fail());
                                speed=(*chosen_dr).Read_speed();
                                if(angle>=0) {time = angle/speed; }else if(angle<0) {time = -angle/speed; };




                                scene.Update_files(link);
                                scene.Display(chosen->ID());

                                cout<<"Estimated flight time : "<<time<<endl;
                                cout << "Put char and push ENTER to start animation" << endl;
                                link.Draw();                // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
                                cin >> sign;
                                usleep(1000000);


                                angle=angle/(time*FPS);
                                if(angle>0) {
                                        (*chosen_dr).Rotor_spin_change(1.5,4);
                                }else if(angle<0) {
                                        (*chosen_dr).Rotor_spin_change(4,1.5);
                                };
                                for(int i=1; i<=time*FPS; ++i) {
                                        usleep(1000000/FPS);
                                        rotation.Add(angle*i,axis);
                                        (*chosen_dr).Spin_rotors(1/(time*FPS));
                                        (*chosen_dr).Turn(rotation);
                                        scene.Display(chosen->ID());
                                        (*chosen_dr).Turn_undo();
                                        link.Draw();

                                };
                                (*chosen_dr).Turn(rotation);
                        }else{
                                cout<<"ERROR  :  The obstacles can't turn themselves!  Try using R - rotate. "<<endl;
                                cout<<"Put any char and click ENTER to continue."<<endl;
                                cin>>sign;
                                cin.ignore(100,'\n');
                        };

                        break;

// CHANGE SMTHG
                case 'C':
                        switch(menu[1]) {
                        //ZMIANA WYMIARÓW
                        case 'S':
                                system("clear");
                                cout<<"    CHOSEN OBJECT   : "; if(chosen->ID()>=9000) {cout<<std::setw(20)<<" DRONE"<<endl; }else if(chosen->ID()>=1000) {cout<<std::setw(20)<<" WINDOW"<<endl; }else{cout<<std::setw(20)<<" OBSTACLE"<<endl; };
                                cout<<"             NAME   : "; chosen->name(cout); cout<<endl;
                                cout<<"               ID   :  "; cout<<std::setw(19)<<chosen->ID()<<endl;
                                cout<<"         POSITION   : "; chosen->Read_position(cout); cout<<endl;
                                chosen->Show_Size(cout);
                                if(chosen->ID()>=9000) {

                                        for(int i=0; i<5; ++i)
                                                size_param[i]=1;
                                        cout<<"Choose the width of drone: ";
                                        do {
                                                if(cin.fail()||size_param[0]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[0];
                                        } while(cin.fail()||size_param[0]<=0);
                                        cout<<"Choose the lenght of drone: ";
                                        do {
                                                if(cin.fail()||size_param[1]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[1];
                                        } while(cin.fail()||size_param[1]<=0);
                                        cout<<"Choose the height of Drone body:";
                                        do {
                                                if(cin.fail()||size_param[2]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[2];
                                        } while(cin.fail()||size_param[2]<=0);
                                        cout<<"Choose the radius of rotor : ";
                                        do {
                                                if(cin.fail()||size_param[3]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[3];
                                        } while(cin.fail()||size_param[3]<=0);
                                        cout<<"Choose the height of rotor : ";

                                        type=ITS_Drone;
                                        obj_ID = scene.ADD(size_param,new_name,type);
                                        {
                                                shared_ptr<Object3D> changed=chosen;
                                                if(scene.give_by_ID(obj_ID,chosen)) {
                                                        cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
                                                };
                                                scene.clear_tracking();
                                                if(obj_ID>=9000) {
                                                        chosen_dr=std::static_pointer_cast<Drone> (chosen);
                                                        scene.tracking_point(chosen_dr->Read_position());
                                                };
                                                {
                                                        shared_ptr<Drone> drone=static_pointer_cast<Drone>(chosen);
                                                        drone->Change_speed(drone->Read_speed());
                                                }
                                                changed->Copy_param(*chosen);
                                                scene.delete_ob(changed);
                                        }
                                }else if(chosen->ID()>=1000) {

                                        for(int i=0; i<5; ++i)
                                                size_param[i]=1;
                                        cout<<"Choose the diagonal of window: ";
                                        do {
                                                if(cin.fail()||size_param[0]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[0];
                                        } while(cin.fail()||size_param[0]<=0);
                                        {
                                                shared_ptr<Window> window=static_pointer_cast<Window>(chosen);
                                                size_param[1]=window->Read_orientation();
                                        }
                                        type=ITS_Window;
                                        obj_ID = scene.ADD(size_param,new_name,type);
                                        {
                                                shared_ptr<Object3D> changed=chosen;
                                                if(scene.give_by_ID(obj_ID,chosen)) {
                                                        cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
                                                };
                                                scene.clear_tracking();
                                                changed->Copy_param(*chosen);
                                                scene.delete_ob(changed);
                                        }
                                }else{

                                        for(int i=0; i<5; ++i)
                                                size_param[i]=1;
                                        cout<<"Choose the width of obstacle: ";
                                        do {
                                                if(cin.fail()||size_param[0]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[0];
                                        } while(cin.fail()||size_param[0]<=0);
                                        cout<<"Choose the lenght of obstacle: ";
                                        do {
                                                if(cin.fail()||size_param[1]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[1];
                                        } while(cin.fail()||size_param[1]<=0);
                                        cout<<"Choose the height of obstacle:";
                                        do {
                                                if(cin.fail()||size_param[2]<=0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>size_param[2];
                                        } while(cin.fail()||size_param[2]<=0);
                                        type=ITS_Obstacle;
                                        obj_ID = scene.ADD(size_param,new_name,type);
                                        {
                                                shared_ptr<Object3D> changed=chosen;
                                                if(scene.give_by_ID(obj_ID,chosen)) {
                                                        cerr<<"ERROR  :  Blad w znajdowaniu obiektu"<<endl;
                                                };
                                                scene.clear_tracking();
                                                changed->Copy_param(*chosen);
                                                scene.delete_ob(changed);
                                        }
                                };



                                break;
                        //ZMIANA PARAMETROW DRONA
                        case 'P':
                                system("clear");
                                if(chosen->ID()>=9000) {
                                        cout<<"    CHOSEN OBJECT   : "; if(chosen->ID()>=9000) {cout<<std::setw(20)<<" DRONE"<<endl; }else if(chosen->ID()>=1000) {cout<<std::setw(20)<<" WINDOW"<<endl; }else{cout<<std::setw(20)<<" OBSTACLE"<<endl; };
                                        cout<<"             NAME   : "; chosen->name(cout); cout<<endl;
                                        cout<<"               ID   :  "; cout<<std::setw(19)<<chosen->ID()<<endl;
                                        cout<<"         POSITION   : "; chosen->Read_position(cout); cout<<endl;
                                        cout<<"    CURRENT SPEED   : "; cout<<std::setw(20)<<chosen_dr->Read_speed()<<endl<<endl;
                                        cout<<" Choose new speed (v > 0):"<<endl;
                                        do {
                                                if(cin.fail()||speed<0) {
                                                        cin.clear();
                                                        cin.ignore(100,'\n');
                                                        cout<<"Incorrect number value! Insert value one more time:"<<endl;
                                                };
                                                cin>>speed;
                                        } while(cin.fail()||speed<0);
                                        chosen_dr->Change_speed(speed);
                                }else{
                                        cout<<"ERROR  :  You can change only parameters of Drones! Obstacles have none! "<<endl;
                                        cout<<"Put any char and click ENTER to continue."<<endl;
                                        cin>>sign;
                                        cin.ignore(100,'\n');
                                };
                                break;
                        //ZMIANA NAZWY OBIEKTU
                        case 'N':
                                system("clear");
                                cout<<"    CHOSEN OBJECT   : "; if(chosen->ID()>=9000) {cout<<std::setw(20)<<" DRONE"<<endl; }else if(chosen->ID()>=1000) {cout<<std::setw(20)<<" WINDOW"<<endl; }else{cout<<std::setw(20)<<" OBSTACLE"<<endl; };
                                cout<<"             NAME   : "; chosen->name(cout); cout<<endl;
                                cout<<"               ID   :  "; cout<<std::setw(19)<<chosen->ID()<<endl;
                                cout<<"         POSITION   : "; chosen->Read_position(cout); cout<<endl;

                                cout<<"   Choose new name for object (max 19 letters and no white signs)"<<endl;
                                {
                                        char load_name[50];
                                        cin>>load_name;
                                        for(int i=0; i<20; ++i) {
                                                new_name[i]=load_name[i];
                                                if(i==19) {new_name[i]='\n'; };
                                        };
                                        (*chosen).ChangeName(new_name);
                                }

                                break;
                        };
                        break;



                case 'Q':
                        system("clear");
                        cout<<endl<<"THE END"<<endl<<endl;
                        break;


                default:
                        system("clear");
                        cout<<"ERROR  :  There's no valid option named : "<<menu<<"!"<<endl;
                        cout<<"Put any char and ENTER to continue."<<endl;
                        cin>>sign;
                        cin.ignore(100,'\n');
                        break;
                } //koniec switch

        }         //koniec while

// DO POPRAWY

        return 0;

}

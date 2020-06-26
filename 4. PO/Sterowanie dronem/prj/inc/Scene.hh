/*!
   \file Scene.hh
   \brief Zawiera klase i metody obslugujace scenerie
   \author Patryk Szydlik
   \date 19.05.19
 */

#pragma once

#include "Fabric.hh"
#include "gnuplot_link.hh"

/*!
 * \brief Klasa tworzy scene do wyswietlania modeli
 */
class Scene {

        std::list<std::shared_ptr<Object3D> >  obstacles; /*!< lista obiektow przeszkod */
        std::list<NEW_Vector> trace; /*!< punkty sciezki */
public:

        Scene(){

        }

        virtual ~Scene(){

        }

/*!
   \brief Dodaje punkt do sciezki
   \param position pozycja obiektu zapisana do sciezki

 */
        void tracking_point(const NEW_Vector & position){
                trace.push_back(position);
        }

/*!
   \brief Usuniecie ostatniego punktu na sciezce

 */
        void undo_tracking_point(){
                trace.pop_back();
        }

/*!
   \brief Wyczyszczenie sciezki
 */
        void clear_tracking(){
                trace.clear();
        }

/*!
   \brief Dodaje przeszkode do listy
   \param new_obstacle wskaznik na przeszkode
 */
        int ADD(float size[5],char name[20],ObjectType type){
                shared_ptr<Object3D> new_ob;
                new_ob=Fabric::UseFabric()->CreateObject(type,size,name);
                obstacles.push_back(new_ob);
                return new_ob->ID();
        }

/*!
   \brief Udziela dostepu do listy obiektow
   \return Wskaznik na liste obiektow
 */
        std::list<std::shared_ptr<Object3D> >& Data_acces(){
                return obstacles;
        }

        /*!
           \brief Wyswietla elementy scenerii
           \param ID wartosc ID obiektu szukanego
           \return Brak
         */
        void Display(int ID){
                ofstream file_stream1; //Obstacles
                ofstream file_stream4; //drones
                ofstream file_stream2; //chosen
                ofstream file_stream3; //trace

                file_stream2.open("Chosen.dat");

                if (!file_stream2.is_open())  {
                        cerr << ":(  Operacja otwarcia do zapisu \"" << "Chosen.dat" << "\"" << endl
                             << ":(  nie powiodla sie." << endl;
                }

                file_stream4.open("Drones.dat");

                if (!file_stream4.is_open())  {
                        cerr << ":(  Operacja otwarcia do zapisu \"" << "Drones.dat" << "\"" << endl
                             << ":(  nie powiodla sie." << endl;
                }


                file_stream1.open("Obstacles.dat");
                if (!file_stream1.is_open())  {
                        cerr << ":(  Operacja otwarcia do zapisu \"" << "Obstacles.dat" << "\"" << endl
                             << ":(  nie powiodla sie." << endl;
                }
                int k=0;
                for(std::list<std::shared_ptr<Object3D> >::iterator Iter = obstacles.begin( ); Iter != obstacles.end( ); ++Iter) {
                        ++k;
                        //  cout<<"Petla wyswietlania. Powtorzenie "<<k<<endl;
                        if((*Iter)->ID()==ID) {
                                //      cout<<"Display chosen"<<endl;
                                (*Iter)->Display(file_stream2);
                        }else if((*Iter)->ID()>=9000) {
                                //      cout<<"Display drone"<<endl;
                                (*Iter)->Display(file_stream4);
                        }else if((*Iter)->ID()<9000) {
                                //      cout<<"Display obstacle or window"<<endl;
                                (*Iter)->Display(file_stream1);
                        };
                };

                file_stream1.close();
                file_stream2.close();
                file_stream4.close();




                file_stream3.open("Trace.dat");
                if (!file_stream3.is_open())  {
                        cerr << ":(  Operacja otwarcia do zapisu \"" << "Obstacles.dat" << "\"" << endl
                             << ":(  nie powiodla sie." << endl;
                };
                if(trace.size()>=2) {
                        for(std::list<NEW_Vector>::iterator Iter = trace.begin(); Iter != trace.end(); ++Iter) {
                                ++Iter;
                                if(Iter!=trace.end()) {
                                        --Iter;
                                        file_stream3<<endl;
                                        (*Iter).Display(file_stream3);
                                        file_stream3<<endl;
                                        ++Iter;
                                        (*Iter).Display(file_stream3);
                                        file_stream3<<endl;
                                };
                                --Iter;


                        };
                };
                file_stream3.close();


        }

/*!
   \brief Update name list for gnuplot_link
 */
        void Update_files(PzG::GnuplotLink& link){
                link.DeleteAllNames();
                link.AddFilename("Drones.dat",PzG::LS_CONTINUOUS,1); //rysowanie linia o grubosci 2
                link.AddFilename("Obstacles.dat",PzG::LS_CONTINUOUS,1);  //rysowanie linia o grubosci 2
                link.AddFilename("Chosen.dat",PzG::LS_CONTINUOUS,4);    //rysowanie linia o grubosci 2
                link.AddFilename("Trace.dat",PzG::LS_CONTINUOUS,2);
                link.SetDrawingMode(PzG::DM_3D);   //ustawienie trybu rysowania 3D


        }


/*!
   \brief Usuwa wybray obiekt z listy
   \param chosen wskaznik na obiekt do usuniecia
 */
        void delete_ob(std::shared_ptr<Object3D> &chosen){
                std::list<std::shared_ptr<Object3D> >::iterator Iter_szukane;
                for(std::list<std::shared_ptr<Object3D> >::iterator Iter = obstacles.begin( ); Iter != obstacles.end( ); ++Iter) {
                        if((*Iter)==chosen) {
                                Iter_szukane=Iter;
                        };
                };
                Iter_szukane->reset();
                obstacles.erase(Iter_szukane);
        }


/*!
   \brief Wyswietla liste obiektow dostepnych od wyboru
   \return Ilosc wszystkic obiektow
 */
        int enlist(){
                int i=0;
                for (std::list<std::shared_ptr<Object3D> >::iterator Iter = obstacles.begin( ); Iter != obstacles.end( ); ++Iter) {
                        ++i;
                        cout<<"    "<<i<<". "; if((*Iter)->ID()>=9000) {cout<<" DRONE   "; }else if((*Iter)->ID()>=1000) {cout<<" WINDOW  "; }else{cout<<" OBSTACLE"; }; cout<<std::setw(5)<<(*Iter)->ID()<<"  ";
                        (*Iter)->name(cout); cout<<"      "; (*Iter)->Read_position(cout);
                        cout<<endl;

                };
                return i;
        }

/*!
   \brief Wyszukuje na liscie obiekt o zadanym numerze
   \param i numer obiektu w liscie
   \param chosen wskaznik na obiekt
   \return wartosc true jesli sie powiodlo
 */
        bool give_by_iter (int i,std::shared_ptr<Object3D> &chosen){
                auto iter = obstacles.begin();
                for(int j=0; j<i; ++j) {
                        if(iter==obstacles.end()) {
                                return 0;
                        };
                        ++iter;
                };
                chosen= (*iter);
                return 1;
        }

/*!
   \brief Wyszukuje na liscie obiekt o zadanym numerze
   \param ID numer ID obiektu w liscie
   \param chosen wskaznik na obiekt
   \return wartosc true jesli sie powiodlo
 */
        bool give_by_ID (int ID,std::shared_ptr<Object3D> &chosen){
                for(std::list<std::shared_ptr<Object3D> >::iterator Iter = obstacles.begin( ); Iter != obstacles.end( ); ++Iter) {
                        if((*Iter)->ID()==ID) {
                                chosen=(*Iter);
                                return 0;
                        };
                };
                return 1;
        }

}; // Koniec klasy scena

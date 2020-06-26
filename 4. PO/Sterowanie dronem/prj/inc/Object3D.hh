/*!
   \file Object3D.hh
   \brief Zawiera klase i metody obslugujace scene
   \author Patryk Szydlik
   \date 20.04.19
 */
#pragma once
#define END_OF_DATA -10
#define FPS 10 /** Ilosc klatek na sekunde*/

//#include "Observer.hh"
#include <memory>
#include <list>
#include "Prism.hh"
/*!
 * \brief Klasa modeluje pojecie sceny zawierajacej 5 graniastoslupow
 */
class Object3D {
protected:
        NEW_Vector position; /*!< Wektory pozycji obiektów */
        NEW_Matrix rotation[2]; /*!< Macierze rotacji obiektów */
        int _ID;
        char _name[20];
        //  static std::list<Observer *> observers; // obserwatorzy
public:
        Object3D(){

        }
        virtual ~Object3D(){

        }

/*!
   \brief Wyswietla nazwe oraz ID obiektu
   \param stream - strumien wyslania napisu
 */
        void name(std::ostream &stream) const {
                stream<<std::setw(20)<<this->_name;;
        }

/*!
   \brief Kopiuje parametry obiektu
   \param copied referencja do obiektu kopiowanego
 */
        void Copy_param(Object3D &copied){
                copied.position=position;
                copied.rotation[0]=rotation[0];
                copied.rotation[1]=rotation[1];
                for(int i=0; i<20; ++i) {
                        copied._name[i]=_name[i];
                };
        }
        /*!
           \brief Wyswietla nazwe oraz ID obiektu
           \param stream - strumien wyslania napisu
         */
        int ID() const {
                return this->_ID;
        }




/*!
   \brief Pozwala zmienic nazwe obiektu
   \param newname nowa nazwa
 */
        void ChangeName(const char newname[20]){
                for(int i=0; i<20; ++i) {
                        _name[i]=newname[i];
                };
        }
/*!
   \brief Wyswietla wspolrzedne wierzcholkow obiektu
   \param Strm strumien wyjsciowy do zapisu
   \return Brak
 */
        virtual void Display(std::ostream &Strm) {
        }

        /*!
           \brief Wyswietla wspolrzedne wierzcholkow obiektu
           \param Strm strumien wyjsciowy do zapisu
           \return Brak
         */
        virtual void Show_Size(std::ostream &Strm) const {
        }
/*!
   \brief Zmienia macierz obrotu. Mnozenie macierzy rotacji.
   \param M nowa macierz obrotu
   \return Brak
 */
        virtual void Turn(const NEW_Matrix &M){
                rotation[0]=rotation[1];
                rotation[1]=M*rotation[0];
        }
/*!
   \brief Cofa ostatni obrót. Przy pomocy poprzedniej macierzy obrotu.
   \return Brak
 */
        void Turn_undo(){
                rotation[1]=rotation[0];
        }
/*!
   \brief Zmienia wektor pozycji obiektu. Przemieszcza obiekt.
   \param V wektor przemieszczenia
   \return Brak
 */
        void Move(const NEW_Vector &V){
                position=position+V;
        }

        /*!
           \brief Wyswietla aktualna pozycje obiektu
           \return Brak
         */
        void Read_position(std::ostream &Strm) const {
                Strm<<std::setw(6)<<position[0]<<" "<<std::setw(6)<<position[1]<<" "<<std::setw(6)<<position[2];;
        }
        /*!
           \brief Wyswietla wartosci macierzy rotacji
           \return Brak
         */
        void Read_rotation() const {
                cout<<"Matrix of previous rotation : "<<endl;
                rotation[0].Display();
                cout<<"Matrix of new rotation : "<<endl;
                rotation[1].Display();

        }

/*!
   \brief Zwraca pozycje srodka obiektu
   \return Zwraca wektor pozycji
 */
        NEW_Vector center() const {
                return position;
        }
        /*!
           \brief Zwraca rotacje obiektu
           \return Zwraca macierz rotacji
         */
        virtual NEW_Matrix give_rotation() const {
                return rotation[1];
        }

/*!
   \brief Zapis do pliku
   \param filename strumien plikowy
   \return true gdy sie powiedzie
 */
        virtual bool WriteToFile(string filename){
                return 1;

        }

        /*!
           \brief Sprawdza liste obiektow w poszukiwaniu kolizji
           \param obstacles lista przeszkod
           \return true jesli znalazlo kolizje
         */
        virtual bool Check_Collision(const std::list <std::shared_ptr<Object3D>* >  &obstacles) const {
                return 1;
        }
        /*!
           \brief Sprawdza kolizje z wybranym obiektem
           \param obstacle wybrany obiekt
           \return true jesli jest kolizja
         */
        virtual bool Who_is_there(const Object3D& obstacle) const {
                return 1;
        }
        /*!
           \brief Sprawdza kolizje naszego obiektu z dronem ktory wyslal zapytanie
           \param Your_pos pozycja drona
           \param Your_move przemieszczenie drona
           \param radius promien drona
           \param height wysokosc drona
           \return true jesli doszlo do kolizji
         */
        virtual bool Is_This_Sit_Taken(const NEW_Vector &Your_pos,const NEW_Vector Your_move, float radius, float height) {
                return 1;
        }
        /*!
           \brief Zwraca promien obiektu
           \return Wartosc promienia
         */
        virtual float Your_Size() const {
                return 1;
        }
/*
        static void Subscribe(const Observer* new_obsrvr){
                observers.push_back(new_obsrvr);
        }
        static void unSubscribe (const Observer* chosen){
                for(std::list<Observer*>::iterator iter=observers.begin(); iter!=observers.end(); ++iter) {
                        if(*iter==chosen) {
                                observers.erase(iter);
                        }
                }
        }
        virtual void Call_to_observers(datatype created_obj,operation done){
                for(std::list<Observer*>::iterator iter=observers.begin(); iter!=observers.end(); ++iter) {
                        (*iter)->Update_value(created_obj,done);
                };

        }*/
};

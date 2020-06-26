#pragma once
using namespace std;

#include <memory>
#include "Drone.hh"
#include "Obstacle.hh"
#include "Window.hh"


enum ObjectType { ITS_Drone, ITS_Obstacle,ITS_Window};
/*!
 * \brief Klasa modeluje pojecie Fabryki
 */
class Fabric;
/*!
 * \brief Klasa modeluje singleton dla klasy Fabric
 */
class Fabric_Ptr : private shared_ptr<Fabric>{
        friend class Fabric;

        void CreateFabric();
        void DeleteFabric(){
                this->reset(static_cast<Fabric*>(nullptr));
        }
public:
        /*!
           \brief Przeciazenie operatora dereferencji
         */
        Fabric* operator -> (){
                return &**this;
        }
};


/*!
 * \brief Klasa modeluje pojecie Fabryki
 */
class Fabric {
        static Fabric_Ptr _Fabric; /*!< wskaznik singleton fabryki */
public:
        /*!
           \brief Zwraca wskaznik fabryki
         */
        static Fabric_Ptr& UseFabric(){
                return _Fabric;
        }
        /*!
           \brief Tworzy nowa fabryke
         */
        static void CreateFabric(){
                _Fabric.CreateFabric();
        }
        /*!
           \brief Usuwa fabryke
         */
        static void DeleteFabric(){
                _Fabric.DeleteFabric();
        }
/*!
   \brief Tworzy nowy obiekt
   \param type Typ obiektu
   \param size_param wymiary obiektu
   \param name nazwa obiektu
   \return Zwraca wskaznik wspoldzielony na obiekt
 */
        shared_ptr<Object3D> CreateObject(ObjectType type, float size_param[5], char name[20]) const {
                shared_ptr<Object3D> new_object;
                switch(type) {
                case ITS_Drone:
                {
                        Drone *dr_ptr = new Drone(size_param[0],size_param[1],size_param[2],size_param[3],size_param[4],name);
                        new_object.reset(dr_ptr);
                        return new_object;
                }
                break;
                case ITS_Window:
                {
                        Window *wnd_ptr = new Window(size_param[0],size_param[1],name);
                        new_object.reset(wnd_ptr);
                        return new_object;
                }
                break;
                case ITS_Obstacle:
                {
                        Obstacle *obs_ptr = new Obstacle(size_param[0],size_param[1],size_param[2],name);
                        new_object.reset(obs_ptr);
                        return new_object;
                }
                break;
                };
                return new_object;
        }
        ~Fabric(){
        }

private:
        friend class Fabric_Ptr;
        Fabric(){
        }
        Fabric(const Fabric &)=delete;
};

void Fabric_Ptr::CreateFabric() {
        if (!*this) reset(new Fabric());
}

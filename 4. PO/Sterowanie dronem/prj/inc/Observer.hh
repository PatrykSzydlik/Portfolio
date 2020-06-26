#pragma once
#include "Object3D.hh"
enum datatype {drones,windows,obstacles,objects};
enum operation {deleted, created, copied};
class Observer {
        datatype Observed;
        int Existing_objects; ///Ile jest teraz
        int Created_objects;  /// Ile istnieje od początku
        int Number_of_copies; /// Ilosc tworzonych kopii
public:
        Observer(datatype who_to_observe) :
                Observed(who_to_observe),Existing_objects(0),Created_objects(0),Number_of_copies(0)
        {
                Object3D::Subscribe(this);
        }
        ~Observer(){
                Object3D::unSubscribe(this);
        }
        void Update_value(datatype edited, operation done){
                if(edited==Observed) {

                        switch(done) {
                        case deleted:
                                --Existing_objects;
                                break;
                        case created:
                                ++Existing_objects;
                                ++Created_objects;
                                break;
                        case copied:
                                ++Existing_objects;
                                ++Created_objects;
                                ++Number_of_copies;
                                break;
                        };
                };
        }
};

/*!
   \file list.hh
   \brief Plik z klasą listy
   \author Patryk Szydlik
   \date 24.04.20
 */
#pragma once


/*!
\brief Klasa implementująca element listy jendokierunkowej
*/
template<typename DATA>
class listElem{
    public:
        DATA x;
        listElem * next=NULL;

        listElem(DATA newData){
            x=newData;
        };

        void display(){
            std::cout<<x;
        }

        DATA value(){
            return x;
        }
};


/*!
\brief Klasa implementująca stos na liście jednokierunkowej
*/
template<typename DATA>
class list{
    private:
        listElem<DATA> * head=NULL;
    public:
        int size=0; 

        listElem<DATA> * operator [](int iter){  // DZIAŁA
            listElem<DATA> * current = head;
            if(iter<0 || iter>=size){
                std::cerr<<"ERROR  list.hh L34 : Iter "<<iter<<" out of range \n";
                return nullptr;
            };
            for(int i=0; i < iter; i++){
                current=current->next;
            };
            return current;
        }

        void insertFirst(DATA newData){ // DZIAŁA
            if(size>0){
                listElem<DATA> * newElem = new listElem<DATA>(newData);
                newElem->next=head;
                head=newElem;
                size++;
            }else{
                head=new listElem<DATA>(newData);
                size++;
            }
        }

        void removeIter(int iter){ // DZIAŁA
            listElem<DATA> * elemBefore; 
            listElem<DATA> * elemAfter;
            if(size==0){
                std::cerr<<"    size "<<size<<" there's nothing to delete "<<"\n";
            }else{
                if(iter==0){
                    elemAfter=head->next;
                    delete head;
                    head = elemAfter;
                    size--;
                }else{
                    if(iter<0 || iter>=size){
                        std::cerr<<"ERROR  list.hh L100 : Iter "<<iter<<" out of range \n";
                    }else{
                        elemBefore = (*this)[iter-1];
                        if(elemBefore->next!=nullptr){
                            elemAfter = elemBefore->next->next;
                            delete elemBefore->next;
                            elemBefore->next=elemAfter;
                            size--;
                        };
                    };
                };
            };
        }

        void removeFirst(){ //  DZIAŁA
            removeIter(0);
        }


        void display(){  // DZIAŁA
            for(int i=0; i<size; i++){
                (*this)[i]->display();
                std::cout<<" \n";
            }
        }

        int Size(){
            return size;
        }

};
/*!
   \file heap.hh
   \brief Plik z klasą kopca
   \author Patryk Szydlik
   \date 21.04.20
 */

#pragma once


/*!
\brief Klasa implementująca element kopca
*/
template<typename KEY, typename DATA>
class HeapElem{
    public:
        KEY  k;
        DATA  x;
       
    

        HeapElem<KEY,DATA> * father=nullptr;
        HeapElem<KEY,DATA> * leftSon=nullptr;
        HeapElem<KEY,DATA> * rightSon=nullptr;

        HeapElem(KEY newK, DATA  newX){
            k=newK;
            x=newX;
        }

        HeapElem(KEY newK, DATA newX, HeapElem<KEY,DATA> * newFather){
            k=newK;
            x=newX;
            father=newFather;
        }

        KEY key(){
            return k;
        }

        void checkValue(KEY  & probeK, DATA & probeX){
            probeK=k;
            probeX=x;
        }

        void takeValue(KEY  & probeK, DATA  & probeX){
            probeK=k;
            probeX=x;
        }

        int operator < (HeapElem<KEY,DATA> & compared){
            if(this->k < compared.k){
                return 1;
            }else{
                return 0;
            };
        }
        int operator <= (HeapElem<KEY,DATA> & compared){
            if(this->k <= compared.k){
                return 1;
            }else{
                return 0;
            }
        }
        int operator > (HeapElem<KEY,DATA> & compared){
            if(this->k > compared.k){
                return 1;
            }else{
                return 0;
            }
        }
        int operator >= (HeapElem<KEY,DATA> & compared){
            if(this->k >= compared.k){
                return 1;
            }else{
                return 0;
            }
        }
        int operator == (HeapElem<KEY,DATA> & compared){
            if(this->k == compared.k){
                return 1;
            }else{
                return 0;
            }
        }

        void display(){
            std::cout<<k<<"->";
            x->display(); 
        }

};


/*!
\brief Klasa implementująca kolejkę priorytetową na kopcu
*/

template<typename KEY, typename DATA>
class Heap{
    public:
        HeapElem<KEY,DATA> * head = NULL;
        int size=0;
        
        

        void downheap(HeapElem<KEY,DATA> * firstElem){ //Działa
            HeapElem<KEY,DATA> * nextElem=nullptr;
            int loop=1;

            do{
                if(firstElem->leftSon!=nullptr){
                    if(firstElem->rightSon==nullptr){
                        nextElem=firstElem->leftSon;
                    }else if(firstElem->rightSon!=nullptr){
                        if(firstElem->leftSon->k >= firstElem->rightSon->k){
                            nextElem=firstElem->rightSon;
                        }else{
                            nextElem=firstElem->leftSon;
                        };
                    };
                    if(firstElem->k > nextElem->k){
                        swap(firstElem,nextElem);
                    }else{
                        loop=0;
                    };
                }else{
                    loop=0;
                };
            }while(loop);
        }

        void upheap(HeapElem<KEY,DATA> * lastHeapElem){ //Działa
            while(lastHeapElem->father!=nullptr){
                if(lastHeapElem->k < lastHeapElem->father->k){
                    swap(lastHeapElem,lastHeapElem->father);
                }else{
                    lastHeapElem=lastHeapElem->father;
                };
            }
        }

        
        HeapElem<KEY,DATA> * findElem(int position){ //Działa
            HeapElem<KEY,DATA> * newHeapElem;
            if(position==0 || position==1){
                return head;
            };
            newHeapElem=findElem(position/2);
            if(position%2){
                newHeapElem=newHeapElem->rightSon;
            }else{
                newHeapElem=newHeapElem->leftSon;
            }
            return newHeapElem;
        }


        HeapElem<KEY,DATA> * findNewFather(){ // Działa
            int position = size+1;
            HeapElem<KEY,DATA> * newHeapElem=findElem(position/2);
            return newHeapElem;
        }

        HeapElem<KEY,DATA> * findLastSon(){ // Działa
            int position = size;
            HeapElem<KEY,DATA> * newHeapElem=findElem(position);
            return newHeapElem;
        }


        void swap(HeapElem<KEY,DATA> * first, HeapElem<KEY,DATA> * second ){ // Działa
            HeapElem<KEY,DATA> * tempFather=first->father;
            HeapElem<KEY,DATA> * tempLeftSon=first->leftSon;
            HeapElem<KEY,DATA> * tempRightSon=first->rightSon;


            // NIGDY NIE WARTO ZADAWAC PYTAN JAK DZIALAJA PONIZSZE WARUNKI
            // PRACOWALEM NAD NIMI TAK DLUGO ZE MUSZA DZIALAC
            // TLUMACZENIE DLACZEGO ZAJELOBY WIELOKROTNIE DLUZEJ NIZ ZNALEZIENIE ROZWIAZANIA
            // CO SAMO W SOBIE BYLO CZASOCHLONNE

            if(first->father==second){
                if(second->leftSon==first){  // PRZYPADEK 3

                    if(second->father!=nullptr){
                        if(second->father->leftSon==second){
                            second->father->leftSon=first;
                        }else{
                            second->father->rightSon=first;
                        };
                    };
                    first->father=second->father;

                    first->leftSon=second;
                    second->father=first;

                    first->rightSon=second->rightSon;
                    if(second->rightSon!=nullptr){second->rightSon->father=first;};

                    second->leftSon=tempLeftSon;
                    if(tempLeftSon!=nullptr){tempLeftSon->father=second;};
                    
                    second->rightSon=tempRightSon;
                    if(tempRightSon!=nullptr){tempRightSon->father=second;};


                }else if(second->rightSon==first){ // PRZYPADEK 4


                    if(second->father!=nullptr){
                        if(second->father->leftSon==second){
                            second->father->leftSon=first;
                        }else{
                            second->father->rightSon=first;
                        };
                    };
                    first->father=second->father;

                    
                    first->rightSon=second;
                    second->father=first;

                    first->leftSon=second->leftSon;
                    if(second->leftSon!=nullptr){second->leftSon->father=first;};

                    second->leftSon=tempLeftSon;
                    if(tempLeftSon!=nullptr){tempLeftSon->father=second;};
                    
                    second->rightSon=tempRightSon;
                    if(tempRightSon!=nullptr){tempRightSon->father=second;};

                }
            }else if(second->father==first){
                if(first->leftSon==second){  // PRZYPADEK 1

                    if(first->father!=nullptr){
                        if(first->father->leftSon==first){
                            first->father->leftSon=second;
                        }else{
                            first->father->rightSon=second;
                        };
                    };
                    second->father=first->father;

                    first->leftSon=second->leftSon;
                    if(second->leftSon!=nullptr){second->leftSon->father=first;};

                    second->leftSon=first;
                    first->father=second;

                    first->rightSon=second->rightSon;
                    if(second->rightSon!=nullptr){second->rightSon->father=first;};

                    if(tempRightSon!=nullptr){tempRightSon->father=second;};
                    second->rightSon=tempRightSon;

                }else if(first->rightSon==second){  // PRZYPADEK 2{

                    if(first->father!=nullptr){
                        if(first->father->leftSon==first){
                            first->father->leftSon=second;
                        }else{
                            first->father->rightSon=second;
                        };
                    };
                    second->father=first->father;

                    first->rightSon=second->rightSon;
                    if(second->rightSon!=nullptr){second->rightSon->father=first;};

                    first->leftSon=second->leftSon;
                    if(second->leftSon!=nullptr){second->leftSon->father=first;};

                    second->rightSon=first;
                    first->father=second;

                    second->leftSon=tempLeftSon;
                    if(tempLeftSon!=nullptr){tempLeftSon->father=second;};

                }
            }else{
                // Rodzina pierwszego musi poznac drugiego
                if(first->father!=nullptr){
                    if(first->father->leftSon==first){
                        first->father->leftSon=second;
                    }else{
                        first->father->rightSon=second;
                    };
                };
                if(first->leftSon!=nullptr){first->leftSon->father=second;};
                if(first->rightSon!=nullptr){first->rightSon->father=second;};

                // Rodzina drugiego poznaje pierwszego
                if(second->father!=nullptr){
                    if(second->father->leftSon==second){
                        second->father->leftSon=first;
                    }else{
                        second->father->rightSon=first;
                    };
                };
                if(second->leftSon!=nullptr){second->leftSon->father=first;};
                if(second->rightSon!=nullptr){second->rightSon->father=first;};


                // Pierwszy poznaje rodzine drugiego
                first->father=second->father;
                first->leftSon=second->leftSon;
                first->rightSon=second->rightSon;

                // Drugi poznaje rodzine pierwszego
                second->father=tempFather;
                second->leftSon=tempLeftSon;
                second->rightSon=tempRightSon;
        };
        
            if(first->father==nullptr){head=first;};
            if(second->father==nullptr){head=second;};
        }

    public:
        ~Heap(){
                if(head!=nullptr){ 
                    delete head;
                };
            }
            
        HeapElem<KEY,DATA> * insert(KEY  k, DATA  x){  // Działa
            HeapElem<KEY,DATA> * newHeapElem= new HeapElem<KEY,DATA>(k,x);
            if(size==0){
                head=newHeapElem;
                size++;
            }else{
            HeapElem<KEY,DATA> * lastHeapElem=findNewFather();
            newHeapElem->father=lastHeapElem;
            
            if(lastHeapElem->leftSon==nullptr){
                lastHeapElem->leftSon=newHeapElem;
            }else if(lastHeapElem->rightSon==nullptr){
                lastHeapElem->rightSon=newHeapElem;
            };
            size++;
            upheap(newHeapElem);
            };

            return newHeapElem;
        }

        void removeMin(KEY  & k, DATA  & x){ //DZIAŁA
            if(size>1){
                HeapElem<KEY,DATA> * lastHeapElem=findLastSon();
                HeapElem<KEY,DATA> * firstHeapElem=head;
                swap(firstHeapElem,lastHeapElem);
                firstHeapElem->takeValue(k,x);
                if(firstHeapElem->father!=nullptr){
                    if(firstHeapElem->father->leftSon==firstHeapElem){
                        firstHeapElem->father->leftSon=nullptr;
                    }else if(firstHeapElem->father->rightSon==firstHeapElem){
                        firstHeapElem->father->rightSon=nullptr;
                    };
                };
                if(firstHeapElem->leftSon!=nullptr){firstHeapElem->leftSon->father=nullptr;};
                if(firstHeapElem->rightSon!=nullptr){firstHeapElem->rightSon->father=nullptr;};
                delete firstHeapElem;
                size--;
                downheap(lastHeapElem);
            }else{
                head->takeValue(k,x);
                delete head;
                head=nullptr;
                size--;
            }
        }

        void min(KEY & k, DATA & x){  // Działa
            head->checkValue(k,x);
        }

        int isEmpty(){  // Działa
            if(size==0){
                return 1;
            }else{
                return 0;
            }
        }

        int getSize(){ // Działa
            return size;
        }

        void replaceKey(HeapElem<KEY,DATA> * h, KEY k){
            if(h->k >= k){
                h->k=k;
                upheap(h);
            }else{
                h->k=k;
                downheap(h);
            }
        }

        void display(){  // DZIAŁĄ
            if(size>0){
                for(int i=1;i<=size;i++){
                    findElem(i)->display();
                    std::cout<<"\n";
                };
            };
        }

};
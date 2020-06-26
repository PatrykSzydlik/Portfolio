/*!
   \file heapsort.hh
   \brief Zawiera algorytm sortowania przez kopcowanie
   \author Patryk Szydlik
   \date 19.03.2020
 */
#pragma once

/*!
\brief Funkcja tworząca kopiec na bazie tablicy
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku fragmentu tablicy
\param[in] last_ind - indeks końca fragmentu tablicy
*/
template<typename DATATYPE>
void make_heap(DATATYPE * el_tab, int first_ind , int last_ind){
  first_ind=first_ind-1;
    for(int i=2;i<=last_ind-first_ind;i++){
      int son_ind=i;
      int father_ind=son_ind/2;
      DATATYPE son_value=el_tab[first_ind+son_ind];
      DATATYPE father_value=el_tab[first_ind+father_ind];
      while(father_ind>0 && father_value <= son_value){
        el_tab[first_ind+son_ind]=father_value;
        son_ind = father_ind;       // Rodzic tez jest dzieckiem
        father_ind = son_ind / 2;   // Znajdz rodzicow rodzica
        father_value=el_tab[first_ind+father_ind];
      };
      el_tab[first_ind+son_ind] = son_value;
  };
}

/*!
\brief Funkcja przywracająca własność kopca metodą downheap
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku fragmentu tablicy
\param[in] last_ind - indeks końca fragmentu tablicy
*/
template<typename DATATYPE>
void down_heap(DATATYPE * el_tab, int first_ind , int last_ind){
  int size=last_ind-first_ind;  //19
  first_ind=first_ind-1; // -1
  int key_ind=1;
  int new_key_ind;
  do{
    new_key_ind=key_ind;
    if(2*new_key_ind<=size && el_tab[first_ind + 2*new_key_ind] > el_tab[first_ind+key_ind]){
      key_ind=2*new_key_ind;
    };
    if(2*new_key_ind+1<=size && el_tab[first_ind + 2*new_key_ind + 1] > el_tab[first_ind + key_ind]){
      key_ind=2*new_key_ind + 1;
    };
    swap(el_tab,first_ind+key_ind,first_ind+new_key_ind);
  }while(key_ind!=new_key_ind);
}

/*!
\brief Funkcja sortująca fragment tablicy metodą sortowania przez kopcowanie
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku sortowanego fragmentu tablicy
\param[in] last_ind - indeks końca sortowanego fragmentu tablicy
*/
template<typename DATATYPE>
void heapsort(DATATYPE * el_tab, int first_ind , int last_ind){
  //std::cout<<"-\n";
  make_heap(el_tab,first_ind,last_ind);
  for(int i=last_ind;i>first_ind;i--){
    swap(el_tab,first_ind,i);
    down_heap(el_tab,first_ind,i);
  };
}
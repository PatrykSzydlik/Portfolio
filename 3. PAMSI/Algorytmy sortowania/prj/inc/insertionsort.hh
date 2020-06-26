/*!
   \file insertionsort.hh
   \brief Zawiera algorytm sortowania przez wstawianie
   \author Patryk Szydlik
   \date 19.03.2020
 */
#pragma once

/*!
\brief Funkcja sortująca fragment tablicy metodą sortowania przez wstawianie
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku sortowanego fragmentu tablicy
\param[in] last_ind - indeks końca sortowanego fragmentu tablicy
*/
template<typename DATATYPE>
void insertionsort(DATATYPE * el_tab, int first_ind , int last_ind){
    //std::cout<<"\n\n            INSERTION SORT\n\n";
    for (int i = first_ind+1; i <= last_ind; i++) { 
        int key = el_tab[i]; 
        int j = i-1; 

        while (j >= first_ind && el_tab[j] > key){ 
            el_tab[j+1] = el_tab[j]; 
            j = j-1; 
        } 
        el_tab[j+1] = key; 
   } 
}

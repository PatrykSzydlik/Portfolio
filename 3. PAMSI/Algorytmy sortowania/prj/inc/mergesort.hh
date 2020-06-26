/*!
   \file mergesort.hh
   \brief Zawiera algorytm sortowania przez scalanie
   \author Patryk Szydlik
   \date 18.03.2020
 */
#pragma once

#include <unistd.h>

/*!
\brief Funkcja scalająca 2 posortowane fragmenty tablicy
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku sortowanego fragmentu tablicy
\param[in] median - punkt środkowy będący punktem podziału fragmentu tablicy
\param[in] last_ind - indeks końca sortowanego fragmentu tablicy
*/
template<typename DATATYPE>
void merge(DATATYPE * el_tab, int first_ind ,int median, int last_ind){
    int first_half_size=median-first_ind+1;
    int second_half_size=last_ind-median;
    DATATYPE * first_half = new DATATYPE[first_half_size];
    DATATYPE * second_half = new DATATYPE[second_half_size];

    for(int i=0;i<first_half_size;i++){
        first_half[i]=el_tab[first_ind+i];
    }
    for(int i=0;i<second_half_size;i++){
        second_half[i]=el_tab[median+i+1];
    }
    int i=0;
    int j=0;
    while(i<first_half_size && j<second_half_size){     // Rozpatrujemy przypadek gdy w obu polowach sa jeszcze elementy
            if(first_half[i]<=second_half[j]){
                el_tab[first_ind+i+j]=first_half[i];                // Gdy elemenent pierwszej tablicy jest mniejszy lub rowny
                i++;
            }else{
                el_tab[first_ind+i+j]=second_half[j];               // Gdy element drugiej polowy jest mniejszy
                j++;
            };
    };
    while(i<first_half_size){                         // Przepisujemy pozostale z pierwszej listy
        el_tab[first_ind+i+j]=first_half[i];     
        i++;
    };
    while(j<second_half_size){                         // Przepisujemy pozostale z pierwszej listy
        el_tab[first_ind+i+j]=second_half[j];   
        j++;
    };
    delete first_half;
    delete second_half;
}

/*!
\brief Funkcja sortująca fragment tablicy metodą sortowania przez scalanie
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku sortowanego fragmentu tablicy
\param[in] last_ind - indeks końca sortowanego fragmentu tablicy
*/
template<typename DATATYPE>
void mergesort(DATATYPE * el_tab, int first_ind , int last_ind){
    if(first_ind<last_ind-1){
        int median=(first_ind+last_ind)/2;
        mergesort(el_tab,first_ind,median);
        mergesort(el_tab,median+1,last_ind);
        merge(el_tab,first_ind,median,last_ind);
    }else{
        int median=(first_ind+last_ind)/2;
        merge(el_tab,first_ind,median,last_ind);
    };
}
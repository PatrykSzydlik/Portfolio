/*!
   \file quicksort.hh
   \brief Zawiera algorytm sortowania szybkiego
   \author Patryk Szydlik
   \date 11.03.2020
 */
#pragma once

/*!
\brief Funkcja zamieniająca miejscami elementy tablicy
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks pierwszego elementu do zamiany
\param[in] second_ind - indeks drugiego elementu do zamiany
*/
template<typename DATATYPE>
void swap(DATATYPE * el_tab, int first_ind , int second_ind){
    DATATYPE temp_value=el_tab[first_ind];
    el_tab[first_ind]=el_tab[second_ind];
    el_tab[second_ind]=temp_value;
}

/*!
\brief Funkcja wybiera punkt podziału fragmentu tablicy
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku dzielonego fragmentu tablicy
\param[in] last_ind - indeks końca dzielonego fragmentu tablicy
\return indeks elementu do podziału
*/
template<typename DATATYPE>
int choose_split_point(DATATYPE * el_tab,int first_ind, int last_ind){
    int median_ind=(first_ind+last_ind)/2;
    int split_point_ind;

    if(el_tab[first_ind]<=el_tab[last_ind]){
        if(el_tab[median_ind]<=el_tab[first_ind]){
            split_point_ind=first_ind;
        }else if(el_tab[median_ind]>el_tab[last_ind]){
            split_point_ind=last_ind;
        }else{
            split_point_ind=median_ind;
        };
    }else{
        if(el_tab[median_ind]>el_tab[first_ind]){
            split_point_ind=first_ind;
        }else if(el_tab[median_ind]<=el_tab[last_ind]){
            split_point_ind=last_ind;
        }else{
            split_point_ind=median_ind;
        };
    };
    
    return split_point_ind;
}

/*!
\brief Funkcja dzieli tablice według wybranego klucza
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku dzielonego fragmentu tablicy
\param[in] last_ind - indeks końca dzielonego fragmentu tablicy
\return indeks elementu między podzielonymi częściami
*/
template<typename DATATYPE>
int split_tab(DATATYPE * el_tab, int first_ind , int last_ind){
    int split_ind=choose_split_point(el_tab,first_ind,last_ind);
    DATATYPE split_value=el_tab[split_ind];
    swap(el_tab,split_ind,last_ind);
    int current_ind=first_ind;
    for(int i=first_ind;i<last_ind;i++){
        if(el_tab[i]<split_value){
            swap(el_tab,i,current_ind);
            current_ind++;
        };
    };
    swap(el_tab,current_ind,last_ind);
    return current_ind;
}

/*!
\brief Funkcja sortująca fragment tablicy metodą sortowania szybkiego
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku sortowanego fragmentu tablicy
\param[in] last_ind - indeks końca sortowanego fragmentu tablicy
*/
template<typename DATATYPE>
void quicksort(DATATYPE * el_tab, int first_ind , int last_ind){
    while(first_ind<last_ind){
        int split_ind=split_tab(el_tab,first_ind,last_ind);
        if((split_ind-first_ind) <= (last_ind-split_ind)){
            quicksort(el_tab,first_ind,split_ind-1);
            first_ind=split_ind+1;
        }else{
            quicksort(el_tab,split_ind+1,last_ind);
            last_ind=split_ind-1;
        };
        
    };
}
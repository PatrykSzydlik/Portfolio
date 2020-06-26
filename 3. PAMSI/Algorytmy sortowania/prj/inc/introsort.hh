/*!
   \file introsort.hh
   \brief Zawiera algorytm sortowania introspektywnego (hybrydowe)
   \author Patryk Szydlik
   \date 19.03.2020
 */
#pragma once

/*!
\brief Funkcja sortująca fragment tablicy metodą sortowania introspektywnego
\param[in] el_tab - wskaźnik na tablice
\param[in] first_ind - indeks początku sortowanego fragmentu tablicy
\param[in] last_ind - indeks końca sortowanego fragmentu tablicy
\param[in] depthLimit - limit głębokości rekursji
*/
template<typename DATATYPE>
void introsort(DATATYPE * el_tab, int first_ind , int last_ind, int depthLimit){ 
    int size = last_ind-first_ind; 
    //std::cout<<"\n\n INTRO SORT\n\n";
    // Ilosc elementow optymalna dla uzycia sortowania przez wstawianie
    if (size < 16){                   
        insertionsort(el_tab, first_ind, last_ind); 
    
     // Po przekroczeniu depthLimit algorytm uzywa sortowania przez kopcowanie 
    }else if (depthLimit == 0) {          
       heapsort(el_tab,first_ind,last_ind);
    }else{
  
    // W warunkach optymalnych kontynuuj sortowanie szybkie

        while(first_ind<last_ind){
            int split_ind=split_tab(el_tab,first_ind,last_ind);
            if((split_ind-first_ind) <= (last_ind-split_ind)){
                introsort(el_tab,first_ind,split_ind-1,depthLimit-1);
                first_ind=split_ind+1;
            }else{
                introsort(el_tab,split_ind+1,last_ind,depthLimit-1);
                last_ind=split_ind-1;
            };
            
        };

    };
    
    
  
} 
/*!
   \file random_data_generation.hh
   \brief Zawiera funkcje przygotowujące tablice losowych liczb do testow sortowania
   \author Patryk Szydlik
   \date 12.03.2020
 */
#pragma once

#include <stdlib.h>
#include <limits> 

/*!
\brief Funkcja sprawdzająca czy tablica jest posortowana
\param[in] test_data - tablica do sprawdzenia
\param[in] amount_of_data - rozmiar tablicy
\return Ilość wystąpień błędnej kolejności elementów
*/
template<typename DATATYPE>
int check_if_sorted(DATATYPE * test_data, int amount_of_data){
     int response=0;
     for(int i=0;i<amount_of_data-1;i++){
         if(test_data[i]>test_data[i+1]){response++;};
     };
     return response;
}

/*!
\brief Funkcja losująca kolejną liczbę po last_value większą o maksymalnie difference
\param[in] last_value - poprzednia wartość losowa
\param[in] difference - maksymalny wzrost nowej wartości od poprzedniej 
\return Nowo wylosowana liczba
*/
template<typename DATATYPE>
DATATYPE increasing_RNG (DATATYPE last_value , DATATYPE difference){
    DATATYPE new_value;
    if(difference>0.00001){
        new_value=last_value + (rand() % difference);
    }else{
        new_value=last_value;
    }
    return new_value;
}

/*!
\brief Funkcja losująca liczbę z przedziału lowest_value - highest_value
\param[in] lowest_value - najmniejsza wartość do wylosowania
\param[in] highest_value - największa wartość do wylosowania
\return Nowo wylosowana liczba
*/
template<typename DATATYPE>
DATATYPE limited_RNG (DATATYPE lowest_value , DATATYPE highest_value){
    DATATYPE diff=highest_value/2-lowest_value/2;
    if(diff>std::numeric_limits<DATATYPE>::max()/2){
        diff = std::numeric_limits<DATATYPE>::max();
    }else{
        diff = 2*diff;
    }
    DATATYPE new_value=lowest_value + (rand() % diff );
    return new_value;
}


/*!
\brief Funkcja generująca tablicę losowych liczb
\param[in] test_data_ptr - wskaźnik na wskaźnik będący początkiem tablicy
\param[in] amount_of_data - rozmiar tablicy
\param[in] percent_already_sorted - procent danych, który ma być posortowany
*/
template<typename DATATYPE>
 void generate_test_data(DATATYPE ** test_data_ptr, int amount_of_data, float percent_already_sorted){
    DATATYPE * test_data=new DATATYPE[amount_of_data];
    DATATYPE lowest_value=std::numeric_limits<DATATYPE>::min();
    DATATYPE highest_value=std::numeric_limits<DATATYPE>::max();
    DATATYPE current_value=lowest_value;
    DATATYPE previous_value=lowest_value;
    DATATYPE difference=(highest_value/amount_of_data-lowest_value/amount_of_data);
    int order_of_elements=1;
    if(percent_already_sorted<0){  // W przypadku ujemnego procenta posortowania oznacza on tablice posortowaną malejąco
        percent_already_sorted=-percent_already_sorted;
        order_of_elements=-1;
    }
    int amount_of_sorted_data=amount_of_data*percent_already_sorted/100;

    for(int i=0; i < amount_of_data ; i++){
        if(i<amount_of_sorted_data){
            difference=(highest_value/(amount_of_data-i)-previous_value/(amount_of_data-i));
            current_value=increasing_RNG(previous_value,difference);
            previous_value=current_value;
        }else{
            current_value=limited_RNG(previous_value,highest_value);
        };
        test_data[i]=order_of_elements*current_value;
    };
    *test_data_ptr=test_data;
}

/*!
\brief Funkcja generująca tablicę losowych liczb z ograniczeniami
\param[in] test_data_ptr - wskaźnik na wskaźnik będący początkiem tablicy
\param[in] amount_of_data - rozmiar tablicy
\param[in] percent_already_sorted - procent danych, który ma być posortowany
\param[in] bottom_limit - najmniejsza dopuszczalna wartośc liczb
\param[in] top_limit - największa dopuszczalna wartość liczb
*/
template<typename DATATYPE>
 void generate_test_data(DATATYPE ** test_data_ptr, int amount_of_data, int percent_already_sorted, DATATYPE bottom_limit, DATATYPE top_limit){
    DATATYPE * test_data=new DATATYPE[amount_of_data];
    DATATYPE lowest_value;
    if(bottom_limit<std::numeric_limits<DATATYPE>::min() && bottom_limit >= top_limit){
    lowest_value=std::numeric_limits<DATATYPE>::min();
    }else{
    lowest_value=bottom_limit;
    };
    DATATYPE highest_value;
    if(top_limit>std::numeric_limits<DATATYPE>::max() && bottom_limit >=top_limit){
    highest_value=std::numeric_limits<DATATYPE>::max();
    }else{
    highest_value=top_limit;
    };
    DATATYPE current_value=lowest_value;
    DATATYPE previous_value=lowest_value;
    DATATYPE difference=(highest_value/amount_of_data-lowest_value/amount_of_data);
    int amount_of_sorted_data=amount_of_data*percent_already_sorted/100;
    for(int i=0; i < amount_of_data ; i++){
        if(i<amount_of_sorted_data){
            difference=(highest_value/(amount_of_data-i)-previous_value/(amount_of_data-i));
            current_value=increasing_RNG(previous_value,difference);
            previous_value=current_value;
        }else{
            current_value=limited_RNG(previous_value,highest_value);
        };
        test_data[i]=current_value;
    };
    *test_data_ptr=test_data;
}

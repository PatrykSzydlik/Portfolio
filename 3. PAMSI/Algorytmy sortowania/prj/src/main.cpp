/*!
   \file main.cpp
   \brief Glowny plik zawierajacy wywolanie menu i funkcji zewnetrznych
   \author Patryk Szydlik
   \date 08.03.20
 */

#include <iostream>
#include <chrono> 
#include "quicksort.hh"
#include "random_data_generation.hh"
#include "mergesort.hh"
#include "insertionsort.hh"
#include "heapsort.hh"
#include "introsort.hh"
#include "time_measurements.hh"

 int main(){
  int data_size[]={10000,50000,100000,500000,1000000};
  float percent_sorted[]={0,25,50,75,95,99,99.7,-100};
  int bottom_limit=-100;
  int top_limit=100;
  int introsort_depth_limit[]={9,11,12,15,16}; // Próg wynosi log2(data_size/X) , gdzie X to granica wykorzystania insertionsort wynosząca tutaj 16 
  int repetitions=100;

  time_measure data_generation_time;
  time_measure quicksort_time;
  time_measure mergesort_time;
  time_measure introsort_time;
  int data_generation_status=0;
  int quicksort_status=0;
  int mergesort_status=0;
  int introsort_status=0;

  for(int k=0;k<8;k++){ // dla różnego posortowania danych
    for(int j=0;j<5;j++){ // dla różnej ilości elementów w tablicy
      for(int l=1;l<=repetitions;l++){

        int * quicksort_data;

        //std::cout<<"\n Repetition number "<<i<<"\n";

        auto start0 = std::chrono::high_resolution_clock::now();
        generate_test_data(&quicksort_data,data_size[j],percent_sorted[k]);
        //generate_test_data(&quicksort_data,data_size,percent_sorted[k],bottom_limit,top_limit);

        int * mergesort_data=new int[data_size[j]];
        for(int i=0;i<data_size[j];i++){
          mergesort_data[i]=quicksort_data[i];
        }

        int * introsort_data=new int[data_size[j]];
        for(int i=0;i<data_size[j];i++){
          introsort_data[i]=quicksort_data[i];
        }

      /*
        int * insertionsort_data=new int[data_size[j]];
        for(int i=0;i<data_size[j];i++){
          insertionsort_data[i]=quicksort_data[i];
        }

        int * heapsort_data=new int[data_size[j]];
        for(int i=0;i<data_size[j];i++){
          heapsort_data[i]=quicksort_data[i];
        }
      */

        auto stop0 = std::chrono::high_resolution_clock::now();
        auto duration0 = std::chrono::duration_cast<std::chrono::microseconds>(stop0 - start0); 
        //std::cout <<"\n     Data generation time: ";
        //std::cout << duration0.count() << " usec \n"; 
        data_generation_time.add_useconds(duration0.count());
      // std::cout<<"\n          Data status before sorting: "<<check_if_sorted(quicksort_data,data_size)<<"\n";
        data_generation_status+=check_if_sorted(quicksort_data,data_size[j]);
        
        /*
        std::cout<<"\nData: ";
        for(int i=0;i<=data_size[j]-1;i++){
          std::cout<<quicksort_data[i];
          if(i!=data_size[j]-1){std::cout<<" , ";}
        }
        std::cout<<"\nSize of data: "<<data_size[j]<<"\n";
        
      */
        // Testy sortowania szybkiego, przez scalanie i introspektywnego

        //std::cout <<"\n     Quicksort execution time: ";
        auto start = std::chrono::high_resolution_clock::now();
        quicksort(quicksort_data,0,data_size[j]-1);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
        //std::cout << duration.count() << " usec \n"; 
        //std::cout<<"\n          Data status after quicksort: "<<check_if_sorted(quicksort_data,data_size[j])<<"\n";

        quicksort_status+=check_if_sorted(quicksort_data,data_size[j]);
        quicksort_time.add_useconds(duration.count());

        //std::cout <<"\n     Mergesort execution time: ";
        auto start2 = std::chrono::high_resolution_clock::now(); 
        mergesort(mergesort_data,0,data_size[j]-1);
        auto stop2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2); 
        //std::cout << duration2.count() << " usec \n"; 
        //std::cout<<"\n          Data status after mergesort: "<<check_if_sorted(mergesort_data,data_size[j])<<"\n";

        mergesort_status+=check_if_sorted(mergesort_data,data_size[j]);
        mergesort_time.add_useconds(duration2.count());

        //std::cout <<"\n     Introsort execution time: ";
        auto start3 = std::chrono::high_resolution_clock::now(); 
        introsort(introsort_data,0,data_size[j]-1,introsort_depth_limit[j]);
        auto stop3 = std::chrono::high_resolution_clock::now();
        auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3); 
        //std::cout << duration3.count() << " usec \n"; 
        //std::cout<<"\n          Data status after introsort: "<<check_if_sorted(introsort_data,data_size[j])<<"\n";

        introsort_status+=check_if_sorted(introsort_data,data_size[j]);
        introsort_time.add_useconds(duration3.count());
        
        //Dodatkowe testy sortowania przez wstawianie i kopcowanie
        
        /*
        std::cout <<"\nHeapsortexecution time: ";
        auto start4 = std::chrono::high_resolution_clock::now();
        heapsort(heapsort_data,0,data_size[j]-1);
        auto stop4 = std::chrono::high_resolution_clock::now();
        auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(stop4 - start4); 
        std::cout << duration4.count() << " usec \n"; 
        std::cout<<"\nData status after heapsort: "<<check_if_sorted(heapsort_data,data_size[j])<<"\n";

        std::cout <<"\nInsertionsort execution time: ";
        auto start5 = std::chrono::high_resolution_clock::now(); 
        insertionsort(insertionsort_data,0,data_size[j]-1);
        auto stop5 = std::chrono::high_resolution_clock::now();
        auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(stop5 - start5); 
        std::cout << duration5.count() << " usec \n"; 
        std::cout<<"\nData status after insertionsort: "<<check_if_sorted(insertionsort_data,data_size[j])<<"\n";
        */

        // Wyswietla dane po sortowaniu wybranym algorytmem
        
        /*  std::cout<<"\nData: ";
        for(int i=0;i<data_size[j];i++){
          std::cout<<introsort_data[i];
          if(i!=data_size[j]-1){std::cout<<" , ";}
        }
        std::cout<<"\nSize of data:"<<data_size[j]<<"\n";
        */
       delete quicksort_data;
       delete mergesort_data;
       delete introsort_data;
      int percent_ready=(500*k+100*j+l)/4000;
       std::cerr<<" k = "<<k<<" j = "<<j<<" l = "<<l<<"\n";
       std::cerr<<"       READY IN      "<<(500*k+100*j+l)/40 <<" % \n";

    }
      // Pelen komplet informacji o sortowaniu
      /*  
        std::cout<<"\n          RESULTS\n";
        std::cout<<"After "<<repetitions<<" repetitions\n";
        std::cout<<"With "<<data_size[j]<<" elements each time\n";
        std::cout<<"Data already sorted in "<<percent_sorted[k]<<" %\n";
        std::cout<<"Overall  data generation time  = ";data_generation_time.display();std::cout<<"\n";
        std::cout<<"                   data status = "<<data_generation_status<<"\n";
        std::cout<<"Overall quicksort sorting time = ";quicksort_time.display();std::cout<<"\n";
        std::cout<<"                   data status = "<<quicksort_status<<"\n";
        std::cout<<"Overall mergesort sorting time = ";mergesort_time.display();std::cout<<"\n";
        std::cout<<"                   data status = "<<mergesort_status<<"\n";
        std::cout<<"Overall introsort sorting time = ";introsort_time.display();std::cout<<"\n";
        std::cout<<"                   data status = "<<introsort_status<<"\n";
        */

       // Zestaw informacji na potrzeby generowania wykresów

        std::cout<<"\n          RESULTS\n";
        std::cout<<"After "<<repetitions<<" repetitions\n";
        std::cout<<"With "<<data_size[j]<<" elements each time\n";
        std::cout<<"Data already sorted in "<<percent_sorted[k]<<" %\n";
        quicksort_time.display_ms();
        mergesort_time.display_ms();
        introsort_time.display_ms();
        quicksort_time.reset();
        mergesort_time.reset();
        introsort_time.reset();
    };
  };
  return 0;
 }
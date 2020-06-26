/*!
   \file main.cpp
   \brief Glowny plik zawierajacy wywolanie menu i funkcji zewnetrznych
   \author Patryk Szydlik
   \date 16.04.20
 */

#include <iostream>
#include <chrono> 
#include <iostream>
#include "time_measurements.hh"
#include "dijkstra.hh"
#include "graphGeneration.hh"
#include "arg.hh"



/*!
\brief Funkcja wyświetlająca ścieżkę wyznaczoną przez algorytm

\param[in] route - zapis ścieżki 
\param[in] start - wierzchołek początkowy
\param[in] size - rozmiar grafu
\param[in] raw - czy wyświetlać surowe dane
\param[in] filename - nazwa pliku do zapisu ścieżki
*/
void displayRoute(vertex *** route, vertex * start, int size, int raw, std::string filename);

/*!
\brief Funkcja wczytująca graf z pliku

\param[in] returnGraph - referencja wskaźnika do grafu
\param[in] filename - nazwa pliku do wczytania grafu
*/
template <typename GRAPH>
vertex * loadFromFile( std::string filename , GRAPH * & returnGraph);


 

int main(int argc, char* argv[]){
  inputArguments settings;
  vertex * startingPoint=nullptr;
  vertex *** route=nullptr;
  graphMatrix * graph2=nullptr;
  graphList * graph=nullptr;
  time_measure graph_generation_time;
  time_measure matrix_Dijkstra_time;
  time_measure list_Dijkstra_time;

//  Poniżej proces interpretacji argumentów wejściowych. W przypadku ich braku program działa na domyślnych parametrach inputArguments

  if(argc >1){
    int error=interpretArguments(settings,argc,argv);
    if(error){
      return error;
    };
  };
  std::cout<<"START OF PROGRAM \n";

//  Pętla powtarzająca eksperyment

  for(int i=1; i<=settings.repetitions;i++){

    std::cout<<"Repetition "<<i<<" \n";

//  Poniżej przypadek gdy wywołano algorytm z opcją generowania grafu wejściowego

    if(settings.generateInput){
      std::cout<<"  Generating data set : nV="<<settings.nVertices<<" full="<<settings.percentFull<<"% start=" <<settings.startingVertex<<" \n";
      auto start0 = std::chrono::high_resolution_clock::now();
      generateGraphToFile(settings.nVertices,settings.startingVertex,settings.percentFull,settings.InputFilename);
      auto stop0 = std::chrono::high_resolution_clock::now();
      auto duration0 = std::chrono::duration_cast<std::chrono::microseconds>(stop0 - start0); 
      graph_generation_time.add_useconds(duration0.count());
    };
   

//  Poniżej przypadek gdy wywołano algorytm z opcją korzystająca z reprezentacji listowej

    if(settings.graphType==1 || settings.graphType==2 ){
      std::cout<<"  List based graph \n";
      std::cout<<"    Loading graph \n";
      startingPoint=loadFromFile(settings.InputFilename, graph);
      std::cout<<"    Dijkstra alghoritm - finding paths \n";

      auto start1= std::chrono::high_resolution_clock::now();

      route=DijkstraDistances(&(*graph),startingPoint);

      auto stop1 = std::chrono::high_resolution_clock::now();
      auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1); 
      list_Dijkstra_time.add_useconds(duration1.count());

      std::string outputFile="./routes/L_"+std::to_string(i)+'_'+settings.OutputFilename;
      std::cout<<"    Displaying route in file "<<outputFile <<" \n";
      displayRoute(route,startingPoint,graph->graphSize(),settings.isRaw,outputFile);
    };

//  Poniżej przypadek gdy wywołano algorytm z opcją korzystająca z reprezentacji macierzowej

    if(settings.graphType==0 || settings.graphType==2 ){
      std::cout<<"  Matrix based graph \n";
      std::cout<<"    Loading graph \n";
      startingPoint=loadFromFile(settings.InputFilename, graph2);
      route=nullptr;
      std::cout<<"    Dijkstra alghoritm - finding paths \n";

      auto start2= std::chrono::high_resolution_clock::now();
      route=DijkstraDistances(&(*graph2),startingPoint);


      auto stop2 = std::chrono::high_resolution_clock::now();
      auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2); 
      matrix_Dijkstra_time.add_useconds(duration2.count());

      std::string outputFile2="./routes/M_"+std::to_string(i)+'_'+settings.OutputFilename;
      std::cout<<"    Displaying route in file "<<outputFile2 <<" \n";
      displayRoute(route,startingPoint,graph2->graphSize(),settings.isRaw, outputFile2);
    };
  };

  // Tutaj następuje zapis czasu do logu wykonania się instancji programu w katalogu ./log/
  std::cout<<" \n\n\n     DATA GENERATION TIME   =   "; graph_generation_time.display_ms();
  if(settings.graphType==0 || settings.graphType==2 ){std::cout<<       "     MATRIX DIJKSTRA TIME   =   "; matrix_Dijkstra_time.display_ms();};
  if(settings.graphType==1 || settings.graphType==2 ){std::cout<<       "     LIST DIJKSTRA TIME     =   "; list_Dijkstra_time.display_ms();};
  std::cout<<"END OF PROGRAM \n";



  // Tutaj następuje zapis czasów wykonywania się algorytmu do pliku time_log.txt
  std::fstream results;
  results.open("time_log.txt",std::fstream::out | std::fstream::app);
  if(results.is_open()){
    results<<" N = "<<settings.nVertices<<" DENS = "<<settings.percentFull<<" \n";
    if(settings.graphType==1 || settings.graphType==2 ){results<<"LIST \n"<<list_Dijkstra_time.us()<<"\n";};
    if(settings.graphType==0 || settings.graphType==2 ){results<<"MATRIX \n"<<matrix_Dijkstra_time.us()<<"\n";};
  }else{
    std::cerr<< "   ERROR: CANNOT SAVE TIME LOG \n"; 
  }




  //   Przed zakończeniem programu usuwane zostają wszystkie dynamicznie alokowane struktury
  if(route!=nullptr){
    delete [] route[0];
    delete [] route[1];
    delete route;
  };
  if(graph!=nullptr){delete graph;};
  if(graph2!=nullptr){delete graph2;};
  if(startingPoint!=nullptr){delete startingPoint;};
  return 0;
}








void displayRoute(vertex *** route, vertex * start, int size, int raw, std::string filename){
  std::fstream file;
  file.open(filename,std::fstream::out |std::fstream::trunc);
  if(file.is_open()){
    list<int> shortPath;
    vertex * current=nullptr;
    vertex * previous=nullptr;
    for(int i=0;i<size;i++){
      current=route[0][i];
      previous=route[1][i];
      if(raw){
        file<<*current<<" "<<current->distance<<" ";
      }else{
        file<<"Vertex "<<*current<<" distance "<<current->distance<<"\n";
      }
      do{
        shortPath.insertAt(current->value,0);
        current=previous;
        previous=route[1][previous->value];
      }while(current!=previous);
      shortPath.insertAt(current->value,0);
      int listSize=shortPath.size;
      for(int j=0;j<listSize;j++){
        file<<shortPath[0]->x<<" ";
        shortPath.removeFirst();
      };
      file<<"\n";
    }
    
    file.close();
  }else{
    std::cerr<<"Can't open File to save route \n";
  };
}

vertex * loadFromFile( std::string filename , GRAPH * & returnGraph){
  std::ifstream file;
  file.open(filename);
  if(file.is_open()){
    int nEdges;
    int nVertices;
    int startingVertex;
    file>>nEdges;
    file>>nVertices;
    file>>startingVertex;
    returnGraph = new GRAPH(nVertices);
    int begin;
    int end;
    int value;
    for(int i=0;i<nEdges;i++){
        file>>begin>>end>>value;
        returnGraph->insertEdge(begin,end,value);
    };
    file.close();
    return returnGraph->vertices(startingVertex);
  }else{
    returnGraph=nullptr;
    return nullptr;
  };
}
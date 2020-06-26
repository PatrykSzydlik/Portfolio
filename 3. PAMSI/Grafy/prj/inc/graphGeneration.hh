/*!
   \file graphGeneration.hh
   \brief Plik z funkcjami generującymi dane wierzchołków dla grafu
   \author Patryk Szydlik
   \date 01.05.20
 */

#include <fstream>
#include <string>
#include <stdlib.h>
#include <limits> 
#include<time.h>



/*!
\brief Funkcja losująca liczbę z przedziału lowest_value - highest_value
\param[in] lowest_value - najmniejsza wartość do wylosowania
\param[in] highest_value - największa wartość do wylosowania
\return Nowo wylosowana liczba
*/
template<typename DATATYPE>
DATATYPE limited_RNG (DATATYPE lowest_value , DATATYPE highest_value){
    DATATYPE diff=highest_value-lowest_value;
    DATATYPE new_value=lowest_value + (rand() % (diff+1) );
    return new_value;
}


/*!
\brief Funkcja losująca krawędzie grafu skierowanego

\param[in] nVertices - ilość wierzchołków 
\param[in] mEdges - ilość krawędzi

\param[out] - zwraca wskaźnik na macierz krawędzi
*/
int ** generateRandomGraph(const int & nVertices, int mEdges){
    int **edgeMatrix = new int * [nVertices];
    int * vertices= new int [nVertices];
    for(int i=0;i<nVertices;i++){edgeMatrix[i]=new int [nVertices];};
     for(int i=0;i<nVertices;i++){
        for(int j=0;j<nVertices;j++){
            edgeMatrix[i][j]=0;
        };
    };
    srand(time(NULL));
    int row=0;
    int col=0;
    while(mEdges>0){
        row=limited_RNG(0,nVertices-1);
        col=limited_RNG(0,nVertices-1);
        while(edgeMatrix[row][col]!=0 || row==col){
            row++;
            if(row>=nVertices){
                row=row%nVertices;
                col++;
            };
            if(col>=nVertices){
                col=col%nVertices;
            }; 
        };
        edgeMatrix[row][col]=limited_RNG(1,nVertices);
        vertices[row]++;
        vertices[col]++;
        mEdges--; 
    };
    
    for(int i=0;i<nVertices;i++){
        row=col=0;
        while(vertices[i]==0){
            if(vertices[row]>1){
                if(col!=row && vertices[col]>1){
                    if(edgeMatrix[row][col]!=0){
                    edgeMatrix[row][i]=edgeMatrix[row][col];
                    vertices[col]--;
                    vertices[i]++;
                    }else{
                        col++;
                        if(col>nVertices){
                            col=col%nVertices;
                            row++;
                        };
                    }
                }else{
                    col++;
                    if(col>nVertices){
                        col=col%nVertices;
                        row++;
                    };
                };
            }else{
                row++;
                row=row%nVertices;
            };
        };
    };
    delete[] vertices;
    return edgeMatrix;
}

/*!
\brief Funkcja generująca graf do pliku

\param[in] nVertices - ilość wierzchołków
\param[in] startingVertex - wierzchołek początkowy
\param[in] percentFull - procent wypełnienia grafu
\param[in] filename - nazwa pliku do zapisu
*/
void generateGraphToFile(int nVertices, int startingVertex, int percentFull, std::string filename ){
    int minEdges = nVertices-1;
    if(percentFull>100){percentFull=100;}else if(percentFull<0){percentFull=0;};
    int mEdges = (nVertices*(nVertices-1)*percentFull)/100;
    if(mEdges<minEdges){mEdges=minEdges;}
    int **edgeMatrix;
   
    edgeMatrix=generateRandomGraph(nVertices,mEdges);
    if(edgeMatrix!=nullptr){
        std::ofstream file;
        file.open(filename);
        if(file.is_open()){
            file<<mEdges<<" "<<nVertices<<" "<<startingVertex<<"\n";
            for(int i=0;i<nVertices;i++){
                for(int j=0;j<nVertices;j++){
                    if(edgeMatrix[i][j]>0){
                        file<<i<<" "<<j<<" "<<edgeMatrix[i][j]<<"\n";
                    };
                };
            };
        };
        for(int i=0;i<nVertices;i++){
            if(edgeMatrix[i]!=nullptr){
                delete [] edgeMatrix[i];
                };
            };
        delete [] edgeMatrix;
    };
}


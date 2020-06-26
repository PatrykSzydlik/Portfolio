/*!
   \file graphMatrix.hh
   \brief Plik z klasami grafu na podstawie macierzy oraz listy sąsiedztwa
   \author Patryk Szydlik
   \date 25.04.20
 */

#include "list.hh"
#include "heap.hh"
#include <fstream>
#include <string>


/*!
\brief Klasa wierzchołek 
*/
class vertex{
    public:
    int value;          //numer wierzchołka
    int distance=0;     // odległość od startowego wierzchołka
    HeapElem<int,vertex *> * locator=nullptr;   //locator w kolejce priorytetowej

    vertex(int val){
        value=val;
    }

    void setLocator( HeapElem<int,vertex *> * newlocator){
        locator=newlocator;
    }  

    HeapElem<int,vertex *> * getLocator(){
        return locator;
    }

    void setDistance(int dist){
        distance=dist;
    }

    int getDistance(){
        return distance;
    }

    void display(){
        std::cout<<" val "<<value<<" dist "<<distance;
    }

    friend std::ostream & operator << (std::ostream & os, const vertex & v);
};

/*!
\brief Klasa krawędź
*/
class edge{
    public:
    vertex * begin;
    vertex * end;
    int value;

    edge(vertex * v, vertex * w, int x){
        begin=v;
        end= w;
        value=x;
    }

    int weight(){
        return value;
    }

    ~edge(){
    }

    void display(){
        std::cout<<" Begin : "<<*begin<<"   End : "<<*end<<"   Value : "<<value<<"  \n";
    }
};

/*!
\brief Klasa grafu zaimplementowana na macierzy sąsiedztwa
*/
class graphMatrix{
    private:
        edge *** adjMatrix=nullptr;
        vertex ** verticesPtr=nullptr;
        int size=0;
        


    vertex * insertVertex(int v){
        if(verticesPtr[v]!=nullptr){
            return verticesPtr[v];
        }
        vertex * vert=new vertex(v);
        verticesPtr[v]=vert;
        return vert;
    }

    void replace(edge * e, int x){
        if(e->value>x){
            e->value=x;
        };
    }


    protected:

    graphMatrix(int nVertices){
        adjMatrix=new edge **[nVertices];
        for(int i=0;i<nVertices;i++){
            adjMatrix[i]=new edge * [nVertices];
            for(int j=0;j<nVertices;j++){
                adjMatrix[i][j]=nullptr;
            };
        }
        verticesPtr=new vertex * [nVertices];
        for(int i=0;i<nVertices;i++){
            verticesPtr[i]=nullptr;
        }
        size=nVertices;
    }
    template<typename GRAPH>
    friend vertex * loadFromFile( std::string filename , GRAPH * & returnGraph);

    public:

    ~graphMatrix(){
        if(adjMatrix!=nullptr){
            for(int i=0;i<size;i++){
                if(adjMatrix[i]!=nullptr){
                    delete[] adjMatrix[i];
                };
            };
            delete[] adjMatrix;
        };
        if(verticesPtr!=nullptr){delete[] verticesPtr;};
    }

    list<edge *> * incidentEdges(vertex * vertex){
        list<edge *> * newList = new list<edge *>;
        edge * elem;
        for(int j=0;j<size;j++){
            elem=adjMatrix[vertex->value][j];
            if(elem!=nullptr){
                newList->insert(elem);
            };
        };
        return newList;
    }



    vertex * opposite(edge * e, vertex * v){
        if(e->begin==v){
            return e->end;
        }else if(e->end==v){
            return e->begin;
        }else{
            return nullptr;
        }
    }

    void insertEdge(int v, int w, int x){  // działa
        if(adjMatrix[v][w]==nullptr){  
            vertex * vVer = insertVertex(v);
            vertex * wVer = insertVertex(w);

            adjMatrix[v][w]=new edge(vVer,wVer,x);
        }else{
            if(adjMatrix[v][w]->value > x){
                replace(adjMatrix[v][w],x);
            };
        };
    }

    vertex ** vertices(){
        return verticesPtr;
    }

    vertex * vertices(int x){
        return verticesPtr[x];
    }

    int graphSize(){
        return size;
    }


    void displayVertices(){ // Działa 
        for(int i=0;i<size;i++){
            if(verticesPtr[i]!=nullptr){
                verticesPtr[i]->display();
                std::cout<<" \n";
            };
        };
    }

    void displayEdges(){  // Działa
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                if(adjMatrix[i][j]!=nullptr){adjMatrix[i][j]->display();};
            };
        };
    };
};


/*!
\brief Klasa grafu zaimplementowana na liście sąsiedztwa
*/

class graphList{
    private:
        list<edge *> ** adjacentList;   // lista sąsiedztwa
        vertex ** verticesPtr=nullptr;  // tablica wierzchołków
        int size=0;


    vertex * insertVertex(int v){
        if(verticesPtr[v]!=nullptr){
            return verticesPtr[v];
        }
        vertex * vert=new vertex(v);
        verticesPtr[v]=vert;
        return vert;
    }


    void replace(edge * e, int x){
        if(e->value>x){
            e->value=x;
        };
    }
    protected:
    graphList(int nVertices){
        adjacentList=new list<edge *> * [nVertices];
        for(int i=0;i<nVertices;i++){
            adjacentList[i]=new list<edge *>;
        };
        verticesPtr=new vertex * [nVertices];
        for(int i=0;i<nVertices;i++){
            verticesPtr[i]=nullptr;
        }
        size=nVertices;
    }

    template<typename GRAPH>
    friend vertex * loadFromFile( std::string filename , GRAPH * & returnGraph);

    public:

    ~graphList(){
        if(verticesPtr!=nullptr){delete[] verticesPtr;};
        if(adjacentList!=nullptr){
            for(int i=0;i<size;i++){
                if(adjacentList[i]!=nullptr){
                    delete adjacentList[i];
                };
            };
            delete[] adjacentList;
        };
    }

    

    vertex * opposite(edge * e, vertex * v){
        if(e->begin==v){
            return e->end;
        }else if(e->end==v){
            return e->begin;
        }else{
            return nullptr;
        }
    }

    void insertEdge(int v, int w, int x){ 
        int edgeExists=0;
        edge *  toInsert;
        if(adjacentList!=nullptr){
            if(adjacentList[v]!=nullptr && adjacentList[v]->Size()>0){
                edge * adjacentToV;
                for(int i=0; i < adjacentList[v]->Size();i++){
                    adjacentToV = (*adjacentList[v])[i]->value();
                    if(adjacentToV->end->value==w){
                        toInsert=adjacentToV;
                        edgeExists=1;
                    };
                };
            };
            if(edgeExists){
                replace(toInsert,x);
            }else{
                vertex * vVer = insertVertex(v);
                vertex * wVer = insertVertex(w);
                toInsert = new edge(vVer,wVer,x);
                adjacentList[v]->insert(toInsert);
            };
        };
    }

    list<edge *> * incidentEdges(vertex * vertex){
        int i=vertex->value;
        return adjacentList[i];
    }

    vertex ** vertices(){
        return verticesPtr;
    }

    vertex * vertices(int x){
        return verticesPtr[x];
    }

    int graphSize(){
        return size;
    }

    void displayVertices(){ // Działa 
        for(int i=0;i<size;i++){
            if(verticesPtr[i]!=nullptr){
                verticesPtr[i]->display();
                std::cout<<" \n";
            };
        };
    }

    void displayEdges(){  // Działa
        if(adjacentList!=nullptr){
            for(int i=0;i<size;i++){
                if(adjacentList[i]!=nullptr){
                    adjacentList[i]->display();
                };
            };
        };
    };
};

std::ostream & operator << (std::ostream & os, const vertex & v){
    os << v.value;
    return os;
}
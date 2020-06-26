/*!
   \file dijkstra.hh
   \brief Algorytm Dijkstry poszukiwania najkrótszej ścieżki
   \author Patryk Szydlik
   \date 27.04.20
 */


#include "graph.hh"
#include <limits>

/*!
\brief Algorytm Dijkstry do wyszukiwania ścieżki oraz odległości między wierzchołkiem startowym a pozostałymi
\param[in] G - graf na którym wykonywany jest algorytm
\param[out] startingVertex - wierzchołek startowy

\param[out] - zwraca listę ze ścieżką
*/
template<typename GRAPH>
vertex *** DijkstraDistances(GRAPH * G, vertex * startingVertex){
    Heap <int,vertex *> Q;
    vertex *** route = new vertex **[2];
    route[0]=new vertex*[G->graphSize()];
    route[1]=new vertex*[G->graphSize()];
    vertex * v;
    for(int i=0;i<G->graphSize();i++){
        v = G->vertices(i);
        if(v==startingVertex){
            v->setDistance(0);
        }else{
            v->setDistance(std::numeric_limits<short>::max());
        };
        route[0][v->value]=v;
        route[1][v->value]=v;
        HeapElem<int,vertex *> * L=Q.insert(v->getDistance(),v);
        v->setLocator(L);
    }
    // powyzsza petla ustawia dystans do wszystkich wierzcholkow na max i wstawia wszystkie wierzcholki do kolejki
    int dist;
    vertex * u; 
    while(!Q.isEmpty()){  // dopoki sa jeszcze niezbadane wierzcholki
        Q.removeMin(dist,u); 
        list<edge *> * incEdges = G->incidentEdges(u);
        int size = incEdges->size; 
        for(int j=0;j<size;j++){
            edge * elem = (*incEdges)[j]->x;
            vertex * z = G->opposite(elem,u);
            dist=u->getDistance() + elem->weight();
            if(dist<z->getDistance()){
                z->setDistance(dist);
                Q.replaceKey(z->getLocator(),dist);
                route[0][z->value]=z;
                route[1][z->value]=u;
            };
        };
    }; 
    return route;
}
#ifndef DEGREE_H
#define DEGREE_H

#include "GrafoLisAd.h"
#include "ListaPT.h"

template< class T , class P>
class Degree {
public:
    typedef GrafoAdiacenti<T, P> GrafoAdiacenti;
    typedef typename GrafoAdiacenti::listaNodi listaNodi;
    typedef typename GrafoAdiacenti::posAdi pos;
    typedef typename GrafoAdiacenti::nodo nodo;
    typedef typename GrafoAdiacenti::Arco ArcoD;
    
    Degree(GrafoAdiacenti &gr);
    
    int inDegree(nodo);
    void reduce(int k);
    void equal(int k);
    
    void popolaGrafo();
    void stampaGrafo();
private:
    void isolaNodo(nodo n);
    void equal(nodo, int, int);
    GrafoAdiacenti *G;
};

template< class T , class P>
Degree<T,P>::Degree(GrafoAdiacenti &gr){
    this->G = &gr;
}

template< class T , class P>
int Degree<T,P>::inDegree(nodo n){
    listaNodi ls = G->listNodi();
    pos p = ls.primolista();
    int deg = 0;
    nodo v;
    while(!ls.finelista(p)){
        v.setId(ls.leggilista(p)->getId());
        ArcoD a(v, n);
        if(G->esisteArco(a)){
            deg++;
        }
        
        p = ls.succlista(p);
    }
    
    return deg;
}

template< class T , class P>
void Degree<T,P>::isolaNodo(nodo n){
    listaNodi ls = G->listNodi();
    pos p1 = ls.primolista();
    
    while (!ls.finelista(p1)) {
        nodo m = *ls.leggilista(p1);
        ArcoD a1(n, m);
        ArcoD a2(m, n);
        
        if(G->esisteArco(a1))
            G->cancArco(n, m);
        
        if(G->esisteArco(a2))
            G->cancArco(m, n);
        
        p1 = ls.succlista(p1);
    }
}

template< class T , class P>
void Degree<T,P>::reduce(int k){
    listaNodi ls = G->listaNodi();
    pos p = ls.primolista();
    
    while(!ls.finelista(p)){
        if(this->inDegree(ls.leggilista(p)) > k){
            this->isolaNodo(ls.leggilista(p));
            G->cancNodo(ls.leggilista(p));
        }
        ls.succlista(p);
    }
}

template< class T , class P>
void Degree<T,P>::equal(nodo n, int k, int ideg){
//    listaNodi ls = G.listNodi();
//    pos p = ls.primolista();
//    int indeg = ideg;
//    nodo v;
//    
//    while(!ls.finelista(p) && !(indeg == k)){
//        v.setId(ls.leggilista(p)->getId());
//        
//        if(G.esisteArco(v, n)){
//            G.cancArco(v, n);
//            indeg--;
//            p = ls.primolista();
//        }
//        
//        p = ls.succlista(p);
//    }
}

template< class T , class P>
void Degree<T,P>::equal(int k){
//    listaNodi ls = G.listNodi();
//    pos p = ls.primolista();
//    nodo n;
//    
//    while(!ls.finelista(p)){
//        n.setId(ls.leggilista(p)->getId());
//        int ideg = this->inDegree(n);
//        if( ideg > k)
//            equal(n, k, ideg);
//        p = ls.succlista(p);
//    }
}

template< class T , class P>
void Degree<T,P>::stampaGrafo(){
}

#endif // DEGREE_H

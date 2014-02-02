#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>

#include "ListaAdiacenti.h"

using namespace std;

template<class P, class N>
class Arco_ {
public:
    N nodo1;
    N nodo2;
    P peso;
    Arco_(N n1, N n2){
        this->nodo1 = n1;
        this->nodo2 = n2;
    }
};

template< class T, class N, class P>
class Grafo {
public:
    typedef T tipoelem;
    typedef P Peso;
    typedef N Nodo;
    
    typedef Arco_<Peso, Nodo> Arco;
    typedef ListaAdiacenti< Nodo* > listaNodi;
    typedef typename ListaAdiacenti< Nodo* >::posizione posListaNodi;
    typedef ListaAdiacenti<Arco> listaArchi;
    
    virtual ~Grafo(){};

    virtual bool vuoto() const = 0;
    virtual void insNodo(Nodo&) = 0;
    virtual void insArco(Nodo, Nodo, Peso) = 0;
    virtual bool cancNodo(Nodo) = 0;
    virtual void cancArco(Nodo, Nodo) = 0;
    virtual bool esisteNodo(Nodo) const = 0;
    virtual bool esisteArco(Arco) const = 0;
    virtual listaNodi adiacenti(Nodo) const = 0;
    virtual listaNodi listNodi() const = 0;
    virtual tipoelem leggiNodo(Nodo) const = 0;
    virtual bool scriviNodo(Nodo, tipoelem) = 0;
    virtual Peso leggiPeso(Nodo, Nodo) const = 0;
    virtual bool scriviPeso(Nodo, Nodo, Peso) = 0;
    virtual int numNodi() = 0;
    virtual int numArchi() = 0;

};

#endif

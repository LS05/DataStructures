#ifndef NODOPTR_H
#define NODOPTR_H

#include <iostream>
using namespace std;

template<class T>
class NodoPtr{
public:
    typedef T tipoelem;
    typedef NodoPtr<T> *nodoN;
    
	NodoPtr();
	NodoPtr(tipoelem);
	NodoPtr(tipoelem, nodoN, nodoN, nodoN);
	~NodoPtr();
    
	tipoelem getEtichetta();
    void setEtichetta(tipoelem);
    
	nodoN getFirstSon();
	nodoN getNextBro();
	nodoN getDaddy();
	void setFirstSon(nodoN);
	void setNextBro(nodoN);
	void setDaddy(nodoN);
    
    bool operator==(const NodoPtr<T> &other) const;
    bool operator!=(const NodoPtr<T> &other) const;

    
	friend ostream& operator<< (ostream &out, NodoPtr<T> &nodo);
    
private:
	nodoN daddy, firstSon, nextBro;
	tipoelem etichetta;
};

template<class T>
NodoPtr<T>::NodoPtr(){
	daddy = firstSon = nextBro = NULL;
	etichetta = 0;
}

template<class T>
NodoPtr<T>::NodoPtr(tipoelem a){
	daddy = firstSon = nextBro = NULL;
	etichetta = a;
}

template<class T>
NodoPtr<T>::NodoPtr(tipoelem a, nodoN p, nodoN pf, nodoN sf){
	daddy = p;
	firstSon = pf;
	nextBro = sf;
	etichetta = a;
}

template<class T>
NodoPtr<T>::~NodoPtr(){
}

template<class T>
typename NodoPtr<T>::tipoelem NodoPtr<T>::getEtichetta(){
    return etichetta;
};

template<class T>
void NodoPtr<T>::setEtichetta(tipoelem a){
    etichetta = a;
};

template<class T>
typename NodoPtr<T>::nodoN NodoPtr<T>::getFirstSon(){
	return firstSon;
}

template<class T>
typename NodoPtr<T>::nodoN NodoPtr<T>::getNextBro(){
	return nextBro;
}

template<class T>
typename NodoPtr<T>::nodoN NodoPtr<T>::getDaddy(){
	return daddy;
}

template<class T>
void NodoPtr<T>::setFirstSon(nodoN n){
	firstSon = n;
}

template<class T>
void NodoPtr<T>::setNextBro(nodoN n){
    nextBro = n;
}

template<class T>
void NodoPtr<T>::setDaddy(nodoN n){
	daddy = n;
}

template< class T >
ostream& operator<< (ostream &out, NodoPtr<T> &nodo){
        out << nodo.getEtichetta();
        return out;
}

template< class T >
bool NodoPtr<T>::operator==(const NodoPtr<T> &other) const {
    return ( *this == other );
}

template< class T >
bool NodoPtr<T>::operator!=(const NodoPtr<T> &other) const {
    return !(*this == other);
}

#endif

#ifndef NODOPTR_H
#define NODOPTR_H
#include <iostream>
#include <stdlib.h>

template<class T>
class NodoPtr{
public:
    typedef T tipoelem;
    typedef NodoPtr<T> *posizione;

    NodoPtr();
    NodoPtr(tipoelem);
    NodoPtr(tipoelem, posizione);
    ~NodoPtr();

    tipoelem getEtichetta();
    void setEtichetta(tipoelem);

    posizione getSuccessivo();
    void setSuccessivo(posizione);
private:
   posizione successivo;
   tipoelem etichetta;
};

template<class T>
NodoPtr<T>::NodoPtr(){
   successivo = NULL;
};

template<class T>
NodoPtr<T>::NodoPtr(tipoelem a){
   etichetta = a;
   successivo = NULL;
};

template<class T>
NodoPtr<T>::NodoPtr(tipoelem a, posizione p){
   etichetta = a;
   successivo = p;
};

template<class T>
NodoPtr<T>::~NodoPtr(){
    successivo = NULL;
    delete successivo;
};

template<class T>
typename NodoPtr<T>::tipoelem NodoPtr<T>::getEtichetta(){
   return etichetta;
};

template<class T>
void NodoPtr<T>::setEtichetta(tipoelem a){
   etichetta = a;
};

template<class T>
typename NodoPtr<T>::posizione NodoPtr<T>::getSuccessivo(){
   return successivo;
};

template<class T>
void NodoPtr<T>::setSuccessivo(posizione p){
   successivo = p;
};

#endif

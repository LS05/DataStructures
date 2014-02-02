#include <iostream>
#include <cstdlib> //Serve per poter usare le funzioni della libreria standard del C
#include "Nodo.h"

NodoPtr::NodoPtr(){
   etichetta = 0;
   successivo = NULL;
};

NodoPtr::NodoPtr(tipoelem a){
   etichetta = a;
   successivo = NULL;
};

NodoPtr::NodoPtr(tipoelem a, posizione p){
   etichetta = a;
   successivo = p;
};

NodoPtr::~NodoPtr(){};

tipoelem NodoPtr::getEtichetta(){
   return etichetta;
};

void NodoPtr::setEtichetta(tipoelem a){
   etichetta = a;     
};
   
posizione NodoPtr::getSuccessivo(){
   return successivo;
};

void NodoPtr::setSuccessivo(posizione p){
   successivo = p;     
};

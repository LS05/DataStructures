#ifndef INSIEMELISTA_H
#define INSIEMELISTA_H
#include <iostream>
#include <stdlib.h>

#include "Nodo.h"
#include "InsiemeIter.h"

using namespace std;

template<class T>
class InsiemeLst{
public:
    typedef NodoPtr<T> *posizione;
    typedef T tipoelem;
    typedef AdtIterator<T> iterator;

    InsiemeLst();
    InsiemeLst(const InsiemeLst<T> &);
	~InsiemeLst();

	void creaInsieme();
    bool insiemeVuoto();
    bool appartiene(tipoelem);
    void inserisci(tipoelem);
    void cancella(tipoelem);
    InsiemeLst<T>* unione(InsiemeLst<T> &);
    InsiemeLst<T>* intersezione(InsiemeLst<T> &);
    InsiemeLst<T>* differenza(InsiemeLst<T> &);
    void stampaInsieme();

    InsiemeLst<T> &operator=(InsiemeLst<T> &);

    iterator begin() const {
        return AdtIterator<T>(insieme);
    }

    iterator end() const {
        return AdtIterator<T>(NULL);
    }

private:
   posizione insieme;
};

template<class T>
InsiemeLst<T>::InsiemeLst(){
   creaInsieme();
}

template<class T>
InsiemeLst<T>::InsiemeLst(const InsiemeLst<T> &set){
    this->creaInsieme();
    for (AdtIterator<T> i = set.begin(); i != set.end(); ++i){
        this->inserisci(*i);
    }
}

template<class T>
InsiemeLst<T>::~InsiemeLst(){
    posizione q;
    while (insieme != NULL){
        q = insieme;
        insieme = insieme->getSuccessivo();
        delete q;
    }
}

template<class T>
void InsiemeLst<T>::creaInsieme(){
   insieme = NULL;
}

template<class T>
bool InsiemeLst<T>::insiemeVuoto(){
   return (insieme == NULL);
}

template<class T>
bool InsiemeLst<T>::appartiene(tipoelem a){
   posizione p = insieme;
   bool flag = false;
   while ((p != NULL) && (!flag)){
      flag = (a == p->getEtichetta());
      p = p->getSuccessivo();
   }
   return flag;
}

template<class T>
void InsiemeLst<T>::inserisci(tipoelem a){
   if (!appartiene(a))
      insieme = new NodoPtr<T>(a, insieme);
   else
      cout<< "Errore: Elemento presente!" << endl;
}

template<class T>
void InsiemeLst<T>::cancella(tipoelem a){
    if (appartiene(a)){
        posizione p = insieme;
        posizione q = p;

        while ((p != NULL) && (p->getEtichetta()!=a)){
            q = p;
            p = p->getSuccessivo();
        }

        if(p == insieme){
            if(p->getSuccessivo() == NULL)
                insieme = NULL;
            else
                insieme = p->getSuccessivo();
        } else
                q->setSuccessivo(p->getSuccessivo());

        delete p;

    } else
        cout<<"Errore: Elemento non presente!";
}

template<class T>
InsiemeLst<T>* InsiemeLst<T>::unione(InsiemeLst<T> &set){
    InsiemeLst<T> *c = new InsiemeLst<T>(*this);

    for (AdtIterator<T> i = set.begin(); i != set.end(); ++i)
    {
        if (!c->appartiene(*i)){
            c->inserisci(*i);
        }
    }

    return c;
}

template<class T>
InsiemeLst<T>* InsiemeLst<T>::intersezione(InsiemeLst<T> &set){
    InsiemeLst<T> *c = new InsiemeLst<T>();

    for (AdtIterator<T> i = set.begin(); i != set.end(); ++i)
    {
        if (appartiene(*i))
            c->inserisci(*i);
    }

    return c;
}

template<class T>
InsiemeLst<T>* InsiemeLst<T>::differenza(InsiemeLst<T> &set){
    InsiemeLst<T> *c = new InsiemeLst<T>();
    for (AdtIterator<T> i = set.begin(); i != set.end(); ++i)
    {
        if (!appartiene(*i))
            c->inserisci(*i);
    }
   return c;
}

template<class T>
InsiemeLst<T>& InsiemeLst<T>::operator=(InsiemeLst<T> &i){

    for(AdtIterator<T> iter = i.begin(); iter != i.end(); ++iter)
        inserisci(*iter);

    return *this;
}

template<class T>
void InsiemeLst<T>::stampaInsieme(){
	cout << "{ ";

	for (AdtIterator<T> i = begin(); i != end(); ++i)
        cout << *i << " ";

	cout << "}" << endl;
}

#endif

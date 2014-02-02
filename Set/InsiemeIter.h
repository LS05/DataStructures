#ifndef INSIEMEITER_H_INCLUDED
#define INSIEMEITER_H_INCLUDED

#include <iostream>
#include <iterator>

#include "InsiemeLista.h"
#include "Nodo.h"

using namespace std;

template<class T> class InsiemeLst;

template<class T>
class AdtIterator : public iterator<forward_iterator_tag, T>{
    friend class InsiemeLst<T>;
public:
    T operator*();
    const AdtIterator<T>& operator++();
    bool operator!=(const AdtIterator<T>& other) const;
private:
    NodoPtr<T> *nPtr;
    AdtIterator(NodoPtr<T> *ptr) : nPtr(ptr) {
    }
};

template <class T>
T AdtIterator<T>::operator*()
{
    return this->nPtr->getEtichetta();
}

template <class T>
const AdtIterator<T>& AdtIterator<T>::operator++()
{
    assert(nPtr != NULL);
    nPtr = nPtr->getSuccessivo();
    return *this;
}

template <class T>
bool AdtIterator<T>::operator!=(const AdtIterator<T>& other) const
{
    return this->nPtr != other.nPtr;
}
#endif

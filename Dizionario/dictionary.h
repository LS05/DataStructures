#ifndef _DICTIONARY_H
#define _DICTIONARY_H
#include "pair.h"

template<class K, class E>
class dictionary{
public:
    virtual ~dictionary() {}
    virtual bool vuoto() const = 0;
    virtual bool appartiene(mypair<K, E>&) = 0;
    virtual void inserisci(mypair<K, E>&) = 0;
    virtual mypair<K, E>* recupera(const K&) const = 0;
    virtual void cancella(K &) = 0;
    virtual void aggiorna(mypair<K, E> &, E) = 0;
    virtual unsigned int dimensione() const = 0;
};

#endif

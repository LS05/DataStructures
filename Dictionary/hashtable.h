#ifndef HASH_TABLET_H_
#define HASH_TABLET_H_

#include "dictionary.h"
#include "ListaPT.h"
#include "hash.h"
#include "pair.h"

#include <iostream>

using namespace std;

template<class K, class E>
class hashtable : public dictionary<K,E>{
public:

    typedef K key;
    typedef E tipoelem;

	hashtable(int);	    // constructor
	~hashtable();

	bool vuoto() const;
    bool appartiene(mypair<K, E>&);
    void inserisci(mypair<K, E>&);
    mypair<K, E>* recupera(const key&) const;
    void cancella(key &);
    void aggiorna(mypair<K, E> &, tipoelem);
    unsigned int dimensione() const;

    void stampa();
private:
	Lista< mypair< K, E> > *table;  // the hash table
	int dsize;		    // number of pairs in dictionary
	int divisor;		    // hash function divisor
};

template<class K, class E>
hashtable<K,E>::hashtable(int the_divisor)
{
	divisor = the_divisor;
	dsize = 0;
	table = new Lista<mypair<K, E> > [divisor];
	for(int i = 0; i < divisor; i++)
		table[i].crealista();
}

template<class K, class E>
hashtable<K,E>::hashtable::~hashtable(){
    typename Lista< mypair< K, E> >::posizione p;
    for (int i = 0; i < divisor; i++){
      p = table[i].primoLista();
      while (!table[i].finelista(p)){
         table[i].cancLista(p);
         p = table[i].primoLista();
      }
    }
}
template<class K, class E>
bool hashtable<K,E>::vuoto() const{
		return (dsize == 0);
}

template<class K, class E>
bool hashtable<K,E>::appartiene(mypair<K, E> &the_pair){
    K key = the_pair.getKey();
    typename Lista< mypair< K, E> >::posizione p;
    int h = (int) Hash::hashFunc(key) % divisor;
    bool trovato = false;

    p = table[h].primoLista();

    while (!(table[h].finelista(p) || trovato)){
        if (table[h].leggilista(p).getValue() == the_pair.getValue())
            trovato = true;
        p = table[h].succLista(p);
    }

    return trovato;
}

template<class K, class E>
void hashtable<K,E>::inserisci(mypair<K, E> &the_pair){
    int i = (int) Hash::hashFunc(the_pair.getKey()) % divisor;
    typename Lista< mypair< K, E> >::posizione pos;

    pos = table[i].primoLista();

    if (!appartiene(the_pair)){
        table[i].inslista(the_pair, pos);
        this->dsize++;
    } else
      cout << the_pair.getKey() << " presente in posizione " << i << endl;
}

template<class K, class E>
mypair< K, E >* hashtable<K,E>::recupera(const key &k) const{
    typename Lista< mypair< K, E> >::posizione p;
    int i = (int) Hash::hashFunc(k) % divisor;
    bool trovato = false;
    mypair<K, E> *res;

    p = table[i].primoLista();

    while (!(table[i].finelista(p) || trovato)){
            if(table[i].leggilista(p).getKey() == k){
                const K ch = table[i].leggilista(p).getKey();
                E val = table[i].leggilista(p).getValue();
                res = new mypair<K, E>(ch, val);
                trovato = true;
            }
    }

    return res;
}

template<class K, class E>
void hashtable<K, E>::cancella(key &k){
    typename Lista< mypair< K, E> >::posizione p;
    int h = (int) Hash::hashFunc(k) % divisor;
    bool trovato = false;
    p = table[h].primoLista();

    while (!(table[h].finelista(p) || trovato)){
        if (table[h].leggilista(p).getKey() == k){
             table[h].cancLista(p);
             trovato = true;
        }
        p = table[h].succLista(p);
    }
}
template<class K, class E>
void hashtable<K, E>::aggiorna(mypair<K, E> &mp, tipoelem e){
    typename Lista< mypair< K, E> >::posizione p;
    int h = (int) Hash::hashFunc(mp.getKey()) % divisor;
    bool trovato = false;

    p = table[h].primoLista();
    while (!(table[h].finelista(p) || trovato)){
        if (table[h].leggilista(p).getKey() == mp.getKey()){
            mp.setValue(e);
        }
        p = table[h].succLista(p);
    }
}
template<class K, class E>
unsigned int hashtable<K, E>::dimensione() const{
    return this->dsize;
}

template<class K, class E>
void hashtable<K, E>::stampa(){
    typename Lista< mypair< K, E> >::posizione p;
    for(int i = 0; i < divisor; i++){
        if(!table[i].listavuota()){
            p = table[i].primoLista();
            int collision = 0;
            cout << "\n---------\nElementi con chiave " << i << ":" << endl;
            while (!table[i].finelista(p)){
                table[i].leggilista(p);
                cout << "Campo chiave: " << table[i].leggilista(p).getKey() << " Valore: " << table[i].leggilista(p).getValue() <<endl;
                p = table[i].succLista(p);
                collision++;
            }
            cout << "Numero di collisioni per la chiave " << i << ": " << collision-1 << "\n--------- \n" << endl;
        }
    }
}

#endif

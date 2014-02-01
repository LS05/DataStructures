#ifndef _CODAP_H
#define _CODAP_H

#include <iostream>

#include "assert.h"

using namespace std;

template < class T >
class CodaP{
public:
	typedef T tipoelem;
	CodaP ();
	CodaP (int);
	~CodaP ();

	void creaPrioriCoda();
	void inserisci (tipoelem);
	tipoelem min ();
	void cancellaMin ();

    template<class Y>
	friend ostream& operator<< (ostream &out, CodaP<Y> &coda);
private:
	int MAXLUNG;
	tipoelem *heap;
	int ultimo;

	void fixUp ();
	void fixDown (int, int);
};


template < class T >
CodaP < T >::CodaP ():MAXLUNG (100){
	heap = new tipoelem[MAXLUNG];
	creaPrioriCoda ();
}

template < class T >
CodaP < T >::CodaP (int maxN):MAXLUNG (maxN){
	heap = new tipoelem[MAXLUNG];
	creaPrioriCoda ();
}

template < class T >
CodaP < T >::~CodaP(){
	delete[]heap;
}

template < class T >
void CodaP < T >::creaPrioriCoda (){
	ultimo = 0;
}

template < class T >
void CodaP < T >::inserisci (tipoelem e){
	assert (ultimo < MAXLUNG);
	heap[++ultimo - 1] = e;
	fixUp ();
}

template < class T >
typename CodaP < T >::tipoelem CodaP < T >::min (){
	assert (ultimo != 0);
	return (heap[0]);
}

template < class T > void CodaP < T >::cancellaMin (){
	assert (ultimo != 0);
	heap[0] = heap[ultimo - 1];
	ultimo--;
	fixDown (1,ultimo);
}


/* Per ripristinare i vincoli dello heap quando la priorità di un nodo è      *
 * cresciuta, ci spostiamo nello heap verso l'alto, scambiando, se necessario,*
 * il nodo in posizione k con il suo nodo padre (in posizione k/2),           *
 * continuando fintanto che heap[k]<heap[k/2] oppure fino a quando            *
 * raggiungiamo la cima dello heap.                                           */

template < class T >
void CodaP < T >::fixUp (){
	int k = ultimo;
	while (k > 1 && heap[k - 1] < heap[k / 2 - 1]){
		tipoelem tmp;
		tmp = heap[k - 1];
		heap[k - 1] = heap[k / 2 - 1];
		heap[k / 2 - 1] = tmp;
		k = k / 2;
	}
}

/* Per ripristinare i vincoli dello heap quando la priorità di un nodo si è   *
 * ridotta, ci spostiamo nello heap verso il basso, scambiando, se necessario,*
 * il nodo in posizione k con il minore dei suoi nodi figli e arrestandoci    *
 * quando il nodo al posto k non è più grande di almeno uno dei suoi figli    *
 * oppure quando raggiungiamo il fondo dello heap. Si noti che se N è pari e  *
 * k è N/2, allora il nodo in posizione k ha un solo figlio: questo caso      *
 * particolare deve essere trattato in modo appropriato.                      */

template < class T >
void CodaP < T >::fixDown (int k, int N){
	short int scambio = 1;
	while (k <= N / 2 && scambio){
		int j = 2 * k;
		tipoelem tmp;
		if (j < N && heap[j - 1] > heap[j])
			j++;
		if (scambio = (heap[j - 1] < heap[k - 1])){
			tmp = heap[k - 1];
			heap[k - 1] = heap[j - 1];
			heap[j - 1] = tmp;
			k = j;
		}
	}
}

template< class Y >
ostream& operator<< (ostream &out, CodaP<Y> &coda){
	out << "C = < ";
    for(int i = 0; i < coda.ultimo; i++)
        out << coda.heap[i] << " ";
	out << ">" << endl;

	return out;
}

#endif

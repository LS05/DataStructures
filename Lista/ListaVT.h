#ifndef _LISTAVT_H
#define _LISTAVT_H

#include <iostream>

#include "linear_list.h"

using namespace std;

const int DIMENSIONE = 1024;

template< class T >
class ListaVT : Linear_list<T, int>{

public:
	typedef typename Linear_list<T, int>::value_type tipoelem;
    typedef typename Linear_list<T, int>::position posizione;

	ListaVT();
	ListaVT(int);
	ListaVT(const ListaVT<T> &);
	~ListaVT();

	void crealista();
	bool listavuota() const;
	tipoelem leggilista(posizione) const;
	void scrivilista(const tipoelem &, posizione);
	posizione primolista() const;
	posizione ultimolista() const;
	bool finelista(posizione) const;
	posizione succlista(posizione) const;
	posizione predlista(posizione) const;
	void inslista(const tipoelem &, posizione);
	void canclista(posizione);
	/**
        Funzioni di servizio implementate
	*/
	int size() const;
	void clear();

	bool operator== (const ListaVT<T> &ls1);
    bool operator!= (const ListaVT<T> &ls2);
    ListaVT<T>& operator= (const ListaVT<T> &);

	template <class Y>
	friend ostream& operator<< (ostream &out, ListaVT<Y> &lista);
private:
	tipoelem *elementi;
	int lunghezza;
	int dimArray;
};

template< class T >
ListaVT< T >::ListaVT()
{
    dimArray = DIMENSIONE;
	this->crealista();
}

template< class T >
ListaVT< T >::ListaVT(int dim){
    dimArray = dim;
    this->crealista();
}

template< class T >
void ListaVT< T >::crealista()
{
	lunghezza = 0;
	elementi = new tipoelem[dimArray];
}

template< class T >
ListaVT< T >::~ListaVT()
{
	delete[] elementi;
}

template< class T >
ListaVT< T >::ListaVT(const ListaVT<T> &lista) {
  this->lunghezza = lista.lunghezza;
  this->elementi = new T[DIMENSIONE];
  this->dimArray = DIMENSIONE;

  for (int i = 0; i < DIMENSIONE; i++)
     this->elementi[i] = lista.elementi[i];
}

template< class Y >
ostream& operator<< (ostream &out, ListaVT<Y> &lista){
	out << "L = < ";

	typename ListaVT<Y>::posizione p = lista.primolista();

	while(!lista.finelista(p)){
		out << lista.leggilista(p) << " ";
		p = lista.succlista(p);
	}
	out << ">" << endl;

	return out;
}

template< class T >
bool ListaVT<T>::operator==(const ListaVT<T> &ls2){
    return Linear_list<T, posizione>::operator==(ls2);
}

template< class T >
bool ListaVT<T>::operator!=(const ListaVT<T> &ls2) {
    return Linear_list<T, posizione>::operator!=(ls2);
}

template< class T >
ListaVT<T>& ListaVT<T>::operator= (const ListaVT<T> &lista){
    this->clear();
    delete [] elementi;
    this->crealista();
    typename ListaVT<T>::position p = lista.primolista();
    typename ListaVT<T>::position m = this->primolista();

    while(!lista.finelista(p)){
        this->inslista(lista.leggilista(p), this->succlista(m));
        p = lista.succlista(p);
        m = this->succlista(m);
    }

    return *this;
}

template< class T >
bool ListaVT< T >::listavuota() const
{
	return(lunghezza == 0);
}

template< class T >
typename ListaVT<T>::posizione ListaVT< T >::primolista() const
{
	return (1);
}

template< class T >
typename ListaVT<T>::posizione ListaVT< T >::ultimolista() const
{
	return (this->elementi[lunghezza - 1]);
}

template< class T >
typename ListaVT<T>::posizione  ListaVT< T >::succlista(posizione p) const
{
	if ( (0 < p) && (p < lunghezza+1)) // precondizione
		return(p + 1);
	else
		return(p);
}

template< class T >
typename ListaVT<T>::posizione ListaVT< T >::predlista(posizione p) const
{
	if ( (1 < p) && (p < lunghezza+1)) // precondizione
		return(p-1);
	else
		return(p);
}

template< class T >
bool ListaVT< T >::finelista(posizione p) const
{
	if ( (0 < p) && (p <= lunghezza+1)) // precondizione
		return( p == lunghezza+1);
	else
		return(false);
}

template< class T >
typename ListaVT<T>::tipoelem ListaVT< T >::leggilista(posizione p) const
{
	if ( (0 < p) && (p < lunghezza+1)) // precondizione
		return(elementi[p-1]);
}

template< class T >
void ListaVT< T >::scrivilista(const tipoelem &a, typename ListaVT<T>::posizione p)
{
	if ( (0 < p) && (p < lunghezza+1)) // precondizione
		elementi[p-1] = a;
}

template< class T >
void ListaVT< T >::inslista(const tipoelem &a, posizione p)
{
	if ( (0 < p) && (p <= lunghezza+1)) // precondizione
	{
		for (int i=lunghezza; i>=p; i--)
			elementi[i] = elementi[i-1];
		elementi[p-1]=a;
		lunghezza++;
	}
}

template< class T >
void ListaVT< T >::canclista(posizione p)
{
	if ( (0 < p) && ( p < lunghezza + 1)) // precondizione
		if (!listavuota())
		{
			for (int i=p-1;i<(lunghezza-1);i++)
				elementi[i]=elementi[i+1];
			lunghezza--;
		}
}

template< class T >
int ListaVT< T >::size() const
{
    return Linear_list<T, int>::size();
}

template< class T >
void ListaVT< T >::clear()
{
    return Linear_list<T, int>::clear();
}

#endif // _LISTAVT_H

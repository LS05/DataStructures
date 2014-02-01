#ifndef LISTAPT_H
#define LISTAPT_H

#include <iostream>

#include "linear_list.h"
#include "Cella.h"

using namespace std;

template< class T >
class ListaPT : Linear_list<T, Cella<T>*>{

public:
	typedef T tipoelem;
	typedef Cella<T> *posizione;

	ListaPT();
	ListaPT(const ListaPT<T>&);

	~ListaPT();

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

    bool operator== (ListaPT<T> &ls1);
    ListaPT<T>& operator= (const ListaPT<T> &);

	template <class Y>
	friend ostream& operator<< (ostream &out, ListaPT<Y> &lista);

private:
	posizione lista;
	posizione checkPos(tipoelem, posizione);
};

template< class T >
ListaPT< T >::ListaPT()
{
	crealista();
}

template< class T >
ListaPT< T >::ListaPT(const ListaPT<T> &lista)
{
    this->crealista();
    posizione p = lista.primolista();
    posizione m = this->primolista();

    while(!lista.finelista(p)){
        this->inslista(lista.leggilista(p), this->succlista(m));
        p = lista.succlista(p);
        m = this->succlista(m);
    }
}

template< class T >
ListaPT< T >::~ListaPT()
{
	posizione primo = primolista();
	posizione q;
	while (this->lista != primo){
		q = primo;
		primo = primo->getSucc();
		delete q;
	}
	delete lista;
}

template< class Y >
ostream& operator<< (ostream &out, ListaPT<Y> &lista){
	out << "L = < ";
	typename ListaPT<Y>::posizione p = lista.primolista();
	while(!lista.finelista(p)){
		out << lista.leggilista(p) << " ";
		p = lista.succlista(p);
	}
	out << ">" << endl;

	return out;
}

/**
* In questo caso si assume che due liste sono uguali se contengono
* gli stessi elementi nelle stesse posizioni.
*/

template< class T >
bool ListaPT<T>::operator==(ListaPT<T> &ls2){
    bool flag = true;

    if(this->size() != ls2.size()){
        return false;
    }else{
        posizione p = this->primolista();
        posizione m = ls2.primolista();
        while(!this->finelista(p) && !ls2.finelista(m) && flag){
            if(this->leggilista(p) != ls2.leggilista(m))
                flag = false;
            p = this->succlista(p);
            m = ls2.succlista(m);
        }
    }

    return flag;
}

template< class T >
ListaPT<T>& ListaPT<T>::operator= (const ListaPT<T> &lista){
    this->clear();
    this->crealista();
    posizione p = lista.primolista();
    posizione m = this->primolista();

    while(!lista.finelista(p)){
        this->inslista(lista.leggilista(p), this->succlista(m));
        p = lista.succlista(p);
        m = this->succlista(m);
    }

    return *this;
}

template<class T>
void ListaPT<T>::crealista()
{
	tipoelem elementoVuoto;
	this->lista = new Cella<T>();
	this->lista->setElemento(elementoVuoto);
	this->lista->setSucc(this->lista);
	this->lista->setPrec(this->lista);
}

template<class T>
bool ListaPT<T>::listavuota() const
{
    return (lista->getSucc() == lista) && (lista->getPrec() == lista);
}

template<class T>
typename ListaPT<T>::posizione ListaPT<T>::primolista() const
{
	return this->lista->getSucc();
}

template<class T>
typename ListaPT<T>::posizione ListaPT<T>::ultimolista() const
{
	return this->lista->getPrec();
}

template<class T>
bool ListaPT<T>::finelista(posizione cella) const
{
	return (cella == this->lista);
}

template<class T>
typename ListaPT<T>::posizione ListaPT<T>::succlista(posizione cella) const
{
	return (cella->getSucc());
}

template<class T>
typename ListaPT<T>::posizione ListaPT<T>::predlista(posizione cella) const
{
	return (cella->getPrec());
}

template<class T>
void ListaPT<T>::inslista(const tipoelem &a, posizione cella)
{
	typename ListaPT<T>::posizione temp = new Cella<T>();
	temp->setElemento(a);
	temp->setPrec(cella->getPrec());
	temp->setSucc(cella);
	(cella->getPrec())->setSucc(temp);
	cella->setPrec(temp);
	cella=temp;
}

template<class T>
typename ListaPT<T>::tipoelem ListaPT<T>::leggilista(posizione cella) const
{
	return (cella->getElemento());
}

template<class T>
void ListaPT<T>::scrivilista(const tipoelem &a, posizione cella)
{
	cella->setElemento(a);
	return;
}

template<class T>
void ListaPT<T>::canclista(posizione cella)
{
	typename ListaPT<T>::posizione temp = cella;

	(cella->getPrec())->setSucc(cella->getSucc());
	(cella->getSucc())->setPrec(cella->getPrec());
	cella = cella->getSucc();
	delete temp;
	return;
}

template< class T >
int ListaPT< T >::size() const
{
    return Linear_list<T, posizione>::size();
}

template< class T >
void ListaPT< T >::clear()
{
    return Linear_list<T, posizione>::clear();
}

#endif

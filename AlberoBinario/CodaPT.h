#ifndef CODAPT_H
#define CODAPT_H

#include <iostream>

#include "Coda.h"
#include "Cella.h"

using namespace std;

template < class T >
class CodaPT : public Coda<T>{
public:
	typedef T tipoelem;
	typedef Cella<T> *nodo;

	CodaPT();
	~CodaPT();
	CodaPT(const CodaPT<T> &);
	void creaCoda();
	bool codaVuota() const;
	tipoelem leggiCoda() const;
	void fuoriCoda();
	void inCoda(const tipoelem &);
    int size() const;
    CodaPT<T>& operator= (const CodaPT<T> &);

	template<class Y>
	friend ostream& operator<< (ostream &out, CodaPT<Y> &coda);
private:
	nodo coda;
	nodo head;
	nodo tail;
	int dimQ;
};

template< class T >
CodaPT<T>::CodaPT(){
    this->dimQ = 0;
	creaCoda();
}

template< class T >
CodaPT<T>::~CodaPT(){
	nodo q;
	while (head != coda){
		q = head;
		head = head->getSucc();
		delete q;
	}
	delete coda;
}

template< class T >
CodaPT<T>::CodaPT(const CodaPT<T> &c){
	this->creaCoda();
	typename CodaPT<T>::nodo n = c.coda->getSucc();
	while(n != c.tail->getSucc()){
		typename CodaPT<T>::tipoelem e = n->getElemento();
		this->inCoda(e);
		n = n->getSucc();
	}
	this->dimQ = c.dimQ;
}

template<class T>
CodaPT<T>& CodaPT<T>::operator= (const CodaPT<T> &c){
    while(!this->codaVuota()){
        this->fuoriCoda();
    }

    typename CodaPT<T>::nodo n = c.coda->getSucc();

	while(n != c.tail->getSucc()){
		typename CodaPT<T>::tipoelem e = n->getElemento();
		this->inCoda(e);
		n = n->getSucc();
	}

    this->dimQ = c.dimQ;
}

template< class Y >
ostream& operator<< (ostream &out, CodaPT<Y> &coda){
	out << "C = < ";
	CodaPT<Y> c = coda;
	while(!c.codaVuota()){
		typename CodaPT<Y>::tipoelem e = c.leggiCoda();
		out << e << " ";
		c.fuoriCoda();
	}

	out << ">" << endl;

	return out;
}

template< class T >
void CodaPT<T>::creaCoda(){
	this->coda = new Cella<T>();
	this->coda->setPrec(this->coda);
	this->coda->setSucc(this->coda);
	this->head = coda;
	this->tail = coda;
}

template< class T >
bool CodaPT<T>::codaVuota() const{
	return (head == coda);
}

template< class T >
typename CodaPT<T>::tipoelem CodaPT<T>::leggiCoda() const{
	if (!codaVuota())
		return (this->head->getElemento());
}

template< class T >
void CodaPT<T>::fuoriCoda(){
	if (!codaVuota()){
		nodo temp = this->coda->getSucc();
		this->coda->setSucc(temp->getSucc());
		temp->getSucc()->setPrec(this->coda);
		this->head = temp->getSucc();
		delete temp;
		this->dimQ--;
	}
	return;
}

template< class T >
void CodaPT<T>::inCoda(const tipoelem &a){
	typename CodaPT<T>::nodo temp = new Cella<T>(a);
	if(codaVuota()){
		this->coda->setSucc(temp);
		this->head = temp;
		temp->setPrec(this->coda);
		temp->setSucc(this->coda);
		this->tail = temp;
		this->dimQ++;
	}else{
		temp->setPrec(tail);
		this->tail->setSucc(temp);
		temp->setSucc(coda);
		this->tail = temp;
		this->dimQ++;
	}
	return;
}

template< class T >
int CodaPT<T>::size() const{
	return dimQ;
}

#endif /* CODA_H_ */

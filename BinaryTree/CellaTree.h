#ifndef NODOBIN_H
#define NODOBIN_H

#include <iostream>

using namespace std;

template < class T >
class NodoBin{
public:
	typedef T tipoelem;
	typedef NodoBin<T> *nodo;

	NodoBin();
	~NodoBin();

	void setSinistro(nodo);
	void setDestro(nodo);
	void setParent(nodo);

	nodo getSinistro() const;
	nodo getDestro() const;
	nodo getParent() const;

	tipoelem leggiCella() const;
	void scriviCella(tipoelem);
    
    template <class Y>
	friend ostream& operator<< (ostream &out, NodoBin<Y> &nodo);
    
private:
	nodo sinistro;
	nodo destro;
	nodo genitore;
	tipoelem valore;
};


template < class T >
NodoBin<T>::NodoBin(){
	tipoelem elmentoNullo;
	this->sinistro = NULL;
	this->destro = NULL;
	this->genitore = NULL;
	this->valore = elmentoNullo;
}

template < class T >
NodoBin<T>::~NodoBin(){

}

template < class T >
void NodoBin<T>::setSinistro(nodo c){
	this->sinistro = c;
}

template < class T >
void NodoBin<T>::setDestro(nodo c){
	this->destro = c;
}

template < class T >
void NodoBin<T>::setParent(nodo c){
	this->genitore = c;
}

template < class T >
typename NodoBin<T>::nodo NodoBin<T>::getDestro() const{
	return this->destro;
}

template < class T >
typename NodoBin<T>::nodo NodoBin<T>::getSinistro() const{
	return this->sinistro;
}

template < class T >
typename NodoBin<T>::nodo NodoBin<T>::getParent() const{
	return this->genitore;
}


template < class T >
typename NodoBin<T>::tipoelem NodoBin<T>::leggiCella() const{
	return this->valore;
}

template < class T >
void NodoBin<T>::scriviCella(tipoelem e){
	this->valore = e;
}

template< class Y >
ostream& operator<< (ostream &out, NodoBin<Y> &nodo){
	out << nodo.leggiCella() << endl;
	return out;
}

#endif

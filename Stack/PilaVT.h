#ifndef PILAVT_H_
#define PILAVT_H_

#include "Pila.h"
#include "nodo.h"

const int MAXLUNG = 1024;

template< class T >
class PilaVT : public Pila<T>{
public:
	typedef T tipoelem;
	typedef Nodo<T> Nodo;

	PilaVT();
	PilaVT(int);
	PilaVT(const PilaVT &);
	~PilaVT();

	void creaPila();
	bool pilaVuota() const;
	tipoelem leggiPila() const;
	void fuoriPila();
	void inPila(const tipoelem &e);

	int size() const;

    PilaVT<T>& operator= (const PilaVT<T> &);
    bool operator== (const PilaVT<T> &p);

	template< class Y>
	friend ostream& operator<< (ostream &, Pila<Y> &);

private:
	int testa;
	int dimArray;
	int dimP;
	Nodo *elementi;
};

template< class T >
PilaVT<T>::PilaVT()
{
    dimArray = MAXLUNG;
	creaPila();
}

template< class T >
PilaVT<T>::PilaVT(int dim)
{
    dimArray = dim;
	creaPila();
}

template< class T >
void PilaVT<T>::creaPila()
{
	this->testa = 0;
	this->elementi = new Nodo[dimArray];
	this->dimP = 0;
}

template< class T >
PilaVT<T>::PilaVT(const PilaVT &pila){
    this->creaPila();
    this->dimArray = pila.dimArray;
    this->testa = pila.testa;
	for(int i = 0; i < MAXLUNG; i++){
		typename PilaVT<T>::tipoelem e = pila.elementi[i].getElemento();
		this->elementi[i].setElemento(e);
	}
}

template< class T >
PilaVT<T>::~PilaVT(){
    delete[] elementi;
}

template< class T>
bool PilaVT<T>::pilaVuota() const
{
	return testa == 0;
}

template< class T>
typename PilaVT<T>::tipoelem PilaVT<T>::leggiPila() const
{
	return (elementi[testa - 1].getElemento());
}

template< class T>
void PilaVT<T>::fuoriPila()
{
	if (!pilaVuota()){
		testa -= 1;
	} else {
		cout << "nessun elemento nella pila" << endl;
	}
}

template< class T>
void PilaVT<T>::inPila(const tipoelem &el)
{
	if (testa == MAXLUNG){
		cout<<"raggiunta capacità massima della pila"<<endl;
	} else {
		elementi[testa].setElemento(el);
		testa++;
		dimP++;
	}
}
template< class T>
int PilaVT<T>::size() const{
    return this->dimP;
}

template< class Y >
ostream& operator<< (ostream &out, PilaVT<Y> &pila){
	out << "P = < ";
	PilaVT<Y> x = pila;
	typename PilaVT<Y>::tipoelem e;

	while(!x.pilaVuota()){
		e = x.leggiPila();
		out << e  << " ";
		x.fuoriPila();
	}
	out << ">" << endl;

	return out;
}

template<class T>
PilaVT<T>& PilaVT<T>::operator= (const PilaVT<T> &p){
    this-> testa = p.testa;
    this->dimArray = p.dimArray;
    this->dimP = p.dimP;

    Nodo *vetElem = new Nodo[this->dimArray];

    for(int i = 0; i < this->dimP; i++){
        vetElem[i] = p.elementi[i];
    }

    delete [] this->elementi;

    this->elementi = vetElem;
}

template<class T>
bool PilaVT<T>::operator== (const PilaVT<T> &p){
    bool flag = true;

    if(this->size() != p.size()){
        flag = false;
    } else {
        int i = 0;
        typename PilaVT<T>::Nodo n = p.elementi[0];
        typename PilaVT<T>::Nodo m = this->elementi[0];

        while(i <= this->size() && flag){
            typename PilaVT<T>::tipoelem e1 = n.getElemento();
            typename PilaVT<T>::tipoelem e2 = m.getElemento();

            if(e1 != e2)
                flag = false;
            else {
                n = p.elementi[++i];
                m = this->elementi[i];
            }
        }
    }

    return flag;
}
#endif

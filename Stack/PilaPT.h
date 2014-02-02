#ifndef PILAPT_H_
#define PILAPT_H_
#include <iostream>

#include "Pila.h"
#include "Cella.h"

using namespace std;

template< class T >
class PilaPT : public Pila<T>{
public:
	typedef T tipoelem;
	typedef Cella<T> *cella;

	PilaPT();
	PilaPT(const PilaPT<T> &);
	~PilaPT();

	void creaPila();
	bool pilaVuota() const;
	tipoelem leggiPila() const;
	void fuoriPila();
	void inPila(const tipoelem &);

	int size() const;

	PilaPT<T>& operator= (const PilaPT<T> &);
	bool operator== (const PilaPT<T> &);

    template< class Y>
	friend ostream& operator<< (ostream &, PilaPT<Y> &);

private:
	cella testa;
	cella pila;
	int dimP;
};

template< class T >
PilaPT<T>::PilaPT()
{
	creaPila();
}

template< class T >
PilaPT<T>::~PilaPT(){
	cella temp;
	while (testa != pila){
		temp = this->testa;
		testa = testa->getSucc();
		delete temp;
	}
	delete pila;
}

template< class T >
void PilaPT<T>::creaPila()
{
	tipoelem elementoNullo;
	this->pila = new Cella<T>();
	this->pila->setPrec(this->pila);
	this->pila->setSucc(this->pila);
	this->pila->setElemento(elementoNullo);
	this->testa = this->pila;
	this->dimP = 0;
}

template< class T >
PilaPT<T>::PilaPT(const PilaPT<T> &p){
	this->creaPila();
	typename PilaPT<T>::cella n = p.pila->getPrec();

	while(n != p.pila){
		typename PilaPT<T>::tipoelem e = n->getElemento();
		this->inPila(e);
		n = n->getPrec();
	}
}

template< class T>
bool PilaPT<T>::pilaVuota() const
{
	return testa == pila;
}

template< class T>
typename PilaPT<T>::tipoelem PilaPT<T>::leggiPila() const
{
	if(!pilaVuota())
		return (this->testa->getElemento());
}

template< class T>
void PilaPT<T>::fuoriPila()
{
	if (!pilaVuota()){
		cella top = this->pila->getSucc();
		this->pila->setSucc(top->getSucc());
		top->getSucc()->setPrec(this->pila);
		this->testa = top->getSucc();
		delete top;
	} else {
		cout << "nessun elemento nella pila" << endl;
	}
}

template< class T>
void PilaPT<T>::inPila(const tipoelem &el)
{
	typename PilaPT<T>::cella temp = new Cella<T>();
	temp->setElemento(el);

	if(pilaVuota()){
		this->pila->setSucc(temp);
		this->pila->setPrec(temp);
		temp->setPrec(this->pila);
		temp->setSucc(this->pila);
	} else {
		cella top = this->pila->getSucc();
		temp->setPrec(this->pila);
		temp->setSucc(top);
		top->setPrec(temp);
		this->pila->setSucc(temp);
	}

    this->dimP++;
	this->testa = temp;
}

template< class T >
int PilaPT<T>::size() const {
    return this->dimP;
}

template< class Y >
ostream& operator<< (ostream &out, PilaPT<Y> &pila){
	out << "P = < ";
	PilaPT<Y> x = pila;
	typename PilaPT<Y>::tipoelem e;

	while(!x.pilaVuota()){
		e = x.leggiPila();
		out << e  << " ";
		x.fuoriPila();
	}
	out << ">" << endl;

	return out;
}

template<class T>
PilaPT<T>& PilaPT<T>::operator= (const PilaPT<T> &p){
    while(!this->pilaVuota()){
        this->fuoriPila();
    }

	typename PilaPT<T>::cella n = p.pila->getPrec();

	while(n != p.pila){
		typename PilaPT<T>::tipoelem e = n->getElemento();
		this->inPila(e);
		n = n->getPrec();
	}

}

template<class T>
bool PilaPT<T>::operator== (const PilaPT<T> &p){
    bool flag = true;

    if(this->size() != p.size()){
        flag = false;
    } else {
        typename PilaPT<T>::cella n = p.pila->getSucc();
        typename PilaPT<T>::cella m = this->pila->getSucc();

        while(n != p.pila && m != this->pila && flag){
            typename PilaPT<T>::tipoelem e1 = n->getElemento();
            typename PilaPT<T>::tipoelem e2 = m->getElemento();
            if(e1 != e2)
                flag = false;
            else {
                n = n->getSucc();
                m = m->getSucc();
            }
        }
    }

    return flag;
}
#endif

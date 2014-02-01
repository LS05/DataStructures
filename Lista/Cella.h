#ifndef CELLA_H_
#define CELLA_H_

#include <iostream>

template< class Y >
class Cella{
public:
	Cella();
	~Cella();

	typedef Y tipoelem;

	void setElemento(tipoelem);
	tipoelem getElemento() const;
	void setSucc(Cella *);
	Cella<Y> * getSucc() const;
	void setPrec(Cella *);
	Cella<Y> * getPrec() const;
private:
	tipoelem elemento;
	Cella * prec;
	Cella * succ;
};

// costruttore
template< class Y >
Cella< Y >::Cella(){
	this->succ = NULL;
	this->prec = NULL;
}

// distruttore
template< class Y >
Cella< Y >::~Cella(){

}

template< class Y >
void Cella< Y >::setElemento(const tipoelem e)
{
	this->elemento = e;
}

template< class Y >
void Cella< Y >::setSucc(Cella *c)
{
	this->succ = c;
}

template< class Y >
Cella< Y > * Cella< Y >::getSucc() const
{
	return succ;
}

template< class Y >
void  Cella< Y >::setPrec(Cella *c)
{
	this->prec = c;
}

template< class Y >
typename Cella<Y>::tipoelem Cella< Y >::getElemento() const {
	return elemento;
}

template< class Y >
Cella< Y >* Cella< Y >::getPrec() const
{
	return this->prec;
}

#endif /* CELLA_H_ */

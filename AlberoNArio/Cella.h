#ifndef CELLA_H
#define CELLA_H

template < class T >
class Cella{
public:
	typedef T tipoelem;

	Cella();
	Cella(tipoelem);
	~Cella();
	void setElemento(tipoelem);
	tipoelem getElemento() const;
	void setSucc(Cella *);
	Cella<T> * getSucc() const;
	void setPrec(Cella *);
	Cella<T> * getPrec() const;
private:
	tipoelem elemento;
	Cella *prec;
	Cella *succ;
};

template<class T>
Cella<T>::Cella() {
	this->prec = NULL;
	this->succ = NULL;
}

template<class T>
Cella<T>::Cella(tipoelem t) {
	this->elemento = t;
	this->prec = NULL;
	this->succ = NULL;
}


template<class T>
Cella<T>::~Cella() { }

template<class T>
void Cella<T>::setElemento(tipoelem t) {
	this->elemento = t;
	return;
}

template<class T>
typename Cella<T>::tipoelem Cella<T>::getElemento() const {
	return this->elemento;
}

template<class T>
void Cella<T>::setSucc(Cella* nodo) {
	this->succ = nodo;
	return;
}

template<class T>
Cella<T>* Cella<T>::getSucc() const {
	return this->succ;
}

template<class T>
void Cella<T>::setPrec(Cella* nodo) {
	this->prec = nodo;
}

template<class T>
Cella<T>* Cella<T>::getPrec() const {
	return this->prec;
}

#endif

#ifndef PILA_H_
#define PILA_H_

#include <iostream>

using namespace std;

template< class T >
class Coda{
public:
	typedef T value_type;

	virtual void creaCoda() = 0;
	virtual bool codaVuota() const = 0;
	virtual value_type leggiCoda() const = 0;
	virtual void fuoriCoda() = 0;
	virtual void inCoda(const value_type &) = 0;
};

#endif

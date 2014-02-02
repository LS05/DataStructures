#ifndef PILA_H_
#define PILA_H_

#include <iostream>

using namespace std;

template< class T >
class Pila{
public:
	typedef T value_type;

	virtual void creaPila() = 0;
	virtual bool pilaVuota() const = 0;
	virtual value_type leggiPila() const = 0;
	virtual void fuoriPila() = 0;
	virtual void inPila(const value_type &) = 0;
	virtual int size() const = 0;
 };

#endif

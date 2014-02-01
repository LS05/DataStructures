#ifndef _LISTALIN_H
#define _LISTALIN_H

#include <iostream>

using namespace std;

template< class T, class P >
class Linear_list{
 public:
	typedef T value_type;
	typedef P position;

	virtual void crealista() = 0;
	virtual bool listavuota() const = 0;
	virtual value_type leggilista(position) const = 0;
	virtual void scrivilista(const value_type &x, position p) = 0;
	virtual position primolista() const = 0;
	virtual bool finelista(position) const = 0;
	virtual position succlista(position) const = 0;
	virtual position predlista(position) const = 0;
	virtual void inslista(const value_type &, position) = 0;
	virtual void canclista(position pos) = 0;
	/**
        Funzioni di servizio implementate
	*/
    int size() const;
    void clear();

};

/* sovraccarica <<. Attenzione se il tipo restituito da read non è primitivo, allora
 * anche per questo tipo bisogna sovraccaricare l'operatore <<
 */
template< class T, class P >
ostream& operator<<(ostream& os, const Linear_list<T,P> &l){
	typename Linear_list<T,P>::position p;
	p = l.primolista();
	cout << "[";
	while (!l.finelista(p)){
		if (p != l.primolista())
			cout << ", " << l.leggilista(p);
		else
			cout << l.leggilista(p);
		p = l.succlista(p);
	}
	cout << "]" << endl;
	return os;
}

template< class T, class P >
int Linear_list<T, P>::size() const{
    int dimList = 0;
    typename Linear_list<T,P>::position p;
	p = this->primolista();
	while(!this->finelista(p)){
        dimList++;
        p = this->succlista(p);
	}

	return dimList;
}

template< class T, class P >
void Linear_list<T, P>::clear(){

    typename Linear_list<T,P>::position p;
	p = this->primolista();
	while(!this->finelista(p)){
        this->canclista(p);
        p = this->succlista(p);
	}

	return;
}

#endif

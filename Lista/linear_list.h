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
	virtual position ultimolista() const = 0;
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

    bool operator== (const Linear_list<T , P> &ls1);
    bool operator!= (const Linear_list<T , P> &ls1);
    Linear_list<T, P>& operator= (const Linear_list<T, P> &lista);
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

template< class T, class P >
bool Linear_list<T, P>::operator==(const Linear_list<T, P> &ls2){
    bool flag = true;

    if(this->size() != ls2.size()){
        return false;
    }else{
        typename Linear_list<T,P>::position p = this->primolista();
        typename Linear_list<T,P>::position m = ls2.primolista();
        while(!this->finelista(p) && !ls2.finelista(m) && flag){
            if(this->leggilista(p) != ls2.leggilista(m))
                flag = false;
            p = this->succlista(p);
            m = ls2.succlista(m);
        }
    }

    return flag;
}

template< class T, class P >
bool Linear_list<T, P>::operator!=(const Linear_list<T, P> &ls2){
    bool flag = true;

    if(this->size() != ls2.size()){
        return flag;
    }else{
        typename Linear_list<T,P>::position p = this->primolista();
        typename Linear_list<T,P>::position m = ls2.primolista();
        while(!this->finelista(p) && !ls2.finelista(m) && flag){
            if(this->leggilista(p) == ls2.leggilista(m))
                flag = false;
            p = this->succlista(p);
            m = ls2.succlista(m);
        }
    }

    return flag;
}

template< class T , class P >
Linear_list<T, P>& Linear_list<T, P>::operator= (const Linear_list<T, P> &lista){
    this->clear();
    this->crealista();
    typename Linear_list<T,P>::position p = lista.primolista();
    typename Linear_list<T,P>::position m = this->primolista();

    while(!lista.finelista(p)){
        this->inslista(lista.leggilista(p), this->succlista(m));
        p = lista.succlista(p);
        m = this->succlista(m);
    }

    return *this;
}

#endif

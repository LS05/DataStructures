#ifndef _CODAVT_
#define _CODAVT_
#include "Coda.h"

using namespace std;

template < class T >
class CodaVT : public Coda<T>{

public:
	typedef T tipoelem;

	CodaVT();
	CodaVT(int n);
	~CodaVT();
	CodaVT(const CodaVT<T> &);
	void creaCoda();
	bool codaVuota() const;
	tipoelem leggiCoda() const;
	void fuoriCoda();
	void inCoda(const tipoelem &);

	int size() const;

    bool operator== (const CodaVT<T> &);
    CodaVT<T>& operator= (const CodaVT<T> &);

	template<class Y>
	friend ostream& operator<< (ostream &out, CodaVT<Y> &coda);

private:
	tipoelem *elementi;
	int head, tail, maxlung, dimQ;
};

template< class T >
CodaVT<T>::CodaVT(){
	maxlung = 1024;
	creaCoda();
}

template< class T >
CodaVT<T>::CodaVT(int n){
	maxlung = n;
	creaCoda();
}

template< class T >
CodaVT<T>::~CodaVT(){
	delete[] elementi;
}

template< class T >
CodaVT<T>::CodaVT(const CodaVT<T> &coda){
	this->elementi = new typename CodaVT<T>::tipoelem[coda.maxlung];

	for(int i = 0; i < coda.maxlung; i++){
		typename CodaVT<T>::tipoelem e = coda.elementi[i];
		this->elementi[i] = e;
	}

	this->head = coda.head;
	this->tail = coda.tail;
	this->maxlung = coda.maxlung;
}

template< class Y >
ostream& operator<< (ostream &out, CodaVT<Y> &coda){
	out << "P = < ";
	CodaVT<Y> c = coda;
	while(!c.codaVuota()){
		typename CodaVT<Y>::tipoelem e = c.leggiCoda();
		out << e << " ";
		c.fuoriCoda();
	}

	out << ">" << endl;

	return out;
}

template< class T >
void CodaVT<T>::creaCoda(){
	elementi = new typename CodaVT<T>::tipoelem[maxlung];
	head = 0;
	tail = 0;
	dimQ = 0;
}

template< class T >
bool CodaVT<T>::codaVuota() const{
	return (tail == 0);
}

template< class T >
typename CodaVT<T>::tipoelem CodaVT<T>::leggiCoda() const{
	if (!codaVuota())
		return (elementi[head]);
}

template< class T >
void CodaVT<T>::fuoriCoda(){
	if (!codaVuota()){
		head = (head + 1) % maxlung;
		tail--;
	}
}

template< class T >
void CodaVT<T>::inCoda(const tipoelem &a){
	if (tail != maxlung){
		elementi[(head+tail) % maxlung] = a;
		tail++;
		dimQ++;
	}
}

template < class T >
int CodaVT<T>::size() const{
    return this->dimQ;
}

template < class T >
bool CodaVT<T>::operator== (const CodaVT<T> &p){
    bool flag = true;

    if(this->size() != p.size()){
        flag = false;
    } else {
        int i = 0;
        typename CodaVT<T>::tipoelem n = p.elementi[0];
        typename CodaVT<T>::tipoelem m = this->elementi[0];

        while(i <= this->size() && flag){

            if(n != m)
                flag = false;
            else {
                n = p.elementi[++i];
                m = this->elementi[i];
            }
        }
    }

    return flag;
}

template< class T >
CodaVT<T>& CodaVT<T>::operator= (const CodaVT<T> &coda){
    this->maxlung = coda.maxlung;
    this->head = coda.head;
    this->tail = coda.tail;
    this->dimQ = coda.dimQ;
    tipoelem *vetElem = new tipoelem[this->maxlung];

    for(int i = 0; i < maxlung; i++){
        vetElem[i] = coda.elementi[i];
    }

    delete [] this->elementi;
    this->elementi = vetElem;

}

#endif //CODAVT_

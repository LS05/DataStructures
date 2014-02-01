#ifndef _LISTAADIACENTI_H
#define _LISTAADIACENTI_H
#include <iostream>
#include "Cella.h"
#include "linear_list.h"

using namespace std;

template< class T >
class ListaAdiacenti : public Linear_list<T, Cella<T>*>{
public:
    typedef T tipoelem;
    typedef Cella< T > * posizione;

    ListaAdiacenti();
    ListaAdiacenti(const ListaAdiacenti<T> &);
    ~ListaAdiacenti();

    void crealista();
	bool listavuota() const;
	tipoelem leggilista(posizione) const;
	void scrivilista(const tipoelem &, posizione);
	posizione primolista() const;
	bool finelista(posizione) const;
	posizione succlista(posizione) const;
	posizione predlista(posizione) const;
	void inslista(const tipoelem &, posizione);
	void canclista(posizione);

    bool operator== (const ListaAdiacenti<T> &ls1) const;
    bool operator!= (const ListaAdiacenti<T> &ls1) const;
    ListaAdiacenti<T>& operator= (const ListaAdiacenti<T> &);
    posizione pos(int);

    template <class Y>
    friend ostream& operator<< (ostream &out, ListaAdiacenti<Y> &lista);

private:
      posizione lista;
};

template< class T >
ListaAdiacenti< T >::ListaAdiacenti()
{
	crealista();
}

template< class T >
ListaAdiacenti< T >::ListaAdiacenti(const ListaAdiacenti<T> &lista)
{
    this->crealista();
    posizione p = lista.primolista();
    posizione m = this->primolista();
    
    while(!lista.finelista(p)){
        this->inslista(lista.leggilista(p), this->succlista(m));
        p = lista.succlista(p);
        m = this->succlista(m);
    }
}

template< class T >
ListaAdiacenti< T >::~ListaAdiacenti()
{
	posizione primo = primolista();
	posizione q;
	while (this->lista != primo){
		q = primo;
		primo = primo->getSucc();
		delete q;
	}
	delete lista;
}

template< class Y >
ostream& operator<< (ostream &out, ListaAdiacenti<Y> &lista){
	out << "L = < ";
	typename ListaAdiacenti<Y>::posizione p = lista.primolista();
	while(!lista.finelista(p)){
		out << lista.leggilista(p) << " ";
		p = lista.succlista(p);
	}
	out << ">" << endl;
    
	return out;
}

/**
 * In questo caso si assume che due liste sono uguali se contengono
 * gli stessi elementi nelle stesse posizioni.
 * Viceversa sono diverse
 */

template< class T >
bool ListaAdiacenti<T>::operator==(const ListaAdiacenti<T> &ls2) const{
    bool flag = true;
    
    if(this->size() != ls2.size()){
        return false;
    }else{
        posizione p = this->primolista();
        posizione m = ls2.primolista();
        while(!this->finelista(p) && !ls2.finelista(m) && flag){
            if(this->leggilista(p) != ls2.leggilista(m))
                flag = false;
            p = this->succlista(p);
            m = ls2.succlista(m);
        }
    }
    
    return flag;
}

template< class T >
bool ListaAdiacenti<T>::operator!=(const ListaAdiacenti<T> &ls2) const{
    bool flag = true;
    
    if(this->size() != ls2.size()){
        return false;
    }else{
        posizione p = this->primolista();
        posizione m = ls2.primolista();
        while(!this->finelista(p) && !ls2.finelista(m) && flag){
            if(this->leggilista(p) == ls2.leggilista(m))
                flag = false;
            p = this->succlista(p);
            m = ls2.succlista(m);
        }
    }
    
    return flag;
}

template< class T >
ListaAdiacenti<T>& ListaAdiacenti<T>::operator= (const ListaAdiacenti<T> &lista){
    this->clear();
    this->crealista();
    posizione p = lista.primolista();
    posizione m = this->primolista();
    
    while(!lista.finelista(p)){
        this->inslista(lista.leggilista(p), this->succlista(m));
        p = lista.succlista(p);
        m = this->succlista(m);
    }
    
    return *this;
}

template<class T>
void ListaAdiacenti<T>::crealista()
{
	tipoelem elementoVuoto;
	this->lista = new Cella<T>();
	this->lista->setElemento(elementoVuoto);
	this->lista->setSucc(this->lista);
	this->lista->setPrec(this->lista);
}

template<class T>
bool ListaAdiacenti<T>::listavuota() const
{
    return (lista->getSucc() == lista) && (lista->getPrec() == lista);
}

template<class T>
typename ListaAdiacenti<T>::posizione ListaAdiacenti<T>::primolista() const
{
	return this->lista->getSucc();
}

template<class T>
bool ListaAdiacenti<T>::finelista(posizione cella) const
{
	return (cella == this->lista);
}

template<class T>
typename ListaAdiacenti<T>::posizione ListaAdiacenti<T>::succlista(posizione cella) const
{
	return (cella->getSucc());
}

template<class T>
typename ListaAdiacenti<T>::posizione ListaAdiacenti<T>::predlista(posizione cella) const
{
	return (cella->getPrec());
}

template<class T>
void ListaAdiacenti<T>::inslista(const tipoelem &a, posizione cella)
{
	typename ListaAdiacenti<T>::posizione temp = new Cella<T>();
	temp->setElemento(a);
	temp->setPrec(cella->getPrec());
	temp->setSucc(cella);
	(cella->getPrec())->setSucc(temp);
	cella->setPrec(temp);
	cella=temp;
}

template<class T>
typename ListaAdiacenti<T>::tipoelem ListaAdiacenti<T>::leggilista(posizione cella) const
{
	return (cella->getElemento());
}

template<class T>
void ListaAdiacenti<T>::scrivilista(const tipoelem &a, posizione cella)
{
	cella->setElemento(a);
	return;
}

template<class T>
void ListaAdiacenti<T>::canclista(posizione cella)
{
	typename ListaAdiacenti<T>::posizione temp = cella;
    
	(cella->getPrec())->setSucc(cella->getSucc());
	(cella->getSucc())->setPrec(cella->getPrec());
	cella = cella->getSucc();
	delete temp;
	return;
}

//template< class T >
//int ListaAdiacenti< T >::size() const
//{
//    return Linear_list<T, posizione>::size();
//}
//
//template< class T >
//void ListaAdiacenti< T >::clear()
//{
//    return Linear_list<T, posizione>::clear();
//}

#endif

//
//template< class T >
//ListaAdiacenti< T >::ListaAdiacenti(const ListaAdiacenti<T> &lista) {
//    this->crealista();
//    posizione p = lista.primolista();
//    posizione m = this->primolista();
//
//    while(!lista.finelista(p)){
//        this->inslista(lista.leggilista(p), m);
//        p = lista.succlista(p);
//        m = this->succlista(m);
//    }
//}
//
//template< class T >
//ListaAdiacenti< T >::~ListaAdiacenti() {
//   posizione q;
//   while (primo!= NULL) {
//      q = primo->successivo;
//      delete(primo);
//      primo = q;
//   }
//}
//
//template< class T >
//void ListaAdiacenti< T >::crealista() {
//   primo = NULL;
//}
//
//template< class T >
//bool ListaAdiacenti< T >::listavuota() {
//   return (primo==NULL);
//}
//
//template< class T >
//typename ListaAdiacenti< T >::posizione ListaAdiacenti< T >::primolista() const {
//   return primo;
//}
//
//template< class T >
//typename ListaAdiacenti< T >::posizione ListaAdiacenti< T >::predlista(posizione p) {
//   if (p!=primo) {
//      posizione q = primo;
//      while ((q->successivo!=p) && (q!=NULL))
//         q = q->successivo;
//      return (q);
//   } else
//      return NULL;
//}
//
//template< class T >
//typename ListaAdiacenti< T >::posizione ListaAdiacenti< T >::succlista(posizione p) const{
//   return (p->successivo);
//}
//
//template< class T >
//bool ListaAdiacenti< T >::finelista(posizione p) const{
//   return (p==NULL);
//}
//
//template< class T >
//void ListaAdiacenti< T >::inslista(tipoelem a, posizione p) {
//   posizione q = new (nodoAdiacenti< T >);
//   q->etichetta = a;
//   q->successivo = p;
//   if (p==primo)
//      primo = q;
//   else {
//      p = predlista(p);
//      p->successivo = q;
//   }
//}
//
//template< class T >
//bool ListaAdiacenti< T >::canclista(posizione p) {
//   if (p!=NULL) {
//      if (p==primo)
//         primo = p->successivo;
//      else {
//		 posizione q;
//         q = predLista(p);
//         q->successivo = p->successivo;
//      }
//      delete(p);
//      return (true);
//   }
//   else
//      return (false);
//}
//
//template< class T >
//bool ListaAdiacenti< T >::scrivilista(tipoelem a, posizione p) {
//   if (p!=NULL) {
//      p->etichetta = a;
//      return (true);
//   }
//   else
//      return (false);
//}
//
//template< class T >
//typename ListaAdiacenti< T >::tipoelem ListaAdiacenti< T >::leggilista(posizione p) const{
//   if (p!=NULL)
//      return (p->etichetta);
//}
//
//template< class T >
//ListaAdiacenti< T > &ListaAdiacenti< T >::operator=(ListaAdiacenti< T > &l) {
//   posizione p, q;
//   while (primo!=NULL) {
//      p = primo->successivo;
//      delete (primo);
//      primo = p;
//   }
//   p = l.primolista();
//   tipoelem a;
//   while (!l.finelista(p)) {
//      a = l.leggilista(p);
//      inslista(a, NULL);
//      p = l.succlista(p);
//   }
//
//   return *this;
//}
//
//template< class T >
//typename ListaAdiacenti< T >::posizione ListaAdiacenti< T >::pos(int i) {
//   if (i>=1) {
//	  posizione p = primo;
//      int j;
//      for (j = 0; (j<i)&&(p!=NULL); j++)
//         p = p->successivo;
//      return (p);
//   }
//   else {
//      return (NULL);
//   }
//}
//
//template< class Y >
//ostream& operator<< (ostream &out, ListaAdiacenti<Y> &lista){
//	out << "L = < ";
//	typename ListaAdiacenti<Y>::posizione p = lista.primolista();
//	while(!lista.finelista(p)){
//		out << lista.leggilista(p) << " ";
//		p = lista.succlista(p);
//	}
//	out << ">" << endl;
//
//	return out;
//}
//
//#endif

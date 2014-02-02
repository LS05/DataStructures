#ifndef _BINTREEPT_H_
#define _BINTREEPT_H_

#include <iostream>

#include "BinTree.h"
#include "CellaTree.h"

using namespace std;

template <class T>
class BinTreePT : public Bin_tree<T, NodoBin<T>* >{
public:

	typedef typename Bin_tree<T, NodoBin<T>* >::value_type value_type;
	typedef typename Bin_tree<T, NodoBin<T>* >::Nodo nodo;

	BinTreePT();
	BinTreePT(const BinTreePT &);
	~BinTreePT();

	void create();
	bool empty() const;

	nodo root() const;
	nodo parent(nodo) const;
	nodo sx(nodo) const;
	nodo dx(nodo) const;
	bool sx_empty(nodo) const;
	bool dx_empty(nodo) const;
    bool isleaf(nodo) const;
	void erase(nodo);

	value_type read(nodo) const;
	void write(nodo , value_type);

	void ins_root(nodo);
	void ins_sx(nodo);
	void ins_dx(nodo);

	void preorder(nodo);
	void postorder(nodo);
	void inorder(nodo);


	BinTreePT<T>& operator= (const BinTreePT<T> &tree);
private:
    void fillTree(NodoBin<T>*, NodoBin<T>*);
	nodo radice;

};

template <class T>
BinTreePT<T>::BinTreePT(){
	create();
}

template <class T>
void BinTreePT<T>::fillTree(NodoBin<T> *dest, NodoBin<T> *source){

	if ( source == NULL  ) {
		return;
	} else {

	    if(source->getSinistro() != NULL){
            NodoBin<T> *nodo = new NodoBin<T>();
            nodo->scriviCella(source->getSinistro()->leggiCella());
            dest->setSinistro(nodo);
            nodo->setParent(dest);
	    }

        if(source->getDestro() != NULL){
            NodoBin<T> *nodo = new NodoBin<T>();
            nodo->scriviCella(source->getDestro()->leggiCella());
            dest->setDestro(nodo);
            nodo->setParent(dest);
        }

		fillTree( dest->getSinistro(), source->getSinistro() );

        fillTree( dest->getDestro(), source->getDestro() );
	}
}

template <class T>
BinTreePT<T>& BinTreePT<T>::operator= (const BinTreePT<T> &tree)
{
    this->erase(this->root());

    if(!tree.empty()){
        NodoBin<T> *nodo = new NodoBin<T>();

        nodo->scriviCella(tree.root()->leggiCella());
        this->radice = nodo;
        fillTree(this->radice, tree.root());
    }

    return *this;
}

template <class T>
BinTreePT<T>::BinTreePT(const BinTreePT<T> &tree){
    if(!tree.empty()){
        NodoBin<T> *nodo = new NodoBin<T>();

        nodo->scriviCella(tree.root()->leggiCella());
        this->radice = nodo;
        fillTree(this->radice, tree.root());
    }
}

template <class T>
void BinTreePT<T>::create(){
	this->radice = NULL;
}

template <class T>
BinTreePT<T>::~BinTreePT(){

}

template <class T>
bool BinTreePT<T>::empty() const{
	return (this->radice == NULL);
}

template <class T>
typename BinTreePT<T>::nodo BinTreePT<T>::root() const{
	return (this->radice);
}

template <class T>
typename BinTreePT<T>::nodo BinTreePT<T>::parent(nodo n) const{
	return n->getParent();
}

template <class T>
typename BinTreePT<T>::nodo BinTreePT<T>::sx(nodo n) const{
	return n->getSinistro();
}

template <class T>
typename BinTreePT<T>::nodo BinTreePT<T>::dx(nodo n) const{
	return n->getDestro();
}

template <class T>
bool BinTreePT<T>::sx_empty(nodo n) const{
	return n->getSinistro() == NULL;
}

template <class T>
bool BinTreePT<T>::dx_empty(nodo n) const{
	return n->getDestro() == NULL;
}

template <class T>
void BinTreePT<T>::ins_root(nodo n)
{
	if(this->radice != NULL){
		cout << "Radice già presente" << endl;
	} else {
		n = new NodoBin<T>();
		this->radice = n;
	}
}

template <class T>
void BinTreePT<T>::ins_sx(nodo n)
{
	if (n->getSinistro() != NULL){
		ins_sx(n->getSinistro());
	}else{
		nodo temp = new NodoBin<T>();
		n->setSinistro(temp);
		temp->setParent(n);
	}
}

template <class T>
void BinTreePT<T>::ins_dx(nodo n)
{
	if (n->getDestro() != NULL){
		ins_dx(n->getDestro());
	}else{
		nodo temp = new NodoBin<T>();
		n->setDestro(temp);
		temp->setParent(n);
	}
}

template <class T>
void BinTreePT<T>::write(nodo n, value_type t){
	if(n != NULL)
		n->scriviCella(t);
}

template <class T>
typename BinTreePT<T>::value_type BinTreePT<T>::read(nodo n) const{
	if(n != NULL)
		return n->leggiCella();
}

template <class T>
void BinTreePT<T>::erase(nodo n){
	if (n != NULL){
		if (!sx_empty(n))
			erase(n->getSinistro());
		if (!dx_empty(n))
			erase(n->getDestro());
		if (n != radice){
			nodo q = n->getParent();
			if (q->getSinistro() == n)
				q->setSinistro(NULL);
			else
				q->setDestro(NULL);
		} else
			radice = NULL;
		delete n;
	}
}

template <class T>
bool BinTreePT<T>::isleaf(nodo n) const{
    bool flag = false;
    
    if(n != NULL){
        if(sx_empty(n) && dx_empty(n))
            flag = true;
        else
            flag = false;
    }
    
    return flag;
}



template <class T>
void BinTreePT<T>::postorder(nodo p){
	if (p == NULL) {
		return;
	} else {
		postorder( this->sx(p) );
		postorder( this->dx(p) );
		cout << this->read(p) << " ";
	}
}

template <class T>
void BinTreePT<T>::preorder(nodo p){
	if (p != NULL){
      value_type a;
      a = read(p);
    	cout << a << " ";
		if (!sx_empty(p))
			preorder(sx(p));
		if (!dx_empty(p))
			preorder(dx(p));
	}
}

template <class T>
void BinTreePT<T>::inorder(nodo p){
	if (p != NULL){
    	if (!sx_empty(p))
			inorder(sx(p));
		value_type a = read(p);
    	cout << a << " ";
		if (!dx_empty(p))
			inorder(dx(p));
	}
}
#endif

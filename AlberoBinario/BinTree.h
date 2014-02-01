#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <iostream>
#include "CodaPT.h"

using namespace std;
template <class T, class N>
class Bin_tree{
	static const int NIL = -1;
public:

	typedef T value_type;
	typedef N Nodo;

	virtual void create() = 0;
	virtual bool empty() const =  0;

	virtual Nodo root() const = 0;
	virtual Nodo parent(Nodo) const =  0;
	virtual Nodo sx(Nodo) const = 0;
	virtual Nodo dx(Nodo) const = 0;
	virtual bool sx_empty(Nodo) const = 0;
	virtual bool dx_empty(Nodo) const = 0;

	virtual void erase(Nodo) = 0;

	virtual value_type read(Nodo) const = 0;
	virtual void write(Nodo , value_type ) = 0;

	virtual void ins_root(Nodo) = 0;
	virtual void ins_sx(Nodo) = 0;
	virtual void ins_dx(Nodo) = 0;

	virtual void preorder(Nodo) = 0;
	virtual void inorder(Nodo) = 0;
	virtual void postorder(Nodo) = 0;
	void BFS(Nodo) const;

	virtual void print() const;

private:
	virtual void printSubTree(const Nodo) const;
};

template <class T, class N>
void Bin_tree<T,N>::print() const{
	if (!empty())
		printSubTree(root());
	else
		std::cout << "[]" << std::endl;
	std::cout << std::endl;
}

template <class T, class N>
void Bin_tree<T,N>::printSubTree(const Nodo n) const{
	std::cout << "[" << read(n) << ", ";
	if (!sx_empty(n))
		printSubTree(sx(n));
	else std::cout << "NIL";
	std::cout << ", ";
	if (!dx_empty(n))
		printSubTree(dx(n));
	else std::cout << "NIL";
	std::cout << " ]";
}

template <class T, class N>
void Bin_tree<T, N>::BFS(Nodo p) const{
   	CodaPT<N> q;
   	q.inCoda(p);
   	int lev = 1;
   	while (!q.codaVuota()){
   	    p = q.leggiCoda();
        q.fuoriCoda();
      	value_type a = read(p);
		cout << a << " ";
    	if (!sx_empty(p)){
			q.inCoda(sx(p));
		}
		if (!dx_empty(p)){
			q.inCoda(dx(p));
		}
   }
}

template<class T, class N>
ostream& operator<<(ostream& out, const Bin_tree<T, N>& t) {
	t.print();
	return out;
}

#endif

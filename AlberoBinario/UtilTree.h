#ifndef UTILTREE_H
#define UTILTREE_H

#include "CodaPT.h"
#include "ListaPT.h"

template<class T>
class UtilTree{
public:
    typedef T tipoelem;
    typedef typename BinTreePT<T>::nodo nodo;

    UtilTree(BinTreePT<T> &);
    void swapTree();
    void RemoveLeavesTree();
    bool SubTree(BinTreePT<T> &bt);
    ListaPT<T> levelNodes(int n);
    int altezza(nodo n);
private:
    BinTreePT<T> *tree;
    void swapSupp(BinTreePT<T> &, nodo, nodo);
    void removeLeaves(nodo);
    nodo findsubRoot(nodo, nodo, bool&);
    bool testSubTree(nodo, nodo, BinTreePT<T> &, bool &);
    void levelNodesSupp(nodo n, CodaPT<T> &ls, int lev, int curr);
};

template<class T>
UtilTree<T>::UtilTree(BinTreePT<T> &binTree){
    this->tree = &binTree;
}

template<class T>
void UtilTree<T>::swapSupp(BinTreePT<T> &rTree, nodo on, nodo n){
    nodo sx, dx, temp;
    if(!tree->sx_empty(n)){
        temp = tree->sx(n);
        rTree.ins_dx(on);
        rTree.write(rTree.dx(on), tree->read(temp));
        swapSupp(rTree, rTree.dx(on), tree->sx(n));
    }
    if(!tree->dx_empty(n)){
        temp = tree->dx(n);
        rTree.ins_sx(on);
        rTree.write(rTree.sx(on), tree->read(temp));
        swapSupp(rTree, rTree.sx(on), tree->dx(n));
    }
}

template<class T>
void UtilTree<T>::swapTree(){
    BinTreePT<T> res;
    nodo root;
    res.ins_root(root);
    res.write(res.root(), tree->read(tree->root()));
              
    this->swapSupp(res, res.root(), this->tree->root());
    
    res.print();
}

template<class T>
void UtilTree<T>::removeLeaves(nodo p){
    if(this->tree->sx_empty(p) && this->tree->sx_empty(p)){
            this->tree->erase(p);
    } else if (p != NULL){
		if (!this->tree->sx_empty(p))
			removeLeaves(this->tree->sx(p));
		if (!this->tree->dx_empty(p))
			removeLeaves(this->tree->dx(p));
	}

	return;
}

template<class T>
void UtilTree<T>::RemoveLeavesTree(){
    this->removeLeaves(this->tree->root());
}

template<class T>
typename UtilTree<T>::nodo UtilTree<T>::findsubRoot(nodo p, nodo root, bool &trovato){
    nodo res = NULL;
    if(p != NULL && !trovato){
        if(p->leggiCella() == root->leggiCella()){
            trovato = true;
            res = p;
            return res;
        }
    }
    if (p != NULL){
		if (!this->tree->sx_empty(p))
			findsubRoot(this->tree->sx(p), root, trovato);
		if (!this->tree->dx_empty(p))
            findsubRoot(this->tree->dx(p), root, trovato);
	}
}

template<class T>
bool UtilTree<T>::testSubTree(nodo foundNode, nodo btNode, BinTreePT<T> &bt, bool &chFnd){

	if (foundNode != NULL && btNode != NULL && chFnd){
        tipoelem a = this->tree->read(foundNode);
        tipoelem b = bt.read(btNode);
        if(a != b)
            chFnd = false;
        if (!this->tree->sx_empty(foundNode) && !bt.sx_empty(btNode))
            testSubTree(this->tree->sx(foundNode), bt.sx(btNode), bt, chFnd);
        if (!this->tree->dx_empty(foundNode) && !bt.dx_empty(btNode))
            testSubTree(this->tree->dx(foundNode), bt.dx(btNode), bt, chFnd);
	}

	return chFnd;
}

template<class T>
bool UtilTree<T>::SubTree(BinTreePT<T> &bt){
    bool flag = false, chFnd = true;
    nodo rootBT = bt.root();

    nodo res = findsubRoot(this->tree->root(), rootBT, flag);
    bool subFlag = testSubTree(res, bt.root(), bt, chFnd);
}

template<class T>
void UtilTree<T>::levelNodesSupp(nodo n, CodaPT<T> &ls, int lev, int curr){
    if(n != NULL){
        if(lev == curr){
            ls.inCoda(n->leggiCella());
        } else {
            levelNodesSupp(n->getSinistro(), ls, lev, curr + 1);
            levelNodesSupp(n->getDestro(), ls, lev, curr + 1);
        }
    }
}

template<class T>
ListaPT<T> UtilTree<T>::levelNodes(int n){
    CodaPT<T> q;
    ListaPT<T> ls;
    levelNodesSupp(this->tree->root(), q, n, 1);
    cout << q;
    while(!q.codaVuota()){
        T elem = q.leggiCoda();
        q.fuoriCoda();
        ls.inslista(elem, ls.succlista(ls.primolista()));
    }

    return ls;
}

template<class T>
int UtilTree<T>::altezza(nodo n){

	if ( n == NULL  ) {
		return 0;
	} else {
		return 1 + max( altezza( n->getSinistro()), altezza( n->getDestro()));
	}
}
#endif

#ifndef TREEPT_H
#define TREEPT_H

#include <iostream>
#include "Tree.h"
#include "NodoPtr.h"
#include "CodaPT.h"

using namespace std;

template<class T>
class TreePT : public Tree<T, NodoPtr<T>*>{
public:
    typedef NodoPtr<T>* node;
    typedef T tipoelem;

	TreePT();
	~TreePT();

	void create();
	bool empty() const;
	void insRoot(node);
	node root() const;
	node parent(node) const;
	bool leaf(node) const;
	node firstChild(node) const;
	bool lastSibling(node) const;
	node nextSibling(node) const;
// inserisce un node come firstChild di n
    void insFirst(node, tipoelem);
// inserisce un node come fratello di n
	void ins(node, tipoelem);

	void insFirstSubTree(node, TreePT<T>&);
	void insSubTree(node, TreePT<T>&);

	void removeSubTree(node);

	void writeNode(node, tipoelem);
    tipoelem readNode(node) const;

    void preorder(node);
    void postorder(node);
    void inorder(node n);
    void bfs(node n);

    void print();

private:
    void supPrint(node);
    node radice; //puntantore al nodo Radice
};

template<class T>
TreePT<T>::TreePT(){
   create();
}

template<class T>
TreePT<T>::~TreePT(){
   removeSubTree(radice);
}

template<class T>
void TreePT<T>::create(){
   radice = NULL;
}

template<class T>
bool TreePT<T>::empty() const{
   return (radice == NULL);
}

template<class T>
void TreePT<T>::insRoot(node n){
    if (radice == NULL){
        n = new NodoPtr<T>();
        radice = n;
    }
}

template<class T>
typename TreePT<T>::node TreePT<T>::root() const{
   return radice; //se l'albero è vuoto, ritorna NULL
}

template<class T>
typename TreePT<T>::node TreePT<T>::parent(node n) const{
   return n->getDaddy(); //se n è la radice, ritorna NULL
}

template<class T>
bool TreePT<T>::leaf(node n) const{
   return (n->getFirstSon() == NULL);
}

template<class T>
typename TreePT<T>::node TreePT<T>::firstChild(node n) const{
   return n->getFirstSon(); //se n non ha figli, ritorna NULL
}

template<class T>
bool TreePT<T>::lastSibling(node n) const{
   return (n->getNextBro() == NULL);
}

template<class T>
typename TreePT<T>::node TreePT<T>::nextSibling(node n) const{
   return n->getNextBro(); //se n è ultimo fratello, ritorna NULL
}

template<class T>
void TreePT<T>::insFirst(node n, tipoelem e){
    if(n != NULL && radice != NULL){
        node m = new NodoPtr<T>();
        m->setEtichetta(e);
        if(leaf(n)){
            n->setFirstSon(m);
            m->setDaddy(n);
        }else{
            m->setNextBro(n->getFirstSon());
            n->setFirstSon(m);
            m->setDaddy(n);
        }
    }
    return;
}
template<class T>
void TreePT<T>::ins(node n, tipoelem e){
    if(n != NULL && radice != NULL){
        node m = new NodoPtr<T>();
        m->setEtichetta(e);
        m->setNextBro(n->getNextBro());
        n->setNextBro(m);
        m->setDaddy(n->getDaddy());
    }
}

template<class T>
void TreePT<T>::insFirstSubTree(node n, TreePT<T> &tree){
	if ((radice != NULL) && (tree.root() != NULL) && (n != NULL)){
  		tree.root()->setNextBro(n->getFirstSon());
  		tree.root()->setDaddy(n);
        n->setFirstSon(tree.root());
	}
}

template<class T>
void TreePT<T>::insSubTree(node n, TreePT<T>& tree){
	if ((radice != NULL) && (tree.root() != NULL) && (n != NULL) && ( n != radice)){
		tree.root()->setDaddy(n->getDaddy());
		tree.root()->setNextBro(n->getNextBro());
		n->setNextBro(tree.root());
	}
}

template<class T>
void TreePT<T>::removeSubTree(node n){
   if ((n!=NULL) && (radice!=NULL)){
      while (n->getFirstSon()!=NULL)
         removeSubTree(n->getFirstSon());
      if (n->getDaddy()!=NULL)
         if (n->getDaddy()->getFirstSon() == n)
            n->getDaddy()->setFirstSon(n->getNextBro());
         else{
            node m = n->getDaddy()->getFirstSon();
            while (m->getNextBro() != n)
               m = m->getNextBro();
            m->setNextBro(n->getNextBro());
         }
		else radice = NULL;
      delete n;
	}
}
template<class T>
typename TreePT<T>::tipoelem TreePT<T>::readNode(node n) const{
   return n->getEtichetta();
}

template<class T>
void TreePT<T>::writeNode(node n, tipoelem a){
   if(n != NULL)
      n->setEtichetta(a);
}

template<class T>
void TreePT<T>::supPrint(node n){
    while (n != NULL){
             cout << "(" << readNode(n);
             supPrint(firstChild(n));
             cout << ")";
             n = nextSibling(n);
    }
}
template<class T>
void TreePT<T>::print(){
   if (radice != NULL){
        supPrint(radice);
        cout << endl;
	} else {
        cout << "()";
	}
}

template<class T>
void TreePT<T>::preorder(node n){
    Tree<T, NodoPtr<T>*>::preorder(n);
}

template<class T>
void TreePT<T>::postorder(node n){
    Tree<T, NodoPtr<T>*>::postorder(n);
}

template<class T>
void TreePT<T>::inorder(node n){
    Tree<T, NodoPtr<T>*>::inorder(n);
}

template<class T>
void TreePT<T>::bfs(node n){
    CodaPT<node> q;
    q.inCoda(n);
    while(!q.codaVuota()){
        node v = q.leggiCoda();
        cout << v->getEtichetta() << " ";
        q.fuoriCoda();
        if (!leaf(v)){
            node m = firstChild(v);
            while (!lastSibling(m)){
                q.inCoda(m);
                m = nextSibling(m);
            }
            q.inCoda(m);
        }
    }
}
#endif

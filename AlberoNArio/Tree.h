#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

template<class I, class N>
class Tree {
 public:
	typedef I item;
	typedef N node;

	virtual void create () = 0;
	virtual bool empty () const = 0;
	virtual void insRoot (node) = 0;
	virtual node root () const = 0;
	virtual node parent (node) const = 0;
	virtual bool leaf (node) const = 0;
	virtual node firstChild (node) const = 0;
	virtual bool lastSibling (node) const = 0;
	virtual node nextSibling (node) const = 0;
	virtual void removeSubTree (node) = 0;

	virtual void writeNode (node, item) = 0;
	virtual item readNode (node) const = 0;

	void preorder(node);
	void postorder(node);
	void inorder(node);

};

template<class I, class N>
void Tree<I, N>::preorder(node n){
   if (n != NULL){
      while (n != NULL){
         cout << readNode(n) << " ";
         preorder(firstChild(n));
         n = nextSibling(n);
      }
	}
}

template<class I, class N>
void Tree<I, N>::postorder(node n){
   if (n != NULL){
      while (n != NULL){
         postorder(firstChild(n));
         cout << readNode(n) << " ";
         n = nextSibling(n);
      }
   }
}

template<class I, class N>
void Tree<I, N>::inorder(node n){
   if (n != NULL){
      if (!leaf(n)){
         inorder(firstChild(n));
         cout << readNode(n) << " ";
         n = firstChild(n);
         while (!lastSibling(n)){
            n = nextSibling(n);
            inorder(n);
         }
      } else cout << readNode(n) << " ";
	}
}
#endif

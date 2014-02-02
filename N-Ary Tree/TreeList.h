#ifndef TREELIST_H
#define TREELIST_H

#include "ListaPT.h"
#include "Tree.h"

#define MAXNODES 100

template<class I>
class TreeList : public Tree<I, int> {
 public:

	typedef I item;
	typedef int node;

	TreeList(){
		create();
	};

	void create () ;
	bool empty () const ;
	void insRoot (node) ;
	node root () const ;
	node parent (node) const ;
	bool leaf (node) const ;
	node firstChild (node) const ;
	bool lastSibling (node) const ;
	node nextSibling (node) const ;

    void insFirstSubTree (node, TreeList<I> &) ;
	void insSubTree (node, TreeList &) ;
	void removeSubTree (node) ;

	void insFirst(node, item);
	void ins(node, item);

	void writeNode (node, item) ;
	item readNode (node) const ;

    int getNumNodes() const;
	void print() const;

 private:
	struct Record {
		item e;
		bool used;
		ListaPT<int> childs;
	};
	typedef ListaPT<int>::position position_list;

	Record nodes[MAXNODES];
	node _root;
	int numNodes;

	void suppSubTree(node, node, TreeList<I> &);

};

template <class I>
void TreeList<I>::print() const{
	cout << "\n{";
	for (int i=0; i < MAXNODES;i++){
		if (nodes[i].used==true){
			cout << "\n  " << readNode(i) << ":  ";
			if (!leaf(i)){
				position_list child = nodes[i].childs.primolista();
				while (!nodes[i].childs.finelista(child)){
					cout << readNode(nodes[i].childs.leggilista(child)) << " ";
					child = nodes[i].childs.succlista(child);
				}
			}
		}

	}
	cout << "\n}\n";
}

template <class I>
void TreeList<I>::create(){
	numNodes = 0;
	for (int i=0; i< MAXNODES;i++){
		nodes[i].used = false;
		nodes[i].childs.crealista();
	}
}

template <class I>
bool TreeList<I>::empty() const{
	return(numNodes == 0);
}

template <class I>
void TreeList<I>::insRoot (node n){
	if (empty()){
		_root = 0;
		nodes[0].used = true;
		numNodes++;
	}
}

template <class I>
typename TreeList<I>::node TreeList<I>::root () const{
	return _root;
}

template <class I>
typename TreeList<I>::node TreeList<I>::parent (node n) const{
	position_list child;
	int p;
	for (int i=0; i < MAXNODES; i++){
		if (!nodes[i].childs.listavuota()){
			child = nodes[i].childs.primolista();
			bool found = false;
			while (!nodes[i].childs.finelista(child) && !found){
				if (nodes[i].childs.leggilista(child) == n){
					found = true;
					p = i;
				}
				child = nodes[i].childs.succlista(child);
			}
			if (found)
				return(i);
		}
	}
}

template <class I>
bool TreeList<I>::leaf(node n) const{
	return(nodes[n].childs.listavuota());
}

template <class I>
typename TreeList<I>::node TreeList<I>::firstChild (node n) const{
	if (!leaf(n)){
		return(nodes[n].childs.leggilista(nodes[n].childs.primolista()));
	}
}

template <class I>
bool TreeList<I>::lastSibling (node n) const {
	position_list c;
	node p = parent(n);
	c = nodes[p].childs.primolista();
	while (!nodes[p].childs.finelista(c))
		c = nodes[p].childs.succlista(c);
	return (n == nodes[p].childs.leggilista(c));
}

template <class I>
typename TreeList<I>::node TreeList<I>::nextSibling (node n) const{
	if (!lastSibling(n)){
		position_list c;
		node p = parent(n);
		c = nodes[p].childs.primolista();
		while (!nodes[p].childs.finelista(c)){
			if (nodes[p].childs.leggilista(c) == n)
				return (nodes[p].childs.leggilista(nodes[p].childs.succlista(c)));
			c = nodes[p].childs.succlista(c);
		}
	}
}

// inserisce un node come firstChild di n
template <class I>
void TreeList<I>::insFirst(node n, item el){
	// cerca una posizione libera
	int k;
	for (k=0; k < MAXNODES && nodes[k].used == true; k++);
	if (k<MAXNODES){
		nodes[k].used = true;
		nodes[k].e = el;
		nodes[n].childs.inslista(k, nodes[n].childs.primolista());
	}
}

// inserisce un node come fratello di n
template <class I>
void TreeList<I>::ins(node n, item el){
	// cerca una posizione libera
	int k;
	for (k=0; k < MAXNODES && nodes[k].used == true; k++);
	if (k<MAXNODES){
		nodes[k].used = true;
		nodes[k].e = el;
		node p = parent(n);
		position_list child = nodes[p].childs.primolista();
		bool found = false;
		while (!nodes[p].childs.finelista(child) && !found){
			if (nodes[p].childs.leggilista(child) == n)
					found = true;
			child = nodes[p].childs.succlista(child);
		}
		nodes[p].childs.inslista(k, child);
	}
}



template <class I>
void TreeList<I>::removeSubTree (node n){

	position_list c;
	if (!leaf(n)){
		while (!nodes[n].childs.listavuota()){
			removeSubTree(nodes[n].childs.leggilista(nodes[n].childs.primolista()));
		}
	}
	node p = parent(n);
	c = nodes[p].childs.primolista();
	while(nodes[p].childs.leggilista(c) != n)
		c = nodes[p].childs.succlista(c);
	nodes[p].childs.canclista(c);
	nodes[n].used = false;
}

template <class I>
void TreeList<I>::writeNode (node n, item el){
	nodes[n].e = el;
}

template <class I>
typename TreeList<I>::item TreeList<I>::readNode (node n) const{
	return(nodes[n].e);
}

template <class I>
int TreeList<I>::getNumNodes() const {
    return this->numNodes;
}

//visita in preordine più aggiunta di tree all'albero.
template <class I>
void TreeList<I>::suppSubTree(node r, node n, TreeList<I> &tree){
    item e = tree.readNode(n);
    node v;
    if(!tree.leaf(n)){
        v = tree.firstChild(n);
        insFirst(r, tree.readNode(v));
        r = firstChild(r);
        while(!tree.lastSibling(v)){
            suppSubTree(r, v, tree);
            v = tree.nextSibling(v);
            if(!tree.lastSibling(v)){
                ins(r, tree.readNode(v));
            }
        }
    }
}

template <class I>
void TreeList<I>::insFirstSubTree (node n, TreeList<I> &tree){
    if(this->numNodes + tree.getNumNodes() < MAXNODES){
        insFirst(n, tree.readNode(tree.root()));
//ins è la radice del sottoalbero da aggiungere (parametro: tree)
        node ins = firstChild(n);
        suppSubTree(ins, tree.root(), tree);
    }
}

template <class I>
void TreeList<I>::insSubTree (node n, TreeList<I> &tree){
    if(this->numNodes + tree.getNumNodes() < MAXNODES){
        item treeRoot = tree.readNode(tree.root());
        ins(n, treeRoot);
        int pos = 0;

        for (int k = 0; k < MAXNODES && nodes[k].used == true; k++){
            if(nodes[k].e == treeRoot){
                pos = k;
                break;
            }
        }
//pos rappresenta il nodo in cui è stata posta la radice del sottoalbero da aggiungere
        suppSubTree(pos, tree.root(), tree);
    }
}

#endif
